#pragma once

#include "MyList.h"
#include <string>

// циклический список
template <typename E>
class MyCircularList: public MyList<E> {
private:
  // список, который оборачиваем
  MyList<E> *myList;
  // текущий индекс
  int current;

public:
  // конструктор
  MyCircularList(MyList<E> *t) : MyList<E>() {
    myList = t;
    current = 0;
  }

  // каждый раз возвращает следующий элемент, после последнего - первый
  E next() {
    return myList->get(current++ % myList->getSize());
  }

  // остальные методы проксируют внутренний список
  void add(E element)    {        myList->add(element);     }
  E get(int index)       { return myList->get(index);       }
  E remove(int index)    { return myList->remove(index);    }
  size_t getSize()       { return myList->getSize();        }
  int indexOf(E element) { return myList->indexOf(element); }
  std::string toString() { return myList->toString();       }

  void forEach(void (*b)(E)) { myList->forEach(b); }

  int indexOfFirst(bool (*p)(E)) { return myList->indexOfFirst(p); }
};
