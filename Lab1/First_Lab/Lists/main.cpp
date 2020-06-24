#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MyList.h"
#include "MyLinkedList.h"
#include "MyArrayList.h"
#include "MyStdVectorList.h"
#include "MyCircularList.h"

using namespace std;

int main() {
  cout << "hello world" << endl;

  // чтобы правильно работал рандом
  srand(time(NULL));

  // объявляем указатель для списка
  //   тип - общий родительский класс,
  //   чтобы можно было присвоить любую реализацию
  MyList<string> *myList;

  // создаём список строк на основе связного списка
  myList = new MyLinkedList<string>;
  // добавляем пару строк
  myList->add("hello");
  myList->add("world");
  // выводим список
  cout << myList->toString() << endl;

  cout << endl;

  // создаём список строк на основе массива
  myList = new MyArrayList<string>;
  // добавляем пару строк
  myList->add("foo");
  myList->add("bar");
  myList->add("baz");
  // выводим список
  cout << myList->toString() << endl;

  cout << endl;

  // создаём список строк на основе вектора (std::vector)
  myList = new MyStdVectorList<string>;
  // добавляем пару строк
  myList->add("qwe");
  myList->add("asdf");
  myList->add("zxc");
  myList->add("hjkl");
  // выводим список
  cout << myList->toString() << endl;
  // ищем и выводим индекс первой строки с длиной > 3 символов
  cout << "  .get .indexOfFirst(.length() > 3): ";
  cout << myList->get(myList->indexOfFirst([](string a) {
    return a.length() > 3;
  })) << endl;

  cout << endl;

  // создаём циклический список "поверх" предыдущего списка (на основе вектора)
  MyCircularList<string> *myCircularList =
    new MyCircularList<string>(myList);
  cout << "myCircularList" << endl;
  for (int i = 0; i < 5; i++) {
    // у него есть метод .next() который каждый раз возвращает
    //   следующий элемент, после последнего - первый
    cout << "  .next() = " << myCircularList->next() << endl;
  }

  cout << endl;

  // создаём список целый чисел
  MyList<int> *myList2 = new MyStdVectorList<int>();
  // заполняем его 15ью рандомными числами от 10 до 99
  myList2->fill(15, [] { return 10 + rand() % 90; });
  // выводим его
  cout << "random:" << endl << myList2->toString() << endl;

  return 0;
}
