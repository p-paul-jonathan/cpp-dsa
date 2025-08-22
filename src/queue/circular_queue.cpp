#include <iostream>

template <class T> class CircularQueue {
public:
  CircularQueue(int cap = 32) {
    if (cap < 1) {
      throw std::invalid_argument("must be greater than 0");
    }
    capacity = cap;
    array = new T[capacity];
  }

  ~CircularQueue() { delete[] array; }

  void enqueue(T n) {
    if ((tail + 1) % capacity == head) {
      throw std::overflow_error("Queue is full");
    }

    if (head == -1) {
      head = tail = 0;
    } else {
      tail = (tail + 1) % capacity;
    }

    array[tail] = n;
    length++;
  }

  T dequeue() {
    if (head == -1) {
      throw std::underflow_error("Queue is empty");
    }

    T top = array[head];

    if (head == tail) {
      head = tail = -1; // queue becomes empty
    } else {
      head = (head + 1) % capacity;
    }

    length--;
    return top;
  }

  T peek() {
    if (head == -1)
      throw std::underflow_error("Queue is empty");
    return array[head];
  }

  void display() {
    std::cout << "{ capacity: " << getCapacity() << ", length: " << getLength()
              << " } [ ";

    if (head == -1) {
      std::cout << "]\n";
      return;
    }

    int i = head;
    while (true) {
      std::cout << array[i] << " ";
      if (i == tail)
        break;
      i = (i + 1) % capacity;
    }

    std::cout << "]\n";
  }

  int getCapacity() { return capacity; }
  int getLength() { return length; }

protected:
  T *array;
  int capacity, head = -1, tail = -1, length = 0;
};

int main() {
  CircularQueue<int> cq(5);

  cq.enqueue(1);
  cq.enqueue(2);
  cq.enqueue(3);
  cq.enqueue(4);

  std::cout << cq.peek() << "\n";
  std::cout << cq.dequeue() << "\n";
  std::cout << cq.dequeue() << "\n";

  cq.enqueue(5);
  cq.enqueue(6);

  cq.display();

  return 0;
}
