#ifndef OOPPROG3_FLAT_H
#define OOPPROG3_FLAT_H

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "../living/living.h"
#include "../room/room.h"

namespace Prog3 {
    class Flat : public Living{
        private: Room* rooms = nullptr;
        public:
            Flat();
            Flat(Address* addr, Room* rooms) noexcept : Living(addr), rooms(rooms) {};
            Flat(const Flat& ob);
            Flat(Flat&& ob) noexcept;
            ~Flat();

            Flat &setRoom(unsigned int ind, Room& room) override;
            Flat &setRooms(Room* rooms);

            Room* getRooms(unsigned int& len) const noexcept override;
            Room& getRoom(unsigned int ind) const override;
            unsigned int getRoomsCount() const noexcept override { return 4; }

            int findRoom(const char* name) const override;
            Flat* clone() const override { return new Flat(*this); }

            void print(ostream& s) const override;
            int input(istream& s) override;
    };
}

#endif