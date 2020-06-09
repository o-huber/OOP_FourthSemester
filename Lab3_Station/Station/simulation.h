#pragma once
#include <chrono>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "station.h"

// генерит машины по заданым параметрам
class CarGenerator {
    std::mt19937 mt;                        // generator of random numbers
    std::uniform_real_distribution<> urd;   // [0,1) new car chance
    std::normal_distribution<> nd;          // _---_ chances of fuel tank in cars generator
    std::vector<std::string> names = {"Audi", "BMW", "Ford", "Honda", "Hyundai", "Mercedes", "Nissan", "Porsche", "Renault", "Volkswagen",};
public:
    CarGenerator(double mean, double deviation);
    Car generate();
    double chance();
};

class Simulation {
    double car_probability;
    double miss_cash = 0.0;

    CarGenerator cg;
    Station st;

    friend struct OutputData;
public:
    Simulation(
        double probability,
        double mean,
        double deviation,
        const std::map<fuel_type, double>& price,
        const std::map<fuel_type, double>& storage,
        const std::vector<std::pair<std::vector<fuel_type>, double>>& sps);

    void step();
    void update();
    bool have_cars();
};
