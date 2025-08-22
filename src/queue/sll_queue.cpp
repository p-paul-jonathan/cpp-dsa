#include "../../lib/singly_linked_list.h"

template <class T> class Queue : public SinglyLinkedList<T> {
public:
  void enqueue(T n) {
    this->pushBack(n);
  }

  T dequeue() {
    return this->pop();
  }

  T peek() {
    return this->head->data;
  }
};

int main() {
  Queue<int> q;

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(4);

  std::cout << q.peek() << "\n";
  std::cout << q.dequeue() << "\n";
  std::cout << q.dequeue() << "\n";

  q.enqueue(5);
  q.enqueue(6);

  q.display();

  return 0;
}
