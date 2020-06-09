#pragma once
#include <algorithm>
#include <chrono>
#include <map>
#include <thread>

#include "fuel.h"
#include "synchronized.h"

// резервуар с бензином на заправке
class Storage {
    using Tanks = std::map<fuel_type, double>;  // "псевдоним", чтобы проще код читался

    // Synchronized значит, что в многопотоке не сломается
    Synchronized<Tanks> storage{};  // основное хранилище
    Synchronized<Tanks> reserve{};  // вспомогательная переменная

public:
    Storage(const Tanks &st);
    double check_fuel(fuel_type ft) const;

    void reserve_fuel(fuel_type ft, double amount); // перемещает amount бензина ft из storage в reserve
    void receive_fuel(fuel_type ft, double amount); // уменьшает кол-во топлива в reserve при заправке авто
};
