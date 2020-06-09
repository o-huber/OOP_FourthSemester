#include "car.h"

Car::Car(const std::string &name, fuel_type type, double capacity, double amount)
    : name(name), type(type), tank_capacity(capacity), fuel_amount(amount) {}

const std::string &Car::get_name() const {
    return name;
}
fuel_type Car::get_fuel_type() const {
    return type;
}
double Car::get_tank_capacity() const {
    return tank_capacity;
}
double Car::get_fuel_amount() const {
    return fuel_amount;
}

void Car::add_fuel(double amount) {
    fuel_amount += amount;
}

std::ostream &operator<<(std::ostream &os, const Car &car) {
    return os << car.name << '\n' << car.fuel_amount << '\n' << car.tank_capacity;
}
