#include "../lib/doubly_linked_list.h"

int main() {
  DoublyLinkedList<int> dll;

  dll.display();

  dll.pushBack(1);
  dll.display();

  dll.push(2);
  dll.display();

  dll.pushBack(3);
  dll.display();

  dll.pushBack(4);
  dll.display();

  dll.push(5);
  dll.display();

  std::cout << "val 1: " << dll.getIndex(1) << "\n";
  std::cout << "val 0: " << dll.getIndex(0) << "\n";
  std::cout << "val 2: " << dll.getIndex(2) << "\n";

  dll.pop();
  dll.display();

  dll.popBack();
  dll.display();

  dll.pop();
  dll.display();

  dll.popBack();
  dll.display();

  return 0;
}
