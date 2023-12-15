#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <sstream>
#include "../address/address.h"
#include "../cottage/cottage.h"
#include "../living/living.h"
#include "../flat/flat.h"
#include "../apartment/apartment.h"
#include "../table/table.h"

using namespace Prog3;

TEST_CASE("Address"){
    SECTION("AddressConstructors"){
        Address a1("Street", 1, 2);
        REQUIRE(strcmp(a1.getStreet(), "Street") == 0);
        REQUIRE(a1.getBuilding() == 1);
        REQUIRE(a1.getFlat() == 2);

        Address a2(a1);
        REQUIRE(strcmp(a2.getStreet(), "Street") == 0);
        REQUIRE(a2.getBuilding() == 1);
        REQUIRE(a2.getFlat() == 2);

        Address a3(std::move(a2));
        REQUIRE(strcmp(a3.getStreet(), "Street") == 0);
        REQUIRE(a3.getBuilding() == 1);
        REQUIRE(a3.getFlat() == 2);
    }

    SECTION("AddressSetters"){
        Address a;
        a.setStreet("Street");
        a.setBuilding(1);
        a.setFlat(2);
        REQUIRE(strcmp(a.getStreet(), "Street") == 0);
        REQUIRE(a.getBuilding() == 1);
        REQUIRE(a.getFlat() == 2);
    }
}

TEST_CASE("Cottage"){
    SECTION("CottageConstructors"){
        unsigned int len;
        Cottage c1;
        REQUIRE(c1.getAddr() == nullptr);
        REQUIRE(c1.getLiving(len) == nullptr);
        REQUIRE(c1.getLen() == 0);

        Address* a = new Address("Street", 1, 2);
        Cottage c2(a);
        REQUIRE(strcmp(c2.getAddr()->getStreet(), "Street") == 0);
        REQUIRE(c2.getAddr()->getBuilding() == 1);
        REQUIRE(c2.getAddr()->getFlat() == 2);
        REQUIRE(c2.getLiving(len) == nullptr);
        REQUIRE(c2.getLen() == 0);

        Apartment* ap = new Apartment();
        Living** l = new Living*[1];
        l[0] = ap;
        Cottage c3(l, 1);
        REQUIRE(c3.getAddr() == nullptr);
        REQUIRE(c3.getLiving(len) == l);
        REQUIRE(c3.getLen() == 1);

        Cottage c4(c3);
        REQUIRE(c4.getAddr() == nullptr);
        REQUIRE(c4.getLen() == 1);
        
        Cottage c5(std::move(c3));
        REQUIRE(c5.getAddr() == nullptr);
        REQUIRE(c5.getLen() == 1);
    }
    SECTION("CottageSetters"){
        Apartment* ap = new Apartment();
        Living** l = new Living*[1];
        l[0] = ap;

        unsigned int len;
        Cottage c;
        c.setLiving(l, 1);
        c.setAddr("Street", 2);
        REQUIRE(strcmp(c.getAddr()->getStreet(), "Street") == 0);
        REQUIRE(c.getAddr()->getBuilding() == 2);
        REQUIRE(c.getAddr()->getFlat() == 0);
        REQUIRE(c.getLiving(len) == l);
        REQUIRE(c.getLen() == 1);

        Address* a = new Address("NewStreet", 3);
        c.setAddr(*a);
        REQUIRE(strcmp(c.getAddr()->getStreet(), "NewStreet") == 0);
        REQUIRE(c.getAddr()->getBuilding() == 3);
        REQUIRE(c.getAddr()->getFlat() == 0);
    }
    SECTION("CottageMethods"){
        unsigned int len;
        Room* arr = new Room[1];
        arr->setName("Bathroom");
        arr->setArea(12);

        Apartment* ap = new Apartment(nullptr, arr, 1);
        Living** l = new Living*[1];
        l[0] = ap;

        Cottage c(nullptr, l, 1);
        Room** rooms = c.getRooms(len);
        REQUIRE(strcmp(rooms[0]->getName(), "Bathroom") == 0);
        REQUIRE(c.getArea() == 12);
        delete[] rooms;
    }
}

