#include <iostream>

#include "DateTime.h"

using namespace std;

int main() {
  cout << "hello world" << endl;

  // дни и месяцы начинаются с 0
  DateTime today(2019, 11, 02, 12, 00, 00);

  DateTime new_year(2020, 00, 00, 00, 00, 00);

  cout << "days until 2020: ";
  unsigned d = DateTime::diff(today, new_year, TimeUnit::DAYS);
  cout << d << endl;

  cout << "today is ";
  cout << DateTime::dayOfWeekToString(today.dayOfWeek()) << endl;

  cout << "2020-01-01 will be ";
  cout << DateTime::dayOfWeekToString(new_year.dayOfWeek()) << endl;

  return 0;
}
