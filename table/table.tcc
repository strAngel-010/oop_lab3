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
    Iterator it;
    for (it = begin(); it != end(); ++it){
        delete it->l;
    }
    delete[] arr;
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
            arr = my_realloc(arr, len, len + REALLOC_SIZE);
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
                if (apartment_ind == -1) { 
                    apartment_ind = distance(begin(), it);
                }
                if (arr[apartment_ind].price < it->price) { 
                    apartment_ind = distance(begin(), it);
                }
            } else {
                if (flat_ind == -1) { 
                    flat_ind = distance(begin(), it);
                }
                if (arr[flat_ind].price < it->price) { 
                    flat_ind = distance(begin(), it);
                }
            }
        }
    } catch (...) { throw; }
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