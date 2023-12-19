#ifndef OOPPROG3_APARTMENT_H
#define OOPPROG3_APARTMENT_H

#include <stdexcept>
#include <iostream>
#include "../living/living.h"
#include "../room/room.h"
#include "../aux_funcs/aux_funcs.h"

namespace Prog3 {
    class Apartment : public Living{
        private:
            Room* rooms = nullptr;
            unsigned int len = 0;
        public:
            Apartment() = default;
            Apartment(Address* addr, Room* rooms = nullptr, unsigned int len = 0) : Living(addr), rooms(rooms), len(len) {};
            Apartment(const Apartment& ob);
            Apartment(Apartment&& ob) noexcept;
            ~Apartment();

            Apartment &setRoom(unsigned int ind, Room& room) override;
            Apartment &setRooms(unsigned int len, Room* rooms) noexcept;

            Room &getRoom(unsigned int ind) const override;
            Room* getRooms(unsigned int& len) const noexcept override;
            unsigned int getRoomsCount() const noexcept override { return len; }

            Apartment &addRoom(const Room& room);
            Apartment &addRoom(const char* name, unsigned int area, char* comment = nullptr);
            int findRoom(const char* name) const override;
            Apartment* clone() const override { return new Apartment(*this); }

            void print(ostream& s) const override;
            int input(istream& s) override;
    };
}

#endif