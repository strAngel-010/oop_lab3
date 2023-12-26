#include "room.h"

namespace Prog3{
    Room::Room(const char* name, unsigned int area, char* comment){
        try {
            int len = std::strlen(name);
            this->name = new char[len+1];
            std::copy(name, name+len+1, this->name);

            if (comment){
                len = std::strlen(comment);
                this->comment = new char[len+1];
                std::copy(comment, comment+len+1, this->comment);
            }
            this->area = area;
        } catch(...){ throw; }
    }

    Room::Room(const Room& ob) : name(nullptr), area(0), comment(nullptr) {
        try {
            int len = std::strlen(ob.name);
            name = new char[len + 1];
            std::copy(ob.name, ob.name + len + 1, name);

            if (comment){
                len = std::strlen(ob.comment);
                comment = new char[len + 1];
                std::copy(ob.comment, ob.comment + len + 1, comment);
            }
            area = ob.area;
        } catch (...){ throw; }
    }

    Room::Room(Room&& ob) noexcept : name(ob.name), area(ob.area), comment(ob.comment) {
        ob.name = nullptr;
        ob.area = 0;
        ob.comment = nullptr;
    }

    Room::~Room(){
        if (name){ delete[] name; }
        name = nullptr;
        area = 0;
        if (comment){ delete[] comment; }
        comment = nullptr;
    }

    Room &Room::setName(const char* name){
        try {
            int len = std::strlen(name);
            if (this->name){ delete[] this->name; }
            this->name = new char[len+1];
            std::copy(name, name+len+1, this->name);
        } catch(...){ throw; }
        return *this;
    }

    Room &Room::setComment(const char* comment){
        try {
            int len = std::strlen(comment);
            if (this->comment){ delete[] this->comment; }
            this->comment = new char[len+1];
            std::copy(comment, comment+len+1, this->comment);
        } catch(...){ throw; }
        return *this;
    }

    Room &Room::setArea(unsigned int area) noexcept {
        this->area = area;
        return *this;
    }

    Room& Room::operator = (const Room& ob){
        try {
            if (name) { delete[] name; }
            name = nullptr;
            if (ob.name) {
                int len = std::strlen(ob.name);
                name = new char[len + 1]; 
                std::copy(ob.name, ob.name + len + 1, name);
            }
            area = ob.area;
            if (comment) { delete[] comment; }
            comment = nullptr;
            if (ob.comment) {
                int len = std::strlen(ob.comment);
                comment = new char[len + 1]; 
                std::copy(ob.comment, ob.comment + len + 1, comment);
            }
        } catch (...) { throw; }
        return *this;
    }

    ostream& operator << (ostream& s, const Room& room){
        if (room.getName()) { s << room.getName() << "; "; }
        if (room.getArea()) { s << "Area: " << room.getArea() << "; "; }
        if (room.getComment()) { s << "Comment: " << room.getComment() << "; "; }
        return s;
    }

    istream& operator >> (istream& s, Room& room){
        std::string name;
        int func_res = input_string(s, "Enter name:", name);
        if (func_res) { return s; }

        int area;
        func_res = input_num(s, "Enter area:", 1, std::numeric_limits<int>::max(), area);
        if (func_res) { return s; }

        std::string comment;
        func_res = input_string(s, "Enter comment or 'E' to leave it empty:", comment);
        if (func_res) { return s; }
        if (comment == "E") { comment.erase(); }

        try { 
            if (!comment.empty()) { room = Room((char*)name.c_str(), area, (char*)comment.c_str()); }
            else { room = Room((char*)name.c_str(), area); }
        }
        catch (...) { throw; }
        return s;
    }
}