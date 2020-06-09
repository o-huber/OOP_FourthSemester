#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "fuel.h"

// класс описывающий обычную машину, которая приехала заправиться
class Car {
    std::string name;       // марка
    fuel_type type;         // тип топлива
    double tank_capacity;   // объём бака
    double fuel_amount;     // кол-во топлива

public:
    Car(const std::string &name, fuel_type type, double capacity, double amount);

    // getters
    const std::string &get_name() const;
    fuel_type get_fuel_type() const;
    double get_tank_capacity() const;
    double get_fuel_amount() const;

    // докидывает в бак топливо
    void add_fuel(double amount);
    friend std::ostream &operator<<(std::ostream &os, const Car &car);
};
