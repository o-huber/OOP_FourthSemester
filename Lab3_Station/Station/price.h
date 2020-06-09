#pragma once
#include <map>
#include "fuel.h"
#include "synchronized.h"

// здоровенное табло на заправке с ценами
class Price {
    // снова упростил написание кода
    using Table = std::map<fuel_type, double>;

    Table price;  // таблица с ценами на топливо

public:
    Price(const Table &price);
    const Table &get_price() const;
};
