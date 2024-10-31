#include "../lib/singly_linked_list.h"

using namespace std;

int main() {
  SinglyLinkedList<int> sll;

  sll.display();

  sll.pushBack(1);
  sll.display();

  sll.push(2);
  sll.display();

  sll.pushBack(3);
  sll.display();

  sll.pushBack(4);
  sll.display();

  sll.push(5);
  sll.display();

  cout << "val 1: " << sll.getIndex(1) << "\n";
  cout << "val 0: " << sll.getIndex(0) << "\n";
  cout << "val 2: " << sll.getIndex(2) << "\n";

  sll.pop();
  sll.display();

  sll.popBack();
  sll.display();

  sll.pop();
  sll.display();

  sll.popBack();
  sll.display();

  return 0;
}
