#include <iostream>

template <class T> class Stack {
public:
  Stack(int cap = 32) {
    if (cap < 1) {
      throw std::invalid_argument("must be greater than 0");
    }

    capacity = cap;
    array = new T[capacity];
  }

  ~Stack() { delete array; }

  void push(T n) {
    if (top == capacity - 1) {
      throw std::overflow_error("Stack is full");
    }

    top++;
    array[top] = n;
  }

  T pop() {
    if (top == -1) {
      throw std::underflow_error("Array is empty");
    }

    return array[top--];
  }

  T peek() {
    if (top == -1) {
      throw std::underflow_error("Array is empty");
    }

    return array[top];
  }

  int getCapacity() { return capacity; }
  int getLength() { return top + 1; }

  T getIndex(int index) {
    if (index > top) {
      throw std::invalid_argument("out of range");
    }

    return array[index];
  }

  void display() {
    std::cout << "{ capacity: " << getCapacity() << ", length: " << getLength()
              << " } ";
    std::cout << "[ ";
    for (int i = 0; i <= top; i++) {
      std::cout << array[i] << " ";
    }
    std::cout << "]\n";
  }

protected:
  T *array;
  int capacity = 0, top = -1;
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
