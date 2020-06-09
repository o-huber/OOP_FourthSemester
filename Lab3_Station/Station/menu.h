#pragma once
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "fuel.h"
#include "simulation.h"

std::vector<fuel_type> split(std::string& str);
Simulation init_menu();
void loop_menu(Simulation& sm);
