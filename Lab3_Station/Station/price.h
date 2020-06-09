#pragma once
#include <map>
#include "fuel.h"
#include "synchronized.h"

// ����������� ����� �� �������� � ������
class Price {
    // ����� �������� ��������� ����
    using Table = std::map<fuel_type, double>;

    Table price;  // ������� � ������ �� �������

public:
    Price(const Table &price);
    const Table &get_price() const;
};