TEST_CASE("Apartment"){
    SECTION("ApartmentConstructors"){
        Apartment a1;
        unsigned int len;
        REQUIRE(a1.getAddr() == nullptr);
        REQUIRE(a1.getRooms(len) == nullptr);
        REQUIRE(a1.getRoomsCount() == 0);

        Address* addr = new Address("Street", 1, 2);
        Room* rooms = new Room[1];
        rooms->setName("Bathroom");
        rooms->setArea(12);
        Apartment a2(addr, rooms, 1);
        REQUIRE(strcmp(a2.getAddr()->getStreet(), "Street") == 0);
        REQUIRE(a2.getAddr()->getBuilding() == 1);
        REQUIRE(a2.getAddr()->getFlat() == 2);
        REQUIRE(strcmp(a2.getRoom(0).getName(), "Bathroom") == 0);
        REQUIRE(a2.getRoom(0).getArea() == 12);
        REQUIRE(a2.getRooms(len) == rooms);
        REQUIRE(a2.getRoomsCount() == 1);

        Apartment a3(a2);
        REQUIRE(strcmp(a3.getAddr()->getStreet(), "Street") == 0);
        REQUIRE(a3.getAddr()->getBuilding() == 1);
        REQUIRE(a3.getAddr()->getFlat() == 2);
        REQUIRE(strcmp(a3.getRoom(0).getName(), "Bathroom") == 0);
        REQUIRE(a3.getRoom(0).getArea() == 12);
        REQUIRE(a3.getRoomsCount() == 1);

        Apartment a4(std::move(a3));
        REQUIRE(strcmp(a4.getAddr()->getStreet(), "Street") == 0);
        REQUIRE(a4.getAddr()->getBuilding() == 1);
        REQUIRE(a4.getAddr()->getFlat() == 2);
        REQUIRE(strcmp(a4.getRoom(0).getName(), "Bathroom") == 0);
        REQUIRE(a4.getRoom(0).getArea() == 12);
        REQUIRE(a4.getRoomsCount() == 1);
    }
    SECTION("ApartmentSetters"){
        Apartment a;
        Address* addr = new Address("Street", 1, 2);
        a.setFlat(2);
        REQUIRE(a.getAddr()->getFlat() == 2);
        a.setAddr(addr);
        REQUIRE(a.getAddr()->getFlat() == 2);
        REQUIRE(a.getAddr()->getBuilding() == 1);
        REQUIRE(strcmp(a.getAddr()->getStreet(), "Street") == 0);

        Room* rooms = new Room[1];
        rooms->setName("Bathroom");
        rooms->setArea(12);
        unsigned int len;
        a.setRooms(1, rooms);
        REQUIRE(strcmp(a.getRooms(len)[0].getName(), "Bathroom") == 0);
        REQUIRE(a.getRooms(len)[0].getArea() == 12);
        
        Room r("Toilet", 5);
        a.setRoom(0, r);
        REQUIRE(strcmp(a.getRooms(len)[0].getName(), "Toilet") == 0);
        REQUIRE(a.getRooms(len)[0].getArea() == 5);
    }
    SECTION("ApartmentMethods"){
        Room* rooms = new Room[1];
        rooms->setName("Bathroom");
        rooms->setArea(12);
        Apartment a(nullptr, rooms, 1);
        a.addRoom("Bedroom", 20);
        REQUIRE(strcmp(a.getRoom(1).getName(), "Bedroom") == 0);

        Room toilet("Toilet", 5);
        a.addRoom(toilet);
        REQUIRE(a.findRoom("Bathroom") == 0);
        REQUIRE(a.findRoom("Toilet") == 2);
        REQUIRE(a.getRoomsCount() == 3);
        REQUIRE(strcmp(a.getRoom(2).getName(), "Toilet") == 0);
        REQUIRE(a.getRoom(2).getArea() == 5);
    }
    SECTION("ApartmentExceptions"){
        Apartment a;
        Room r;
        REQUIRE_THROWS(a.setRoom(1, r));
        REQUIRE_THROWS(a.getRoom(1));
    }
}

TEST_CASE("Flat"){
    SECTION("FlatConstructors"){
        Flat f1;
        unsigned int len;
        REQUIRE(f1.getRooms(len)[0].getName() == nullptr);
        REQUIRE(f1.getRoomsCount() == 4);

        Address* addr = new Address("Street", 1, 2);
        Room* rooms = new Room[4];
        rooms[0] = Room("Bathroom", 10);
        rooms[1] = Room("Kitchen", 15);
        rooms[2] = Room("Living Room", 15);
        rooms[3] = Room("Bedroom", 20);
        Flat f2(addr, rooms);
        REQUIRE(strcmp(f2.getRooms(len)[1].getName(), "Kitchen") == 0);
        REQUIRE(f2.getRooms(len)[1].getArea() == 15);

        Flat f3(f2);
        REQUIRE(strcmp(f3.getRooms(len)[2].getName(), "Living Room") == 0);
        REQUIRE(f3.getRooms(len)[2].getArea() == 15);

        Flat f4(std::move(f3));
        REQUIRE(strcmp(f4.getRooms(len)[3].getName(), "Bedroom") == 0);
        REQUIRE(f4.getRooms(len)[3].getArea() == 20);
    }
    SECTION("FlatSetters"){
        Flat f;
        unsigned int len;
        Room bathroom("Bathroom", 10);
        f.setRoom(0, bathroom);
        REQUIRE(strcmp(f.getRooms(len)[0].getName(), "Bathroom") == 0);
        REQUIRE(f.getRooms(len)[0].getArea() == 10);

        Room* rooms = new Room[4];
        rooms[0] = Room("Bathroom", 10);
        rooms[1] = Room("Kitchen", 15);
        rooms[2] = Room("Living Room", 15);
        rooms[3] = Room("Bedroom", 20);
        f.setRooms(rooms);
        REQUIRE(strcmp(f.getRooms(len)[1].getName(), "Kitchen") == 0);
        REQUIRE(f.getRooms(len)[1].getArea() == 15);
    }
    SECTION("FlatMethods"){
        Address* addr = new Address("Street", 1, 2);
        Room* rooms = new Room[4];
        rooms[0] = Room("Bathroom", 10);
        rooms[1] = Room("Kitchen", 15);
        rooms[2] = Room("Living Room", 15);
        rooms[3] = Room("Bedroom", 20);
        Flat f(addr, rooms);
        REQUIRE(f.findRoom("Kitchen") == 1);
        REQUIRE(f.findRoom("Bedroom") == 3);
    }
    SECTION("FlatExceptions"){
        Flat f;
        Room r;
        REQUIRE_THROWS(f.setRoom(5, r));
        REQUIRE_THROWS(f.getRoom(5));
        REQUIRE_THROWS(f.findRoom("Room"));
    }
}

