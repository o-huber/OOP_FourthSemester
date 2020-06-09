#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "car.h"
#include "storage.h"

// это бензоколонка (стойка с пистолетами и шлангами)
class Spreader {
    using Types = std::vector<fuel_type>;

    Storage &st;            // ссылка на резервуар, который на заправке (всегда тот же будет)
    Types fuel_types;       // типы топлива на конкретно этой колонке
    double filling_speed;   // пропускная способность л/с

    std::mutex m;           // мьютекс для многопотока
    friend class Station;   // позволяем станции тут шариться
public:
    Spreader(Storage &st, const Types &types, double speed);
    Spreader(Spreader &&s) noexcept;

    const Types &get_types() const; // getter
    bool is_available();            // если свободен - заблочит мьютекс и начнет процесс заправки авто
    void receive_fuel(Car &car);    // заправить машину car
private:
    void micro_receive(Car &car, fuel_type ft, double amount);  // тик процесса заправки
};
