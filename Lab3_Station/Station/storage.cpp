#include "storage.h"
#include "simulation.h"

Storage::Storage(const Tanks &st)
    : storage(st) {}

double Storage::check_fuel(fuel_type ft) const {
    const auto &access = storage.get();
    return access.ref().count(ft) ? access.ref().at(ft) : 0.0;
}

void Storage::reserve_fuel(fuel_type ft, double amount) {
    storage.get().ref()[ft] -= amount;
    reserve.get().ref()[ft] += amount;
}

void Storage::receive_fuel(fuel_type ft, double amount) {
    reserve.get().ref()[ft] -= amount;
}
