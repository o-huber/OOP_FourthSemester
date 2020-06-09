#include "spreader.h"
#include "simulation.h"

Spreader::Spreader(Storage &st, const Types &types, double speed)
    : st(st), fuel_types(types), filling_speed(speed) {}

Spreader::Spreader(Spreader &&s) noexcept
    : st(s.st), fuel_types(std::move(s.fuel_types)), filling_speed(s.filling_speed) {}

const Spreader::Types &Spreader::get_types() const {
    return fuel_types;
}

bool Spreader::is_available() {
    return m.try_lock();
}

void Spreader::receive_fuel(Car &car) {
    fuel_type ft = car.get_fuel_type();
    double amount = car.get_tank_capacity() - car.get_fuel_amount();

    st.reserve_fuel(ft, amount);
    for (; amount > filling_speed; amount -= filling_speed)
        micro_receive(car, ft, filling_speed);
    micro_receive(car, ft, amount);

    // unlock after is_available()
    m.unlock();
}

void Spreader::micro_receive(Car &car, fuel_type ft, double amount) {
	std::this_thread::sleep_for(std::chrono::seconds(1));   // 1 sec in slowest mode
    st.receive_fuel(ft, amount);
    car.add_fuel(amount);
}
