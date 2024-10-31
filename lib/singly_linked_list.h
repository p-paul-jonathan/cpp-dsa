#include <cstddef>
#include <iostream>
#include <stdexcept>

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
    if(length == 0) { throw std::runtime_error("empty"); }

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
    if(length == 0) { throw std::runtime_error("empty"); }

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
    if(index >= length) { throw std::invalid_argument("out of range"); }

    Node<T> *itr = head;

    for(int i = 0; i < index; i++) {
      itr = itr->next;
    }

    return itr->data;
  }

  void display() {
    Node<T> *itr = head;
    std::cout << "{ length: " << length << " } ";
    std::cout << "[ ";

    for(int i = 0; i < length; i++) {
      std::cout << itr->data << " ";
      itr = itr->next;
    }

    std::cout << "]\n";
  }

  int getLength() { return length; }

protected:
  Node<T> *head, *tail;
  int length;
};
