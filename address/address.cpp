#include "address.h"

using std::cin;

namespace Prog3{
    Address::Address(const char* street, unsigned int building, unsigned int flat){
        try{
            int len = std::strlen(street);
            this->street = new char[len+1];
            std::copy(street, street+len+1, this->street);
        } catch (...){ throw; }
        this->building = building;
        this->flat = flat;
    }

    Address::Address(const Address& ob) : street(nullptr), building(0), flat(0) {
        try {
            if (ob.street) {
                int len = std::strlen(ob.street);
                street = new char[len + 1];
                std::copy(ob.street, ob.street + len + 1, street);
            }
            building = ob.building;
            flat = ob.flat;
        } catch (...){ throw; }
    }

    Address::Address(Address&& ob) noexcept : street(ob.street), building(ob.building), flat(ob.flat){
        ob.street = nullptr;
        ob.building = 0;
        ob.flat = 0;
    }

    Address::~Address(){
        if (street){ delete[] street; }
        street = nullptr;
        building = 0;
        flat = 0;
    }

    Address &Address::setStreet(const char* street){
        try{
            int len = std::strlen(street);
            this->street = new char[len+1];
            std::copy(street, street+len+1, this->street);
        } catch (...){ throw; }
        return *this;
    }

    Address &Address::setBuilding(unsigned int building) noexcept {
        this->building = building; 
        return *this;
    }

    Address &Address::setFlat(unsigned int flat) noexcept{
        this->flat = flat;
        return *this;
    }

    ostream& operator << (ostream& s, const Address& addr){
        if (addr.getStreet()) { s << addr.getStreet() << " "; }
        if (addr.getBuilding()) { s << addr.getBuilding() << " "; }
        if (addr.getFlat()) { s << addr.getFlat(); }
        return s;
    }

    istream& operator >> (istream& s, Address& addr){
        try{
            if (addr.getStreet()) { delete[] addr.getStreet(); }
            std::string street;
            int func_res = input_string(s, "Enter street name:", street);
            int building;
            func_res = input_num(cin, "Enter building number: ", 1, std::numeric_limits<int>::max(), building);
            int flat;
            func_res = input_num(cin, "Enter flat number: ", 1, std::numeric_limits<int>::max(), flat);
            if (func_res) { return s; }
            addr.setStreet(street.c_str());
            addr.setBuilding(building);
            addr.setFlat(flat);
            return s;
        } catch (...) { throw; }
    }

    bool operator == (const Address& first, const Address& second) noexcept{
        return std::strcmp(first.getStreet(), second.getStreet()) == 0 &&
        first.getBuilding() == second.getBuilding() &&
        first.getFlat() == second.getFlat();
    }
}