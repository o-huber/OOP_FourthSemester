#pragma once
#include <algorithm>
#include <optional>
#include <queue>
#include <vector>

#include "car.h"
#include "fuel.h"
#include "price.h"
#include "spreader.h"
#include "storage.h"
#include "synchronized.h"
#include "thread_pool.h"

// заправка
class Station {
    Price price;            // цены
    Storage storage;        // резервуар
    double cash = 0.0;      // бабки в кассе

    // массив колонок на заправке
    std::vector<Spreader> spreaders;

    // массив очередей к колонкам (+ мьютекс для блокировки)
    std::vector<std::pair<std::queue<Car>, std::mutex>> queues;

    // одна здоровая очередь на подъезде к заправке
    std::queue<Car> queue_to_station;

    // это структура для удобного юзания потоков (рили без попаболи)
    ThreadPool workers;

    friend class Simulation;    // позволяем симуляции тут шариться
    friend struct OutputData;
public:
    Station(
        const std::map<fuel_type, double> &price,
        const std::map<fuel_type, double> &storage,
        const std::vector<std::pair<std::vector<fuel_type>, double>> &sps);

    // добавить клиента из общей очереди
    void add_client(const Car &car);

    // getter
    const std::map<fuel_type, double> &get_price_info() const;

    // тик симуляции
    void update();

    // reset state
    void refresh();
private:
    // считает стоимость заправки
    double calculate_price(fuel_type ft, double amount) const;

    // считает стоимость, выбирает колонку-очередь получше
    void manage_new_car();

    // выбирает лучшую колонку
    std::pair<std::queue<Car>, std::mutex> &get_better_queue(fuel_type ft);

    // проверяет, если есть незанятые колонки и машины в очереди
    // то запускает для них заправку
    void update_queues();
};
