#include "station.h"

Station::Station(
    const std::map<fuel_type, double> &price,
    const std::map<fuel_type, double> &storage,
    const std::vector<std::pair<std::vector<fuel_type>, double>> &sps)
    : price(price)
    , storage(storage)
    , queues(sps.size())
    , workers(sps.size())
{
    for (const auto &[types, speed] : sps)
        spreaders.emplace_back(this->storage, types, speed);
}

// машина добавляется в очередь, если есть её топливо
void Station::add_client(const Car &car) {
    queue_to_station.push(car);
}

// имитация табло на заправке
const std::map<fuel_type, double> &Station::get_price_info() const {
    return price.get_price();
}

// тик работы заправки в основном потоке
void Station::update() {
    manage_new_car();
    update_queues();
}

// обновляет состояние заправки
void Station::refresh() {
    while (!queue_to_station.empty())
        queue_to_station.pop();

    for (size_t i = 0; i < spreaders.size(); ++i) {
        if (auto &q = queues[i].first; !q.empty()) {
            // поменяешь порядок захвата мьютексов и прога зависнет
            std::lock_guard<std::mutex> lgs(spreaders[i].m);
            std::lock_guard<std::mutex> lgq(queues[i].second);

            // защитили данные и удаляем всё к чертям
            while (!q.empty())
                q.pop();
        }
    }
}

double Station::calculate_price(fuel_type ft, double amount) const {
    return price.get_price().at(ft) * amount;
}

std::atomic_int32_t count1, count2;
inline std::mutex cout_m;

void Station::manage_new_car() {
    while (!queue_to_station.empty()) {
        auto car = std::move(queue_to_station.front());
        queue_to_station.pop();

        // make price
        double fuel_amount = car.get_tank_capacity() - car.get_fuel_amount();
        cash += calculate_price(car.get_fuel_type(), fuel_amount);

        // choose good queue
        auto &q = get_better_queue(car.get_fuel_type());
        std::lock_guard<std::mutex> lg(q.second);
        q.first.push(std::move(car));
    }
}

std::pair<std::queue<Car>, std::mutex> &Station::get_better_queue(fuel_type ft) {
    std::vector<std::pair<std::reference_wrapper<Spreader>, std::reference_wrapper<std::pair<std::queue<Car>, std::mutex>>>> v;

    for (size_t i = 0; i < spreaders.size(); ++i)
        v.emplace_back(std::ref(spreaders[i]), std::ref(queues[i]));

    v.erase(std::remove_if(v.begin(), v.end(), [ft](const auto &p) {
        const auto &types = p.first.get().get_types();
        return std::none_of(types.begin(), types.end(), [ft](auto t) {
            return t != ft;
        });
    }), v.end());

    std::nth_element(v.begin(), v.begin(), v.end(), [](const auto &p1, const auto &p2) {
        return p1.second.get().first.size() < p2.second.get().first.size();
    });

    return v.front().second.get();
}

void Station::update_queues() {
    for (size_t i = 0; i < spreaders.size(); ++i) {
        if (!queues[i].first.empty() && spreaders[i].is_available()) {
            auto s = std::ref(spreaders[i]);
            auto q = std::ref(queues[i]);

            workers.add_task([s, q] {
                s.get().receive_fuel(q.get().first.front());
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::lock_guard<std::mutex> lg(q.get().second);
                q.get().first.pop();
            });
        }
    }
}
