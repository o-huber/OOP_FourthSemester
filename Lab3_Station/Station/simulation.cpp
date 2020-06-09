#include "simulation.h"

CarGenerator::CarGenerator(double mean, double deviation)
    : mt(std::chrono::system_clock::now().time_since_epoch().count())
    , nd(mean, deviation) {}

Car CarGenerator::generate() {
    return Car(
        names[mt() % names.size()],
        static_cast<fuel_type>(mt() % static_cast<int32_t>(fuel_type::_sz)),
        nd(mt),
        nd(mt) * urd(mt) / 3.33 + 1);
}

double CarGenerator::chance() {
    return urd(mt);
}

Simulation::Simulation(
    double probability,
    double mean,
    double deviation,
    const std::map<fuel_type, double>& price,
    const std::map<fuel_type, double>& storage,
    const std::vector<std::pair<std::vector<fuel_type>, double>>& sps)
    : car_probability(probability)
	, cg(mean, deviation)
    , st(price, storage, sps) {}

void Simulation::step() {
    if (cg.chance() < car_probability) {
        const auto car = cg.generate();

        if (st.storage.check_fuel(car.get_fuel_type())) {
            st.add_client(car);
        } else {
            miss_cash += st.calculate_price(car.get_fuel_type(), car.get_tank_capacity() - car.get_fuel_amount());
        }
    }
    st.update();
}

void Simulation::update() {
    st.update();
}

bool Simulation::have_cars() {
    return std::any_of(st.queues.begin(), st.queues.end(), [](const auto &p) {
        return !p.first.empty();
    });
}
