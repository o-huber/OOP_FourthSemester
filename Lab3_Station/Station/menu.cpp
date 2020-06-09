#include "menu.h"
#include "output_data.h"

std::vector<fuel_type> split(std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> splited(std::istream_iterator<std::string>(iss), {});
    std::vector<fuel_type> types;

    for (auto& i : splited)
        types.push_back(static_cast<fuel_type>(std::stoi(i)));
    return types;
}

Simulation init_menu() {
    std::cout << "�������� ��������� ������ �������� �������" << std::endl;

    std::cout << "������ ��������� ����� ������ ���� � ���� �� ������� � ����� �������: ";
    double probability;
    std::cin >> probability;

    std::cout << std::endl << "�� ����� ������ ������� ��� ���� ��������: ";
    print_all_types();

    std::cout << "������ ����� ����� �������� ������ ����, �� ������ ������� �� ��������: ";
    std::string types;
    std::cin.get();
    std::getline(std::cin, types);
    auto splited = split(types);

    std::cout << "������ ���� �� ����� ��� �������:" << std::endl;
    std::map<fuel_type, double> price;

    for (auto [type, name] : fuel_names) {
        std::cout << name << ": ";
        std::cin >> price[type];
    }

    std::cout << "������ �������� ������� ������� ���� ������� �� ��������:" << std::endl;
    std::map<fuel_type, double> storage;

    for (auto type : splited) {
        std::cout << fuel_names.at(type) << ": ";
        std::cin >> storage[type];
    }

    std::cout << "������ ������� ������� �� ��������: ";
    size_t spreaders_amount;
    std::cin >> spreaders_amount;

    std::cout << "������ �� ���� ������� ������ �� ����� �������, �� ��������� �������� �������� �� ����� �������:" << std::endl;
    std::vector<std::pair<std::vector<fuel_type>, double>> spreaders(spreaders_amount, { {}, 0.0 });

    std::cout << "�� ����� ������ ������� ��� ���� ��������: ";
    for (auto i : splited)
        std::cout << static_cast<int>(i) << ':' << fuel_names.at(i) << ' ';
    std::cout << std::endl;

    for (auto& [types, speed] : spreaders) {
        std::cout << std::endl << "������ ����� ����� �������� ������ ����, �� ������ ������� �� �������: ";
        std::string sp_types;
        std::cin.get();
        std::getline(std::cin, sp_types);
        types = split(sp_types);

        std::cout << "������ ��������� �������� �������� ����/��� �� ��� �������: ";
        std::cin >> speed;
    }
    std::cout << std::endl;

    double mean, deviation;
    std::cout << "������ ��������� ����������� �������� ��'��� ��������� � ������, �� ���������� �����������." << std::endl;
    std::cout << "������ ����������� ��������� (������ �������� ��'���): ";
    std::cin >> mean;
    std::cout << "������ �������� (��������� �� ��������� ��������): ";
    std::cin >> deviation;

    return Simulation(probability, mean, deviation, price, storage, spreaders);
}

void loop_menu(Simulation& sm) {
    bool exit_status = false;
    OutputData od(sm);

    while (!exit_status) {
        while (!_kbhit()) {
            for (size_t i = 0; i < 10; ++i)
                sm.step();

            std::this_thread::sleep_for(std::chrono::seconds(1));
            system("cls");
            od.print(sm);
        }

        if (_getch() == 27) // escape key
            exit_status = true;
    }
	while (sm.have_cars()) {
        for (size_t i = 0; i < 10; ++i)
            sm.update();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
        od.print(sm);
	}
}
