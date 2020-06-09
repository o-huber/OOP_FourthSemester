#include "price.h"

Price::Price(const Price::Table &price)
    : price(price) {}

const Price::Table &Price::get_price() const {
    return price;
}
