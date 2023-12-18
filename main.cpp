#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include "table/table.h"
#include "cottage/cottage.h"
#include "aux_funcs/aux_funcs.h"

using namespace Prog3;
using std::cin, std::cout, std::endl;

int start_dialog(int& ans);
int check_in(Table& table, Cottage** arr, int& len);

int main(){
    Table table;
    Cottage* cottages = nullptr;
    int len = 0;
    int ans = 0;
    int func_res = 0;
    while (true){
        try {
            func_res = start_dialog(ans);
            if (func_res) { break; }
            switch (ans){
                case 1:
                    func_res = check_in(table, &cottages, len);
                    break;
                default:
                    throw std::runtime_error("Error in switch");
            }
            if (func_res) { break; }
        } catch (...) { return 0; }
    }
    cout << "Exiting..." << endl;
    if (cottages) { delete[] cottages; }
}

int start_dialog(int& ans){
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Check in" << endl;
        cout << "2. Check out" << endl;
        cout << "3. List all unoccupied living" << endl;
        cout << "4. Find cheapest living" << endl;
        cout << "----------" << endl;
        
        try { return input_num(cin, "", 1, 4, ans); }
        catch (...) { throw; }
    }
}

//ToDo: remake check_in()
int check_in(Table& table, Cottage** arr, int& len){
    int func_res = 0;
    std::string street;
    try { func_res = input_string(cin, "Enter street name: ", street); }
    catch (...) { throw; }
    if (func_res) { return func_res; }

    int building;
    try { 
        func_res = input_num(cin, "Enter building number: ", 1, std::numeric_limits<int>::max(), building); 
    } catch (...) { throw; }
    if (func_res) { return func_res; }

    int flat;
    try { 
        func_res = input_num(cin, "Enter flat number: ", 1, std::numeric_limits<int>::max(), flat); 
    } catch (...) { throw; }
    if (func_res) { return func_res; }

    try{
        Address* address = new Address(street.c_str(), building, flat);
        int res = table.findLiving(*address);
        if (res != -1){ 
            //ToDo: debug this case
            table.setStatus(res, 1); 
            delete address;
        } else {
            cout << "No living with this address. Creating new living..." << endl;
            Address* cottage_addr = new Address(street.c_str(), building);
            res = find_cottage(*cottage_addr, *arr, len);
            unsigned int living_len;
            Living* living_to_add;
            if (res != -1){
                delete cottage_addr;
                cin >> *arr[res];
                living_to_add = arr[res]->getLiving(living_len)[living_len-1];
                living_to_add->setAddr(address);
            }
            else {
                cout << "No cottage for this living found. Creating new cottage..." << endl;
                *arr = (Cottage*)cottage_realloc(*arr, len, len+1);
                ++len;
                cin >> *arr[len-1];
                living_to_add = arr[len-1]->getLiving(living_len)[living_len-1];
                living_to_add->setAddr(address);
                arr[len-1]->setAddr(cottage_addr);
            }

            int price;
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

//Test main() function for Table and Living output
/*
int main(){
    Address* a1 = new Address("First Street", 1, 1);
    Room* rooms_a1 = new Room[3];
    rooms_a1[0] = Room("Toilet", 5);
    rooms_a1[1] = Room("Bathroom", 7);
    rooms_a1[2] = Room("Bedroom", 15);
    Apartment* a = new Apartment(a1, rooms_a1, 3);

    Address* a2 = new Address("First Street", 1, 2);
    Room* rooms_a2 = new Room[4]{};
    rooms_a2[0] = Room("Toilet", 5);
    rooms_a2[1] = Room("Bathroom", 7);
    rooms_a2[2] = Room("Bedroom", 15);
    rooms_a2[3] = Room("Living Room", 15);
    Flat* f = new Flat(a2, rooms_a2);

    std::cout << *a << std::endl;
    std::cout << *f << std::endl;

    Living** living = new Living*[2];
    living[0] = a;
    living[1] = f;
    Table t(living, 2);
    std::cout << t;
    delete[] living;
}
*/