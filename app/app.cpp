#include "app.h"

using std::cout, std::endl, std::cin;

namespace Prog3 {
    App::~App(){
        if (cottages) { delete[] cottages; }
        cottages = nullptr;
        cout << "Exiting..." << endl;
    }

    App& App::start(){
        int func_res;
        int ans;
        while (true){
            try {
                func_res = start_dialog(ans);
                if (func_res) { break; }
                switch (ans){
                    case 1:
                        func_res = check_in(table, &cottages, len);
                        break;
                    case 2:
                        check_out(table);
                        break;
                    case 3:
                        print_unsettled(table);
                        break;
                    case 4:
                        print_cheapest(table);
                        break;
                    case 5:
                        cout << table;
                        break;
                    default:
                        throw std::runtime_error("Error in switch");
                }
                if (func_res) { break; }
            } catch (...) { return *this; }
        }
        return *this;
    }

    int App::start_dialog(int& ans){
        while (true) {
            cout << "Choose an option:" << endl;
            cout << "1. Check in" << endl;
            cout << "2. Check out" << endl;
            cout << "3. List all unoccupied living" << endl;
            cout << "4. Find cheapest living" << endl;
            cout << "5. Print table" << endl;
            cout << "----------" << endl;
            
            try { return input_num(cin, nullptr, 1, 5, ans); }
            catch (...) { throw; }
        }
    }

    int App::check_in(Table<Keyspace>& table, Cottage** arr, int& len){
        try{
            Address* address = new Address();
            cin >> *address;
            if (cin.eof()){
                delete address;
                return 1;
            }

            int res = table.findLiving(*address);
            if (res != -1){ 
                table.setStatus(res, 1); 
                delete address;
            } else {
                cout << "No living with this address. Creating new living..." << endl;
                Address* cottage_addr = new Address(address->getStreet(), address->getBuilding());
                res = find_cottage(*cottage_addr, *arr, len);
                unsigned int living_len;
                Living* living_to_add;
                if (res != -1){
                    delete cottage_addr;
                    cin >> *(arr[res]);
                    if (cin.eof()){
                        delete address;
                        return 1;
                    }
                    living_to_add = arr[res]->getLiving(living_len)[living_len-1];
                    living_to_add->setAddr(address);
                }
                else {
                    cout << "No cottage for this living found. Creating new cottage..." << endl;
                    *arr = (Cottage*)my_realloc(*arr, len, len+1);
                    ++len;
                    cin >> *arr[len-1];
                    if (cin.eof()){
                        delete address;
                        delete cottage_addr;
                        return 1;
                    }
                    living_to_add = arr[len-1]->getLiving(living_len)[living_len-1];
                    living_to_add->setAddr(address);
                    arr[len-1]->setAddr(cottage_addr);
                }

                int price;
                int func_res;
                try { 
                    func_res = input_num(cin, "Enter price per sq meter: ", 0, std::numeric_limits<int>::max(), price); 
                } catch (...) { throw; }
                if (func_res) { 
                    delete living_to_add;
                    return func_res; 
                }
                table.addLiving(living_to_add, 1, price);
            }
        } catch (...) { throw; }
        cout << "Checked-in successfully" << endl << endl;
        return 0;
    }

    void App::check_out(Table<Keyspace>& table){
        try {
            Address* address = new Address();
            cin >> *address;
            if (cin.eof()){
                delete address;
                return;
            }

            int res = table.findLiving(*address);
            if (res != -1){ 
                table.setStatus(res, 0); 
                cout << "Checked-out successfully" << endl;
            }
            else { cout << "No living with this address found" << endl;}
            cout << endl;
            delete address;
        } catch (...) { throw; }
    }

    void App::print_unsettled(Table<Keyspace>& table){
        Table<Keyspace>::TableIterator it;
        for (it = table.begin(); it != table.end(); ++it){
            if (it->status == 0) { cout << *(it->l); }
        }
        cout << endl;
    }

    void App::print_cheapest(Table<Keyspace>& table){
        int apartment_ind = -1;
        int flat_ind = -1;
        try {
            table.findCheapest(apartment_ind, flat_ind);
            Keyspace* arr = table.getLivingArr();
            if (apartment_ind != -1){
                cout << "Cheapest apartment: " << endl;
                cout << *(arr[apartment_ind].l);
                cout << "Price per sq meter:" << arr[apartment_ind].price;
            }
            
            if (flat_ind != -1){
                cout << "Cheapest flat: " << endl;
                cout << *(arr[flat_ind].l);
                cout << "Price per sq meter:" << arr[flat_ind].price;
            }
            cout << endl;
        } catch (...) { throw; }
    }
}