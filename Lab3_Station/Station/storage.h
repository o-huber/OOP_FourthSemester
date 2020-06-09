#pragma once
#include <algorithm>
#include <chrono>
#include <map>
#include <thread>

#include "fuel.h"
#include "synchronized.h"

// ��������� � �������� �� ��������
class Storage {
    using Tanks = std::map<fuel_type, double>;  // "���������", ����� ����� ��� �������

    // Synchronized ������, ��� � ����������� �� ���������
    Synchronized<Tanks> storage{};  // �������� ���������
    Synchronized<Tanks> reserve{};  // ��������������� ����������

public:
    Storage(const Tanks &st);
    double check_fuel(fuel_type ft) const;

    void reserve_fuel(fuel_type ft, double amount); // ���������� amount ������� ft �� storage � reserve
    void receive_fuel(fuel_type ft, double amount); // ��������� ���-�� ������� � reserve ��� �������� ����
};
