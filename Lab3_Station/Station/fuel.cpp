#include "fuel.h"

void print_all_types() {
    for (const auto& [type, name] : fuel_names)
        std::cout << static_cast<int>(type) << ':' << name << ' ';
    std::cout << std::endl;
}
