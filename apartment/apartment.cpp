#include "apartment.h"

namespace Prog3{
    Apartment::Apartment(const Apartment& ob) : Living(nullptr), rooms(nullptr), len(0){
        try{
            if (ob.addr){ addr = new Address(*ob.addr); }
            if (ob.len){
                rooms = new Room[ob.len];
                for (int i = 0; i < (int)ob.len; ++i){
                    rooms[i] = ob.rooms[i];
                }
                len = ob.len;
            }
        } catch (...){ throw; }
    }

    Apartment::Apartment(Apartment&& ob) noexcept : Living(ob.addr), rooms(ob.rooms), len(ob.len) {
        ob.addr = nullptr;
        ob.rooms = nullptr;
        ob.len = 0;
    }

    Apartment::~Apartment(){
        if (rooms){ delete[] rooms; }
        rooms = nullptr;
        len = 0;
        Living::~Living();
    }

    Apartment &Apartment::setRoom(unsigned int ind, Room& room){
        if (ind >= len){ throw std::runtime_error("Wrong index"); }
        try{ rooms[ind] = room; }
        catch (...){ throw; }
        return *this;
    }

    Apartment &Apartment::setRooms(unsigned int len, Room* rooms) noexcept {
        if (this->rooms) { delete[] this->rooms; }
        this->rooms = rooms;
        this->len = len;
        return *this;
    }

    Room &Apartment::getRoom(unsigned int ind) const {
        if (ind >= len){ throw std::runtime_error("Wrong index"); }
        try { return rooms[ind]; }
        catch (...){ throw; }
    }

    Room* Apartment::getRooms(unsigned int& len) const noexcept {
        len = this->len;
        return rooms;
    }

    Apartment &Apartment::addRoom(const Room& room){
        try {
            rooms = (Room*)room_realloc(rooms, len, len+1);
            rooms[len] = room;
            ++len;
        } catch(...){ throw; }
        return *this;
    }

    Apartment &Apartment::addRoom(const char* name, unsigned int area, char* comment){
        try{
            Room r(name, area, comment);
            this->addRoom(r);
        } catch(...){ throw; }
        return *this;
    }

    int Apartment::findRoom(const char* name) const {
        for (int i = 0; i < (int)len; ++i){
            try {
                if (std::strcmp(rooms[i].getName(), name) == 0){
                    return i;
                }
            } catch(...){ throw; }
        }
        return -1;
    }

    void Apartment::print(ostream& s) const {
        s << "Apartment:" << std::endl;
        if (rooms){
            s << "Rooms:" << std::endl;
            for (int i = 0; i < (int)len; ++i){
                s << i << ") " << rooms[i] << std::endl;
            }
        }
    }
}