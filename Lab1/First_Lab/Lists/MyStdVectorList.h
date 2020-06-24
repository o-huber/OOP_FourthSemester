#pragma once

#include "MyList.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

// список на основе std::vector,
//   реализует методы из MyList
template <typename E>
class MyStdVectorList: public MyList<E> {
private:
  // вектор элементов
  std::vector<E> arr;

public:
  // конструктор
  MyStdVectorList() : MyList<E>() {
  }

  // метод для добавления нового элемента в список
  void add(E element) {
    arr.push_back(element);
  }

  // метод для получения элемента по индексу
  E get(int index) {
    return arr[index];
  }

  // метод для удаления элемента по индексу
  E remove(int index) {
    E ret = arr[index];
    arr.erase(arr.begin() + index);
    return ret;
  }

  // метод для получения размера списка
  size_t getSize() {
    return arr.size();
  }

  // метод для получения индекса элемента
  int indexOf(E element) {
    // идём по вектору
    for (int i = 0; i < arr.size(); i++) {
      // если нашли нужный элемент
      if (arr[i] == element) {
        return i;
      }
    }
    // если не нашли
    return -1;
  }

  // метод для получения индекса первого элемента удовлетворяющего условие
  //   bool p(E) - указатель на функцию,
  //   которая будет проверять каждый элемент
  int indexOfFirst(bool (*p)(E)) {
    // идём по вектору
    for (int i = 0; i < arr.size(); i++) {
      // если нашли нужный элемент
      if (p(arr[i])) {
        return i;
      }
    }
    // если не нашли
    return -1;
  }

  // метод для получения строкового представления списка
  std::string toString() {
    // создаём поток
    std::stringstream ret;
    ret << "[";
    // идём по вектору
    for (int i = 0; i < arr.size(); i++) {
      // и записываем в поток
      ret << arr[i];
      if (i != arr.size() - 1) {
        ret << ", ";
      }
    }
    ret << "]";
    // возвращаем поток как строку
    return ret.str();
  }


  // метод для последовательного прохождения по всем элементам списка
  //   void b(E) - указатель на функцию,
  //   которая будет вызываться для каждого элемента
  void forEach(void (*b)(E)) {
    // идём по массиву
    for (int i = 0; i < arr.size(); i++) {
      // вызываем функцию
      b(arr[i]);
    }
  }
};
