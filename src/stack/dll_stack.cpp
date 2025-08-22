#include "../../lib/doubly_linked_list.h"

template <class T> class Stack : public DoublyLinkedList<T> {
public:
  T peek() {
    if (this->length == 0) {
      throw std::runtime_error("empty");
    }

    return this->head->data;
  }
};

int main() {
  Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);

  std::cout << s.peek() << "\n";
  std::cout << s.pop() << "\n";

  s.push(6);

  std::cout << s.peek() << "\n";

  s.display();

  return 0;
}
