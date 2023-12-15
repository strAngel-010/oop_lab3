#include "flat.h"

namespace Prog3{
    Flat::Flat() : Living() {
        try { rooms = new Room[4]; }
        catch (...) { throw; }
    }

    Flat::Flat(const Flat& ob) : Living(nullptr) {
        try{
            addr = new Address(*ob.addr);
            if (rooms) { delete[] rooms; }
            rooms = new Room[4];
            for (int i = 0; i < 4; ++i){ rooms[i] = ob.rooms[i]; }
        } catch (...){ throw; }
    }

    Flat::Flat(Flat&& ob) noexcept : Living(ob.addr), rooms(ob.rooms) {
        ob.addr = nullptr;
        ob.rooms = nullptr;
    }

    Flat::~Flat(){
        if (addr) { delete addr; }
        addr = nullptr;
        if (rooms) { delete[] rooms; }
        rooms = nullptr;
    }

    Flat &Flat::setRoom(unsigned int ind, Room& room){
        if (ind > 3) { throw std::runtime_error("Wrong index (must be >=0 && <= 3)"); }
        try{ rooms[ind] = room; }
        catch (...) { throw; }
        return *this;
    }

    Flat &Flat::setRooms(Room* rooms){
        if (this->rooms) { delete[] this->rooms; }
        this->rooms = rooms;
        return *this;
    }

    Room* Flat::getRooms(unsigned int& len) const noexcept {
        len = 4;
        return (Room*)rooms;
    }

    Room& Flat::getRoom(unsigned int ind) const {
        if (ind > 3) { throw std::runtime_error("Wrong index (must be >=0 && <= 3)"); }
        return (Room&)rooms[ind];
    }

    int Flat::findRoom(const char* name) const {
        for (int i = 0; i < 4; ++i){
            try {
                if (rooms[i].getName() && 
                std::strcmp(rooms[i].getName(), name) == 0){
                    return i;
                }
            } catch(...){ throw; }
        }
        throw std::runtime_error("Room not found");
    }

    void Flat::print(ostream& s) const {
        s << "Flat:" << std::endl;
        if (rooms){
            s << "Rooms:" << std::endl;
            for (int i = 0; i < 4; ++i){
                s << i+1 << ") " << rooms[i] << std::endl;
            }
        }
    }
}