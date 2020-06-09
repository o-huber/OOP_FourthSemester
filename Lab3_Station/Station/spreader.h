#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "car.h"
#include "storage.h"

// ��� ������������ (������ � ����������� � ��������)
class Spreader {
    using Types = std::vector<fuel_type>;

    Storage &st;            // ������ �� ���������, ������� �� �������� (������ ��� �� �����)
    Types fuel_types;       // ���� ������� �� ��������� ���� �������
    double filling_speed;   // ���������� ����������� �/�

    std::mutex m;           // ������� ��� �����������
    friend class Station;   // ��������� ������� ��� ��������
public:
    Spreader(Storage &st, const Types &types, double speed);
    Spreader(Spreader &&s) noexcept;

    const Types &get_types() const; // getter
    bool is_available();            // ���� �������� - �������� ������� � ������ ������� �������� ����
    void receive_fuel(Car &car);    // ��������� ������ car
private:
    void micro_receive(Car &car, fuel_type ft, double amount);  // ��� �������� ��������
};
