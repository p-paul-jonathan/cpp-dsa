#include <cstddef>
#include <iostream>
#include <stdexcept>

template <class T>
struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <class T>
class DoublyLinkedList {
public:
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
  }

  void pushBack(int value) {
    Node<T> *node = new Node<T>;
    node->data = value;
    node->next = nullptr;
    node->prev = tail;

    length++;

    if(tail != nullptr) { tail->next = node; }
    tail = node;
    if(head == nullptr) { head = node; }
  }

  T popBack() {
    if(length == 0) { throw std::runtime_error("empty"); }

    Node<T> *node = tail;
    T value = node->data;

    length--;

    tail = tail->prev;
    node->prev = nullptr;

    if(tail == nullptr) {
      head = nullptr;
    } else {
      tail->next = nullptr;
    }

    delete node;
    return value;
  }

  void push(int value){
    Node<T> *node = new Node<T>;
    node->data = value;
    node->next = head;
    node->prev = nullptr;

    length++;

    if(head != nullptr) { head->prev = node; }
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

    if(head == nullptr) {
      tail = nullptr;
    } else {
      head->prev = nullptr;
    }

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
