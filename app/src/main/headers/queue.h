#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

template <typename T>

class QueueNode {
public:
  T value;
  QueueNode<T> *nextNode;
};

template <typename T>

class Queue {
public:
  T getNext() {

    if (this->queue == 0) {
      return 0;
    }
    T value = this->queue->value;

    this->queue = this->queue->nextNode;

    return value;
  }

  void add(T value) {

    QueueNode<T> *newItem = new QueueNode<T>;

    newItem->value = value;
    newItem->nextNode = 0;

    if (this->queue == 0) {
      this->queue = newItem;
      return;
    }

    QueueNode<T> *node = this->queue;
    while (true) {

      if (node->nextNode == 0) {
        node->nextNode = newItem;
        return;
      }
      node = node->nextNode;
    }
  }

private:
  QueueNode<T> *queue = 0;
};

#endif // !QUEUE_H
