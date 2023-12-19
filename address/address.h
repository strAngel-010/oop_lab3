#ifndef OOPPROG3_ADDRESS_H
#define OOPPROG3_ADDRESS_H

#include <cstring>
#include <iostream>
#include <limits>
#include "../aux_funcs/aux_funcs.h"

using std::ostream, std::istream;

namespace Prog3{
    class Address {
        private:
            char* street = nullptr;
            unsigned int building = 0;
            unsigned int flat = 0;
        public:
            explicit Address() = default;
            explicit Address(const char* street, unsigned int building, unsigned int flat = 0);
            explicit Address(const Address& ob);
            explicit Address(Address&& ob) noexcept;
            ~Address();

            Address &setStreet(const char* street);
            Address &setBuilding(unsigned int building) noexcept;
            Address &setFlat(unsigned int flat) noexcept;

            const char* getStreet() const noexcept { return street; }
            unsigned int getBuilding() const noexcept { return building; }
            unsigned int getFlat() const noexcept { return flat; }
            
            friend ostream& operator << (ostream&, const Address&);
            friend istream& operator >> (istream&, Address&);
            friend bool operator == (const Address& first, const Address& second) noexcept;
    };
}

#endif