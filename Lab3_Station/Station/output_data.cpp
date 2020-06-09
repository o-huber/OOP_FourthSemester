#include "output_data.h"

OutputData::OutputData(Simulation &sm)
    : table(1, 1, samilton::Alignment::centre) {
    samilton::ConsoleTable::TableChars chars;
    chars.topDownSimple = '-';
    chars.leftSeparation = chars.rightSeparation = '|';
    chars.centreSeparation = chars.leftRightSimple = '|';
    chars.topLeft = chars.topRight = chars.topSeparation = '|';
    chars.downLeft = chars.downRight = chars.downSeparation = '|';
    table.setTableChars(chars);

    table[0][0] = "Прибуток";
    table[0][1] = "Втрачені гроші";
    table[1][0] = table[1][1] = "0";

    for (size_t i = 0; i < sm.st.spreaders.size(); ++i) {
        table[0][i + 2] = "Колонка " + std::to_string(i + 1);
    }
}

void OutputData::print(Simulation &sm) {
    table[1][0] = sm.st.cash;
    table[1][1] = sm.miss_cash;

    for (size_t i = 0; i < sm.st.spreaders.size(); ++i) {
        if (!sm.st.queues[i].first.empty()) {
            std::ostringstream iss;
            iss << sm.st.queues[i].first.front();
            table[1][i + 2] = iss.str();
        } else {
            table[1][i + 2].clear();
        }
    }
    std::cout << table << std::endl;
}
