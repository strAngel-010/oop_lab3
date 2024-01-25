template <typename T>
using Iterator = Table<T>::TableIterator;

template <typename T>
Table<T>::Table(Living** arr, unsigned int len, int* status, int* prices) {
    try {
        this->arr = new Keyspace[len];
        this->len = len;
        allocated_len = len;

        for (int i = 0; i < (int)len; ++i){
            this->arr[i].l = arr[i];
            
            if (status) { this->arr[i].status = status[i]; }
            if (prices) { this->arr[i].price = prices[i]; }
        }
    } catch (...) { throw; }
}

template <typename T>
Table<T>::~Table(){
    if (arr){
        Iterator it;
        for (it = begin(); it != end(); ++it){
            delete it->l;
        }
        delete[] arr;
    }
}

template <typename T>
Table<T> &Table<T>::setLiving(Living** arr, unsigned int len) {
    try {
        if (this->arr) { delete[] this->arr; }
        this->arr = nullptr;
        this->arr = new Keyspace[len];
        for (int i = 0; i < (int)len; ++i){
            this->arr[i].l = arr[i];
        }
    } catch (...) { throw; }
    
    return *this;
}

template <typename T>
Table<T> &Table<T>::setStatus(unsigned int ind, int status){
    if (status < -1 || status > 1){
        throw std::runtime_error("Wrong status (must be >=-1 && <= 1)");
    }
    
    if ((int)ind >= len) {
        throw std::runtime_error("Wrong index");
    }

    try { this->arr[ind].status = status; }
    catch (...) { throw; }
    return *this;
}

template <typename T>
Table<T> &Table<T>::setPrice(unsigned int ind, int price){
    if (ind >= len) {
        throw std::runtime_error("Wrong index");
    }

    try { arr[ind].price = price; }
    catch (...) { throw; }
    return *this;
}

template <typename T>
Living* Table<T>::getLiving(unsigned int ind) const {
    try{
        if (ind >= len) { throw std::runtime_error("Wrong index"); }
        return arr[ind].l;
    }
    catch (...) { throw; }
}

template <typename T>
int Table<T>::getStatus(unsigned int ind) const {
    if (ind >= len) { throw std::runtime_error("Wrong index"); }

    try { return arr[ind].status; }
    catch (...) { throw; }
}

template <typename T>
int Table<T>::getPrice(unsigned int ind) const {
    if (ind >= len) { throw std::runtime_error("Wrong index"); }

    try { return arr[ind].price; }
    catch (...) { throw; }
}

template <typename T>
Table<T> &Table<T>::addLiving(Living* living, int status, int price){
    if (status < -1 || status > 1) { throw std::runtime_error("Wrong status"); }
    try {
        if (len == allocated_len){
            arr = keyspace_realloc(arr, len, len + REALLOC_SIZE);
            allocated_len += REALLOC_SIZE;
        }
        arr[len].l = living;
        arr[len].status = status;
        arr[len].price = price;
        ++len;
        return *this;
    } catch (...) { throw; }
}

template <typename T>
int Table<T>::findLiving(Address& addr) const {
    if (!arr) { return -1; }
    try{
        Iterator it;
        Living* l;
        for (it = begin(); it != end(); ++it){
            l = it->l;
            if (l && l->getAddr() && *(l->getAddr()) == addr){
                return distance(begin(), it);
            }
        }
        return -1;
    } catch (...) { throw; }
}

template <typename T>
void Table<T>::findCheapest(int& apartment_ind, int& flat_ind) const{
    try{
        apartment_ind = -1;
        flat_ind = -1;
        Iterator it;
        for (it = begin(); it != end(); ++it){
            if (dynamic_cast<Apartment*>(it->l)){
                if (apartment_ind == -1 || arr[apartment_ind].price > it->price) { 
                    apartment_ind = distance(begin(), it);
                }
            } else {
                if (flat_ind == -1 || arr[flat_ind].price > it->price) { 
                    flat_ind = distance(begin(), it);
                }
            }
        }
    } catch (...) { throw; }
}

template <typename T>
void Table<T>::local_min(Iterator cur, Iterator end, int& local_apartment_ind, int& local_flat_ind) {
    thread_local int min_apartment_price = std::numeric_limits<int>::max();
    thread_local int min_flat_price = std::numeric_limits<int>::max();
    for (; cur != end; ++cur) {
        if (dynamic_cast<Apartment*>(cur->l)) {
            if (cur->price < min_apartment_price) {
                local_apartment_ind = distance(begin(), cur);
                min_apartment_price = cur->price;
            }
        } else {
            if (cur->price < min_flat_price) {
                local_flat_ind = distance(begin(), cur);
                min_flat_price = cur->price;
            }
        }
    }
}

template <typename T>
void Table<T>::findCheapest_mt(int& apartment_ind, int& flat_ind) {
    apartment_ind = -1;
    flat_ind = -1;
    auto threadNum = 4;
    cout << "Total threads: " << threadNum << endl;
    vector<jthread> threads(threadNum);

    std::mutex living_mux;
    for (int i = 0; i < threadNum; i++) {
        int start_i = i * len / threadNum;
        int end_i = (i + 1) * len / threadNum;
        Iterator start(arr + start_i, arr + len);
        Iterator end(arr + end_i, arr + len);
        auto thread_func = [&](){
            thread_local int cur_a = -1;
            thread_local int cur_f = -1;
            local_min(start, end, cur_a, cur_f);

            living_mux.lock();
            if (cur_a != -1 && (apartment_ind == -1 || arr[cur_a].price < arr[apartment_ind].price)) {
                apartment_ind = cur_a;
            }
            if (cur_f != -1 && (flat_ind == -1 || arr[cur_f].price < arr[flat_ind].price)) {
                flat_ind = cur_f;
            }
            living_mux.unlock();
        };
        threads[i] = jthread(thread_func);
    }
}

template <typename T>
Table<T> &Table<T>::removeLiving(unsigned int ind){
    if (ind >= len) { throw std::runtime_error("Wrong index"); }

    try{
        delete arr[ind].l;
        arr[ind] = arr[len-1];
        --len;
    } catch (...) { throw; }
    return *this;
}

template <typename T>
Table<T> &Table<T>::erase(){
    if (arr) { delete[] arr; }
    arr = nullptr;
    len = 0;
    allocated_len = 0;
    return *this;
}