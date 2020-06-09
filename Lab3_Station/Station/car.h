#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "fuel.h"

// ����� ����������� ������� ������, ������� �������� �����������
class Car {
    std::string name;       // �����
    fuel_type type;         // ��� �������
    double tank_capacity;   // ����� ����
    double fuel_amount;     // ���-�� �������

public:
    Car(const std::string &name, fuel_type type, double capacity, double amount);

    // getters
    const std::string &get_name() const;
    fuel_type get_fuel_type() const;
    double get_tank_capacity() const;
    double get_fuel_amount() const;

    // ���������� � ��� �������
    void add_fuel(double amount);
    friend std::ostream &operator<<(std::ostream &os, const Car &car);
};
