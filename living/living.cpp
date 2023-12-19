#include "living.h"

namespace Prog3{
    Living::~Living(){
        if (addr){ delete addr; }
        addr = nullptr;
    }

    Living &Living::setFlat(unsigned int flat){
        try { 
            if (!addr){ addr = new Address(); }
            addr->setFlat(flat); 
        } catch(...){ throw; }
        return *this;
    }

    Living &Living::setAddr(Address* addr) noexcept {
        if (this->addr) { delete this->addr; }
        this->addr = addr;
        return *this;
    }

    ostream& operator << (ostream& s, const Living& l){
        Address* addr = l.getAddr();
        if (addr) { s << "Address: " << *addr << std::endl; }
        l.print(s);
        return s;
    }

    istream& operator >> (istream& s, Living& l){
        l.input(s);
        return s;
    }

    Living** living_realloc(const Living** arr, int prev_size, int size){
        try{
            Living** new_arr = new Living*[size];
            for (int i = 0; i < prev_size; ++i){ new_arr[i] = (Living*)arr[i]; }
            delete[] arr;
            return new_arr;
        } catch (...){ throw; }
    }
}