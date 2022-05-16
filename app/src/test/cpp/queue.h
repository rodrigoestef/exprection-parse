#include "../../main/headers/queue.h"
#include <cassert>

void testQueue() {

  Queue<int> *queue = new Queue<int>();
  queue->add(1);
  queue->add(2);
  queue->add(3);

  assert(queue->getNext() == 1);
  assert(queue->getNext() == 2);
  assert(queue->getNext() == 3);
  assert(queue->getNext() == 0);
}
