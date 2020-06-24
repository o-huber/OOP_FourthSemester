#pragma once

#include "MyList.h"
#include <string>
#include <sstream>
#include <stdexcept>

// ячейка связного списка
template <typename E>
struct node {
  // указатель на след ячейку
  node<E> *next;
  // данные
  E value;
  // конструктор
  node(E v) : value(v), next(NULL) {
  }
};

// список на основе связного списка,
//   реализует методы из MyList
template <typename E>
class MyLinkedList: public MyList<E> {
private:
  // указатели на ячейки голову и хвост списка
  node<E> *head, *tail;

public:
  // конструктор
  MyLinkedList() : MyList<E>() {
    // изначально элементов нет, а значит нет и головы с хвостом
    head = tail = NULL;
  }

  // метод для добавления нового элемента в список
  void add(E element) {
    // создаём новую ячейку
    node<E> *n = new node<E>(element);
    // если список пуст
    if (head == NULL) {
      // то эта ячейка становится и головой и хвостом
      head = tail = n;
      return;
    }
    // иначе добавляем её в хвост
    tail->next = n;
    tail = n;
  }

  // метод для получения элемента по индексу
  virtual E get(int index) {
    int i = 0;
    // идём по списку
    for (node<E> *t = head; t != NULL; t = t->next) {
      // пока i не будет равно нужному индексу
      if (i++ == index) {
        return t->value;
      }
    }

    // иначе был указан невалидный индекс,
    //   тогда бросаем исключение
    throw std::out_of_range("index");
  }

  // метод для удаления элемента по индексу
  E remove(int index) {
    // если головы нет, то список пуст и удалять нечего
    if (head == NULL) {
      throw std::out_of_range("index");
    }

    // если удаляем голову списка
    if (index == 0) {
      node<E> *t = head;
      head = head->next;
      E ret = t->value;
      delete t;
      if (head == NULL) {
        tail = NULL;
      }
      return ret;
    }

    // иначе идём до нужной ячейки
    node<E> *prev = head;
    int i = 1;
    for (node<E> *t = prev->next; t != NULL; t = t->next) {
      if (i++ == index) {
        prev->next = t->next;
        E ret = t->value;
        delete t;
        if (prev->next == NULL) {
          tail = prev;
        }
        return ret;
      }
      prev = t;
    }

    // если не нашли
    throw std::out_of_range("index");
  }

  // метод для получения размера списка
  size_t getSize() {
    // счётчик
    size_t ret = 0;
    // идём по списку и увеличиваем счётчик
    for (node<E> *t = head; t != NULL; t = t->next) {
      ret++;
    }
    return ret;
  }

  // метод для получения индекса элемента
  int indexOf(E element) {
    // счётчик
    int i = 0;
    // идём по списку
    for (node<E> *t = head; t != NULL; t = t->next) {
      // если нашли нужный элемент
      if (t->value == element) {
        return i;
      }
      i++;
    }
    // если не нашли
    return -1;
  }

  // метод для получения индекса первого элемента удовлетворяющего условие
  //   bool p(E) - указатель на функцию,
  //   которая будет проверять каждый элемент
  int indexOfFirst(bool (*p)(E)) {
    // счётчик
    int i = 0;
    // идём по списку
    for (node<E> *t = head; t != NULL; t = t->next) {
      // если нашли нужный элемент
      if (p(t->value)) {
        return i;
      }
      i++;
    }
    // если не нашли
    return -1;
  }

  // метод для получения строкового представления списка
  std::string toString() {
    // создаём поток
    std::stringstream ret;
    ret << "[";
    // идём по списку
    for (node<E> *t = head; t != NULL; t = t->next) {
      // и записываем в поток
      ret << t->value;
      if (t->next != NULL) {
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
    // идём по списку
    for (node<E> *t = head; t != NULL; t = t->next) {
      // вызываем функцию
      b(t->value);
    }
  }
};
