#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

template <typename T>

class QueueNode {
public:
  T value;
  QueueNode<T> *nextNode;
  QueueNode() { this->nextNode = 0; }
};

template <typename T>

class Queue {
public:
  T getNext() {

    if (this->first == 0) {
      return 0;
    }
    T value = this->first->value;

    this->first = this->first->nextNode;

    if (this->first == 0) {
      this->last = 0;
    }

    return value;
  }

  void add(T value) {

    QueueNode<T> *newItem = new QueueNode<T>;

    newItem->value = value;

    if (this->last == 0) {
      this->first = newItem;
      this->last = newItem;
      return;
    }

    this->last->nextNode = newItem;

    this->last = newItem;
  }

private:
  QueueNode<T> *first = 0;
  QueueNode<T> *last = 0;
};

#endif // !QUEUE_H
