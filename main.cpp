#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "libs/houses.h"
#include "libs/table.h"

int main() {
    std::vector<std::shared_ptr<BaseObject>> rooms_1;
    rooms_1.push_back(std::make_shared<Room> (std::string("Living room"), 12.5, std::string("The best living room")));
    rooms_1.push_back(std::make_shared<Room> (std::string("Kitchen"), 10));
    rooms_1.push_back(std::make_shared<Room> (std::string("Bedroom"), 13, std::string("Big bed")));

    std::vector<std::shared_ptr<BaseObject>> rooms_2;
    rooms_2.push_back(std::make_shared<Room> (std::string("Living room"), 20, std::string("Big living room")));
    rooms_2.push_back(std::make_shared<Room> (std::string("Kitchen"), 15, std::string("Modern kitchen")));
    rooms_2.push_back(std::make_shared<Room> (std::string("Bedroom"), 14, std::string("Big TV")));
    rooms_2.push_back(std::make_shared<Room> (std::string("Hallway"), 10, std::string("Big hallway")));
    

    std::vector<std::shared_ptr<BaseObject>> buildings;
    buildings.push_back(std::make_shared<Building> (1, 3, rooms_1));
    buildings.push_back(std::make_shared<Building> (2, 4, rooms_2));

    std::shared_ptr<Cottage> c = std::make_shared<Cottage> (std::string("some street 12"), 2, buildings);
    std::shared_ptr<Flat> f = std::make_shared<Flat> (std::string("some street 13"), rooms_2);
    std::shared_ptr<Appartment> a = std::make_shared<Appartment> (std::string("some street 14"), 3, rooms_1);

    Shelter s1 = {true, 100, c};
    Shelter s2 = {false, 200, f};
    Shelter s3 = {true, 50, a};

    Table<Shelter> t;
    t.add(s1);
    t.add(s2);
    t.add(s3);

    std::cout << "Printing whole table:\n";
    t.print();

    std::cout << "\nFinding shelter by address \"some street 13\":\n";
    t.find_by_address(std::string("some street 13"));

    std::cout << "\nFinding shelter by address \"some street 15\":\n";
    t.find_by_address(std::string("some street 15"));
}