#include <cstddef>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
struct Node {
  T data;
  Node *next;
};

template <class T>
class SinglyLinkedList {
  public:
    SinglyLinkedList() {
      head = nullptr;
      tail = nullptr;
      length = 0;
    }

    void pushBack(T value) {
      Node<T> *node = new Node<T>;
      node->data = value;
      node->next = nullptr;

      length++;

      if(tail == nullptr) {
        tail = node;
        head = node;
      } else {
        tail->next = node;
        tail = node;
      }
    }

    T popBack() {
      Node<T> *itr = head, *node = tail;
      T value = node->data;

      length--;

      while(itr->next != tail) { itr = itr->next; }

      tail = itr;
      itr->next = nullptr;

      delete node;

      return value;
    }

    void push(T value) {
      Node<T> *node = new Node<T>;
      node->data = value;
      node->next = head;
      length++;

      head = node;
      if(tail == nullptr) { tail = node; }
    }

    T pop() {
      if(length == 0) { throw runtime_error("empty"); }

      Node<T> *node = head;
      T value = node->data;

      length--;

      head = head->next;
      node->next = nullptr;

      if(head == nullptr) { tail = nullptr; }

      delete node;
      return value;
    }

    T getIndex(int index) {
      if(index >= length) { throw invalid_argument("out of range"); }

      Node<T> *itr = head;

      for(int i = 0; i < index; i++) {
        itr = itr->next;
      }

      return itr->data;
    }

    void display() {
      Node<T> *itr = head;
      cout << "{ length: " << length << " } ";
      cout << "[ ";

      for(int i = 0; i < length; i++) {
        cout << itr->data << " ";
        itr = itr->next;
      }

      cout << "]\n";
    }

    int getLength() { return length; }
  private:
    Node<T> *head, *tail;
    int length;
};

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
