#pragma once
#include <iostream>
#include <map>
#include <string>

// чтобы докинуть новый тип топлива достаточно 
// добавить его переменную в enum и текстовый вариант в map ниже

// различные типы топлива
enum class fuel_type {
    _72,
    _76,
    _80,
    _91,
    _92,
    _93,
    _95,
    _96,
    _98,
    _df,    // дизель
    _sz,    // size for loops
};

const inline std::map<fuel_type, std::string> fuel_names{
    {fuel_type::_72, "72"},
    {fuel_type::_76, "76"},
    {fuel_type::_80, "80"},
    {fuel_type::_91, "91"},
    {fuel_type::_92, "92"},
    {fuel_type::_93, "93"},
    {fuel_type::_95, "95"},
    {fuel_type::_96, "96"},
    {fuel_type::_98, "98"},
    {fuel_type::_df, "df"},
};

void print_all_types();
