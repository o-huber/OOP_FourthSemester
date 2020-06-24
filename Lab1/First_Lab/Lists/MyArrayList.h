#pragma once

#include "MyList.h"
#include <string>
#include <sstream>
#include <stdexcept>

// список на основе массива,
//   реализует методы из MyList
template <typename E>
class MyArrayList: public MyList<E> {
private:
  // массив элементов
  E *arr;
  // размер самого массива
  size_t capacity;
  // кол-во элементов в массиве
  size_t size;

  // метод для увеличения размера массива
  void grow() {
    // новый размер будет на 16 больше
    size_t newCap = capacity + 16;
    // создаём новый массив
    E *newArr = new E[newCap];
    // если был старый массив
    if (arr != NULL) {
      // копируем элементы из него в новый
      for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
      }
      // и удаляем
      delete arr;
    }
    // обновляем размер и массив
    capacity = newCap;
    arr = newArr;
  }

public:
  // конструктор
  MyArrayList() : MyList<E>() {
    arr = NULL;
    size = capacity = 0;
    grow();
  }

  // метод для добавления нового элемента в список
  void add(E element) {
    // если массив полон - увеличиваем
    if (size == capacity) grow();
    // добавляем элемент
    arr[size++] = element;
  }

  // метод для получения элемента по индексу
  E get(int index) {
    // если индекс невалидный
    if (index < 0 || index >= size) {
      // кидаем исключение
      throw std::out_of_range("index");
    }
    // возвращаем элемент
    return arr[index];
  }

  // метод для удаления элемента по индексу
  E remove(int index) {
    // если индекс невалидный
    if (index < 0 || index >= size) {
      // кидаем исключение
      throw std::out_of_range("index");
    }
    // сохраняем элемент чтобы потом вернуть
    E ret = arr[index];
    // уменьшаем размер
    size--;
    // сдвигаем элементы в массиве
    for (int i = 0; i < (size - index); i++) {
      arr[index + i] = arr[index + i + 1];
    }
    // возвращаем
    return ret;
  }

  // метод для получения размера списка
  size_t getSize() {
    return size;
  }

  // метод для получения индекса элемента
  int indexOf(E element) {
    // идём по массиву
    for (int i = 0; i < size; i++) {
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
    // идём по массиву
    for (int i = 0; i < size; i++) {
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
    // идём по массиву
    for (int i = 0; i < size; i++) {
      // и записываем в поток
      ret << arr[i];
      if (i != size - 1) {
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
    for (int i = 0; i < size; i++) {
      // вызываем функцию
      b(arr[i]);
    }
  }
};