TEST_CASE("Room"){
    SECTION("RoomConstructors"){
        Room r1;
        REQUIRE(r1.getName() == nullptr);
        REQUIRE(r1.getComment() == nullptr);
        REQUIRE(r1.getArea() == 0);

        Room r2("Bathroom", 10);
        REQUIRE(strcmp(r2.getName(), "Bathroom") == 0);
        REQUIRE(r2.getArea() == 10);
        REQUIRE(r2.getComment() == nullptr);

        Room r3(r2);
        REQUIRE(strcmp(r3.getName(), "Bathroom") == 0);
        REQUIRE(r3.getArea() == 10);
        REQUIRE(r3.getComment() == nullptr);

        Room r4(std::move(r3));
        REQUIRE(strcmp(r4.getName(), "Bathroom") == 0);
        REQUIRE(r4.getArea() == 10);
        REQUIRE(r4.getComment() == nullptr);
    }
    SECTION("RoomSetters"){
        Room r;
        r.setName("Bathroom");
        r.setArea(15);
        r.setComment("Best bathroom in the world");
        REQUIRE(strcmp(r.getName(), "Bathroom") == 0);
        REQUIRE(strcmp(r.getComment(), "Best bathroom in the world") == 0);
        REQUIRE(r.getArea() == 15);
    }
}

TEST_CASE("Table"){
    SECTION("TableConstructors"){
        Table t1;
        REQUIRE(t1.getLen() == 0);

        Apartment* ap = new Apartment();
        Living** l = new Living*[1];
        l[0] = ap;
        int* status = new int[1]{1};
        int* prices = new int[1]{10000};
        Table t2(l, 1, status, prices);
        REQUIRE(t2.getLen() == 1);
        REQUIRE(t2.getLiving(0) == ap);
        REQUIRE(t2.getStatus(0) == 1);
        REQUIRE(t2.getPrice(0) == 10000);
        delete[] status;
        delete[] prices;
        delete[] l;
    }
    SECTION("TableSetters"){
        Table t;
        Apartment* ap = new Apartment();
        Living** l = new Living*[1];
        l[0] = ap;
        t.setLiving(l, 1);
        REQUIRE(t.getLen() == 1);
        REQUIRE(t.getLiving(0) == ap);
        REQUIRE(t.getStatus(0) == -1);
        REQUIRE(t.getPrice(0) == 0);

        t.setStatus(0, 0);
        t.setPrice(0, 5000);
        REQUIRE(t.getStatus(0) == 0);
        REQUIRE(t.getPrice(0) == 5000);
        delete[] l;
    }
    SECTION("TableMethods"){
        Apartment* ap = new Apartment();
        Living** l = new Living*[1];
        l[0] = ap;
        Table t(l, 1);
        Flat* f = new Flat();
        t.addLiving(f);
        REQUIRE(t.getLiving(1) == f);
        
        Address* addr = new Address("Street", 1, 2);
        t.addLiving(new Apartment(addr));
        REQUIRE(t.findLiving(*addr) == 2);

        t.removeLiving(1);
        REQUIRE(t.findLiving(*addr) == 1);
        delete[] l;
    }
    SECTION("TableExceptions"){
        Table t;
        Address a("Street", 1, 2);
        REQUIRE_THROWS(t.setStatus(0, -5));
        REQUIRE_THROWS(t.setStatus(1, 0));
        REQUIRE_THROWS(t.setPrice(1, 0));
        REQUIRE_THROWS(t.getLiving(1));
        REQUIRE_THROWS(t.getStatus(1));
        REQUIRE_THROWS(t.getPrice(1));
        REQUIRE_THROWS(t.findLiving(a));
        REQUIRE_THROWS(t.removeLiving(1));
    }
}