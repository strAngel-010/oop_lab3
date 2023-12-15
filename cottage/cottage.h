#ifndef OOPPROG3_COTTAGE_H
#define OOPPROG3_COTTAGE_H

#include "../address/address.h"
#include "../living/living.h"
#include "../room/room.h"
#include "../apartment/apartment.h"
#include "../flat/flat.h"

namespace Prog3 {
    class Cottage{
        private:
            Address* addr = nullptr;
            Living** living = nullptr;
            unsigned int len = 0;
        public:
            explicit Cottage() = default;
            explicit Cottage(Address* addr, Living** living = nullptr, unsigned int len = 0);
            explicit Cottage(Living** living, unsigned int len);
            explicit Cottage(const Cottage& ob);
            explicit Cottage(Cottage&& ob) noexcept;
            ~Cottage();

            Cottage &setLiving(Living** living, unsigned int len) noexcept;
            Cottage &setAddr(const char* str, unsigned int building);
            Cottage &setAddr(const Address& addr) noexcept;

            Address* getAddr() const noexcept { return addr; };
            Living** getLiving(unsigned int& len) const noexcept;
            unsigned int getLen() const noexcept { return len; };

            Room** getRooms(unsigned int& len) const;
            unsigned int getArea() const;
            Cottage &addLiving(Living** l);
    };
}

#endif