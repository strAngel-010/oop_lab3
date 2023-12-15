#ifndef OOPPROG3_ROOM_H
#define OOPPROG3_ROOM_H

#include <cstring>
#include <iostream>

using std::ostream;

namespace Prog3{
    class Room {
        private:
            char* name = nullptr;
            unsigned int area = 0;
            char* comment = nullptr;
        public:
            Room() = default;
            Room(const char* name, unsigned int area, char* comment = nullptr);
            Room(const Room& ob);
            Room(Room&& ob) noexcept;
            ~Room();

            Room &setName(const char* name);
            Room &setArea(unsigned int area) noexcept;
            Room &setComment(const char* comment);

            unsigned int getArea() const noexcept { return area; }
            char* getName() const noexcept { return name; }
            char* getComment() const noexcept { return comment; }

            Room& operator = (const Room& ob);
            friend ostream& operator << (ostream&, const Room&);
    };

    const Room* room_realloc(const Room* arr, int prev_size, int size);
}

#endif