#include <iostream>
#include <stdexcept>
#include <string>
#include "cottage/cottage.h"

unsigned int start_dialog();
void checkIn();

using namespace Prog3;
using std::cin, std::cout, std::endl;
/*
int main(){
    unsigned int ans = 0;
    while (true){
        try {
            ans = start_dialog();
            if (ans == 0) { break; }
            switch (ans){
                case 1:
                    checkIn();
                    break;
            }
        } catch (...) { return 0; }
    }
    cout << "Exiting..." << endl;
}

unsigned int start_dialog(){
    unsigned int ans = 0;
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Check in" << endl;
        cout << "2. Check out" << endl;
        cout << "3. List all unoccupied living" << endl;
        cout << "4. Find cheapest living" << endl;
        cout << "----------" << endl;
        
        cin >> ans;
        if (cin.eof()) { return 0; }
        if (cin.bad()) { throw std::runtime_error("Input broken"); }
        if (cin.good()){
            if (ans > 4 || ans == 0) { cout << "Wrong number, please repeat" << endl; }
            else { return ans; }
        }
    }
}

void checkIn(){
    cout << "Enter street name: ";
    string street;
    cin >> street;
    if (cin.eof()) { return; }
    if (cin.bad()) { throw std::runtime_error("Input broken"); }
    cout << endl;

    cout << "Enter building number: ";
    unsigned int building;
    cin >> building;
    if (cin.eof()) { return; }
    if (cin.bad()) { throw std::runtime_error("Input broken"); }
    cout << endl;

    cout << "Enter flat number: ";
    unsigned int flat;
    cin >> flat;
    if (cin.eof()) { return; }
    if (cin.bad()) { throw std::runtime_error("Input broken"); }
    cout << endl;

    Address* address = new Address(street.c_str(), building, flat);
}
*/

int main(){}