#include "cottage.h"

namespace Prog3{
    Cottage::Cottage(Address* addr, Living** living, unsigned int len){
        this->addr = addr;
        this->living = living;
        this->len = len;
    }

    Cottage::Cottage(Living** living, unsigned int len){
        this->living = living;
        this->len = len;
        this->addr = nullptr;
    }

    Cottage::Cottage(const Cottage& ob) : addr(nullptr), living(nullptr), len(0) {
        try {
            if (ob.addr){ addr = new Address(*(ob.addr)); }
            if (ob.len){
                living = new Living*[ob.len];
                for (int i = 0; i < (int)ob.len; ++i){ 
                    living[i] = ob.living[i]->clone(); 
                }
            }
            len = ob.len;
        } catch (...){ throw; }
    }

    Cottage::Cottage(Cottage&& ob) noexcept : addr(ob.addr), living(ob.living), len(ob.len) {
        ob.addr = nullptr;
        ob.living = nullptr;
        ob.len = 0;
    }

    Cottage::~Cottage(){
        if (addr) { delete addr; }
        addr = nullptr;
        if (living) { delete[] living; }
        living = nullptr;
        len = 0;
    }

    Cottage &Cottage::setLiving(Living** living, unsigned int len) noexcept {
        this->living = living;
        this->len = len;
        return *this;
    }

    Cottage &Cottage::setAddr(const char* str, unsigned int building){
        if (this->addr){ delete this->addr; }
        try{ this->addr = new Address(str, building); }
        catch(...){ throw; }
        return *this;
    }

    Cottage &Cottage::setAddr(Address* addr) noexcept {
        if (this->addr){ delete this->addr; }
        this->addr = addr;
        return *this;
    }

    Living** Cottage::getLiving(unsigned int& len) const noexcept {
        len = this->len;
        return living;
    };

    Room** Cottage::getRooms(unsigned int& len) const {
        try{
            len = 0;
            for (int i = 0; i < (int)this->len; ++i){ len += living[i]->getRoomsCount(); }
            Room** arr = new Room*[len];

            unsigned int cur_len = 0;
            int cur_filled = 0;
            Room* cur_arr = nullptr;
            for (int i = 0; i < (int)this->len; ++i){
                cur_arr = living[i]->getRooms(cur_len);
                for (int j = 0; j < (int)cur_len; ++j){
                    arr[cur_filled] = cur_arr+j;
                    ++cur_filled;
                }
            }
            return arr;
        } catch (...) { throw; }
    }

    unsigned int Cottage::getArea() const {
        try{
            unsigned int area = 0;
            unsigned int cur_len = 0;
            Room* cur_arr = nullptr;
            for (int i = 0; i < (int)this->len; ++i){
                cur_arr = living[i]->getRooms(cur_len);
                for (int j = 0; j < (int)cur_len; ++j){
                    area += cur_arr[j].getArea();
                }
            }
            return area;
        } catch (...) { throw; }
    }

    Cottage& Cottage::operator = (const Cottage& ob){
        try {
            if (addr) { delete addr; }
            addr = nullptr;
            if (ob.addr) { addr = new Address(*ob.addr); }

            if (living) { delete[] living; }
            living = nullptr;
            if (ob.len) { std::copy(ob.living, ob.living + len, living); }

            len = ob.len;
        } catch (...) { throw; }
        return *this;
    }

    int find_cottage(const Address& addr, const Cottage* arr, int len){
        try {
            for (int i = 0; i < len; ++i){
                if (arr[i].getAddr() && *(arr[i].getAddr()) == addr){
                    return i;
                }
            }
        } catch (...) { throw; }
        return -1;
    }

    std::ostream& operator << (std::ostream& s, const Cottage& cottage){
        if (cottage.getAddr()) { s << "Address: " << *cottage.getAddr() << std::endl; }
        unsigned int len;
        Living** living = cottage.getLiving(len);
        if (len){
            try {
                for (int i = 0; i < (int)len; ++i){
                    s << *living[i];
                }
            } catch (...) { throw; }
        }
        return s;
    }

    std::istream& operator >> (std::istream& s, Cottage& cottage){
        try {
            unsigned int len;
            Living** living = cottage.getLiving(len);
            living = my_realloc(living, len, len+1);
            ++len;

            int ans;
            int func_res = input_num(s, "Enter (1) for an apartment or (2) for a flat:", 1, 2, ans);
            if (func_res) { 
                delete[] living; 
                return s;
            }

            switch (ans){
                case 1:
                    living[len-1] = new Apartment();
                    break;
                case 2:
                    living[len-1] = new Flat();
                    break;
                default:
                    throw std::runtime_error("Error in switch");
            }
            s >> *living[len-1];
            if (s.eof()){
                delete living[len-1];
                delete[] living;
                return s;
            }
            cottage.setLiving(living, len);
            return s;
        } catch (...) { throw; }
    }
}