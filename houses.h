#include <iostream>
#include <vector>
#include <memory>
#ifndef HOUSES_H
#define HOUSES_H

class BaseObject {
    public:
        BaseObject() =default;
        virtual const double get_area() const {return 0.0;}
        virtual ~BaseObject() =default;
};

class Room: public BaseObject {
    private:
        double area;
        std::string name;
        std::string comment = "";
    public:
        Room(std::string name, double area): name(name), area(area) {}
        Room(std::string name, double area, std::string comment): name(name), area(area), comment(comment) {}

        const std::string get_name() const {return name;}
        const double get_area() const override {return area;}
        const std::string get_comment() const {return comment;}

        virtual ~Room() =default;
};

class Building: public BaseObject {
    private:
        int number;
        int amount;
        std::vector<std::shared_ptr<BaseObject>> rooms;
    public:
        Building(int number, int amount, std::vector<std::shared_ptr<BaseObject>> rooms)
            :number(number), amount(amount), rooms(rooms) {}

        const int get_number() const {return number;}
        const int get_amount() const {return amount;}
        const std::vector<std::shared_ptr<BaseObject>> get_rooms() const {return rooms;}
        const double get_area() const override {
            double area = 0.0;
            for (int i = 0; i < rooms.size(); ++i)
                area += rooms[i]->get_area();
            return area;
        }

        virtual ~Building() =default;
};

class BaseAppartment {
    protected:
        int amount;
        std::string address;
        std::vector<std::shared_ptr<BaseObject>> objects;
    protected:
        BaseAppartment(std::string address, int amount, std::vector<std::shared_ptr<BaseObject>> objects)
            :address(address), amount(amount), objects(objects) {}
    public:
        const int get_amount() const {return amount;}
        const std::string get_address() const {return address;}
        const std::vector<std::shared_ptr<BaseObject>> get_objects() const {return objects;}
        virtual const std::string get_object_type() const {return std::string("");}
        const double get_area() const {
            double area = 0.0;
            for (int i = 0; i < objects.size(); ++i)
                area += objects[i]->get_area();

            return area;
        }

        friend std::ostream& operator <<(std::ostream& out, const BaseAppartment& appartment) {
            out << appartment.get_object_type() << " on \"" << appartment.get_address() << "\"\n";
            out << " * Area: " << appartment.get_area()  << "\n";
            out << " * Amount of rooms/buildings: " << appartment.get_amount() << "\n";

            return out;
        }

        virtual ~BaseAppartment() =default;
};

class Cottage: public BaseAppartment {
    public:
        Cottage(std::string address, int amount, std::vector<std::shared_ptr<BaseObject>> buildings)
            :BaseAppartment(address, amount, buildings) {}

        const std::string get_object_type() const override {return std::string("Cottage");}

        virtual ~Cottage() =default;
};

class Appartment: public BaseAppartment {
    public:
        Appartment(std::string address, int amount, std::vector<std::shared_ptr<BaseObject>> rooms)
            :BaseAppartment(address, amount, rooms) {}

        const std::string get_object_type() const override {return std::string("Appartment");}

        virtual ~Appartment() =default;
};

class Flat: public BaseAppartment {
    public:
        Flat(std::string address, std::vector<std::shared_ptr<BaseObject>> rooms)
            :BaseAppartment(address, 4, rooms) {}

        const std::string get_object_type() const override {return std::string("Flat");}

        virtual ~Flat() =default;
};
#endif //HOUSES_H