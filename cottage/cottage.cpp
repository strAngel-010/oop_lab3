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
        for (int i = 0; i < (int)len; ++i){ delete living[i]; }
        if (living) { delete[] living; }
        living = nullptr;
        len = 0;
    }

    Cottage &Cottage::setLiving(Living** living, unsigned int len) noexcept {
        if (this->living){ delete this->living; }
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

    Cottage &Cottage::setAddr(const Address& addr) noexcept {
        if (this->addr){ delete this->addr; }
        this->addr = (Address*)&addr;
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
}