#pragma once
#include <sstream>
#include <string>
#include "CppConsoleTable.h"
#include "simulation.h"

struct OutputData {
    samilton::ConsoleTable table;

    explicit OutputData(Simulation &sm);
    void print(Simulation &sm);
};
