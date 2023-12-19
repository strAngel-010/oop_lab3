#ifndef OOPPROG3_LIVING_H
#define OOPPROG3_LIVING_H

#include <iostream>
#include "../address/address.h"
#include "../room/room.h"

namespace Prog3 {
    class Living {
        protected:
            Address* addr = nullptr;
        public:
            Living() = default;
            Living(Address* addr) noexcept : addr(addr) {}
            Living(Living&& ob) noexcept : addr(ob.addr) { ob.addr = nullptr; }
            virtual ~Living();

            Living &setFlat(unsigned int flat);
            Living &setAddr(Address* addr) noexcept;
            virtual Living &setRoom(unsigned int ind, Room& room) = 0;

            Address* getAddr() const noexcept { return addr; }

            virtual int findRoom(const char* name) const = 0;
            virtual Room* getRooms(unsigned int& len) const noexcept = 0;
            virtual Room& getRoom(unsigned int ind) const = 0;
            virtual unsigned int getRoomsCount() const noexcept = 0;
            virtual Living* clone() const = 0;

            virtual void print(ostream& s) const = 0;
            virtual int input(istream& s) = 0;
            friend ostream& operator << (ostream&, const Living&);
            friend istream& operator >> (istream&, Living&);
    };
    Living** living_realloc(const Living** arr, int prev_size, int size);
}

#endif