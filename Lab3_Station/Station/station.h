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

// ��������
class Station {
    Price price;            // ����
    Storage storage;        // ���������
    double cash = 0.0;      // ����� � �����

    // ������ ������� �� ��������
    std::vector<Spreader> spreaders;

    // ������ �������� � �������� (+ ������� ��� ����������)
    std::vector<std::pair<std::queue<Car>, std::mutex>> queues;

    // ���� �������� ������� �� �������� � ��������
    std::queue<Car> queue_to_station;

    // ��� ��������� ��� �������� ������ ������� (���� ��� ��������)
    ThreadPool workers;

    friend class Simulation;    // ��������� ��������� ��� ��������
    friend struct OutputData;
public:
    Station(
        const std::map<fuel_type, double> &price,
        const std::map<fuel_type, double> &storage,
        const std::vector<std::pair<std::vector<fuel_type>, double>> &sps);

    // �������� ������� �� ����� �������
    void add_client(const Car &car);

    // getter
    const std::map<fuel_type, double> &get_price_info() const;

    // ��� ���������
    void update();

    // reset state
    void refresh();
private:
    // ������� ��������� ��������
    double calculate_price(fuel_type ft, double amount) const;

    // ������� ���������, �������� �������-������� �������
    void manage_new_car();

    // �������� ������ �������
    std::pair<std::queue<Car>, std::mutex> &get_better_queue(fuel_type ft);

    // ���������, ���� ���� ��������� ������� � ������ � �������
    // �� ��������� ��� ��� ��������
    void update_queues();
};
