#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <class T> class BinaryMinHeap {
private:
  int capacity;
  int length;
  T *array;
  std::function<int(const T &, const T &)> comparator;

  static int defaultComparator(const T &a, const T &b) {
    if (a < b)
      return -1;
    if (a > b)
      return 1;
    return 0;
  }

  void heapify() {
    for (int i = (length / 2) - 1; i >= 0; i--) {
      siftDown(i);
    }
  }

  void siftDown(int index) {
    int new_index, old_index = index;

    while (1) {
      new_index = leastIndex(old_index);
      if (new_index == old_index) {
        break;
      }

      swap(array[old_index], array[new_index]);
      old_index = new_index;
    }
  }

  void siftUp(int index) {
    int current_index = index, parent_index;

    while (current_index > 0) {
      parent_index = (current_index - 1) / 2;

      if (comparator(array[parent_index], array[current_index]) <= 0) {
        break;
      }

      swap(array[parent_index], array[current_index]);
      current_index = parent_index;
    }
  }

  void swap(T &a, T &b) {
    T temp;

    temp = a;
    a = b;
    b = temp;
  }

  int leastIndex(int index) {
    int left_child_index = 2 * index + 1;
    int right_child_index = 2 * index + 2;
    int smallest_index = index;

    if (left_child_index < length &&
        comparator(array[left_child_index], array[smallest_index]) < 0) {
      smallest_index = left_child_index;
    }

    if (right_child_index < length &&
        comparator(array[right_child_index], array[smallest_index]) < 0) {
      smallest_index = right_child_index;
    }

    return smallest_index;
  }

public:
  BinaryMinHeap(
      int cap = 32,
      std::function<int(const T &, const T &)> comparator = defaultComparator)
      : capacity(cap), length(0), comparator(comparator) {
    if (cap < 1) {
      throw std::invalid_argument("`cap` must be greater than 0");
    }
    array = new T[capacity];
  }

  ~BinaryMinHeap() { delete[] array; }

  T getMin() {
    if (length == 0) {
      throw std::underflow_error("heap is empty");
    }

    return array[0];
  }

  T extractMin() {
    if (length == 0) {
      throw std::underflow_error("heap is empty");
    }

    T min = array[0];
    length--;
    array[0] = array[length];

    siftDown(0);

    return min;
  }

  void changeKey(T old_value, T new_value) {
    bool valueFound = false;
    int index = -1;

    for (int i = 0; i < length; i++) {
      if (array[i] == old_value) {
        valueFound = true;
        array[i] = new_value;
        index = i;
        break;
      }
    }

    if (!valueFound) {
      throw std::out_of_range("value not in heap");
    }

    // heapify();

    if (comparator(old_value, new_value) <= 0) {
      siftDown(index);
    } else {
      siftUp(index);
    }
  }

  void insert(T value) {
    if (length == capacity) {
      throw std::overflow_error("heap is full");
    }

    array[length] = value;
    length++;
    siftUp(length - 1);
  }
};

void check(bool condition, const std::string &message) {
  if (condition) {
    std::cout << "\033[32mPASS\033[0m: " << message << "\n"; // green
  } else {
    std::cout << "\033[31mFAIL\033[0m: " << message << "\n"; // red
  }
}

int main() {
  // Test 1: constructor with invalid capacity
  {
    bool threw = false;
    try {
      BinaryMinHeap<int> h(0);
    } catch (std::invalid_argument &) {
      threw = true;
    }
    check(threw, "constructor throws invalid_argument for capacity 0");
  }

  // Test 2: insert and getMin
  {
    BinaryMinHeap<int> h(5);
    h.insert(42);
    check(h.getMin() == 42, "insert and getMin returns inserted element");
  }

  // Test 3: getMin on empty heap throws
  {
    BinaryMinHeap<int> h(5);
    bool threw = false;
    try {
      h.getMin();
    } catch (std::underflow_error &) {
      threw = true;
    }
    check(threw, "getMin throws underflow_error on empty heap");
  }

  // Test 4: extractMin on non-empty
  {
    BinaryMinHeap<int> h(5);
    h.insert(10);
    h.insert(20);
    int m = h.extractMin();
    check(m == 10, "extractMin returns smallest element");
    check(h.getMin() == 20,
          "getMin after extractMin returns remaining element");
  }

  // Test 5: extractMin on empty throws
  {
    BinaryMinHeap<int> h(5);
    bool threw = false;
    try {
      h.extractMin();
    } catch (std::underflow_error &) {
      threw = true;
    }
    check(threw, "extractMin throws underflow_error on empty heap");
  }

  // Test 6: changeKey decrease
  {
    BinaryMinHeap<int> h(5);
    h.insert(100);
    h.changeKey(100, 50);
    check(h.getMin() == 50, "changeKey decrease works");
  }

  // Test 7: changeKey on missing value
  {
    BinaryMinHeap<int> h(5);
    h.insert(1);
    bool threw = false;
    try {
      h.changeKey(999, 10);
    } catch (std::out_of_range &) {
      threw = true;
    }
    check(threw, "changeKey throws out_of_range when value not found");
  }

  // Test 8: insert beyond capacity
  {
    BinaryMinHeap<int> h(2);
    h.insert(1);
    h.insert(2);
    bool threw = false;
    try {
      h.insert(3);
    } catch (std::overflow_error &) {
      threw = true;
    }
    check(threw, "insert throws overflow_error when heap is full");
  }

  // Test 9: multiple inserts maintain heap property
  {
    BinaryMinHeap<int> h(10);
    h.insert(5);
    h.insert(3);
    h.insert(8);
    h.insert(1);
    check(h.getMin() == 1, "heap maintains min after multiple inserts");
  }

  // Test 10: extractMin repeatedly returns sorted order
  {
    BinaryMinHeap<int> h(10);
    h.insert(4);
    h.insert(7);
    h.insert(2);
    h.insert(9);
    h.insert(1);

    int a = h.extractMin(); // 1
    int b = h.extractMin(); // 2
    int c = h.extractMin(); // 4
    check((a == 1 && b == 2 && c == 4),
          "extractMin repeatedly returns ascending order");
  }

  // Test 11: changeKey increase
  {
    BinaryMinHeap<int> h(5);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.changeKey(1, 10); // increase root
    check(h.getMin() == 2, "changeKey increase pushes element down");
  }

  // Test 12: changeKey no-op (same value)
  {
    BinaryMinHeap<int> h(5);
    h.insert(5);
    h.changeKey(5, 5); // no change
    check(h.getMin() == 5, "changeKey with same value does nothing");
  }

  // Test 13: stress test with many values
  {
    BinaryMinHeap<int> h(20);
    for (int i = 20; i >= 1; --i) {
      h.insert(i);
    }

    bool sorted = true;
    for (int i = 1; i <= 20; i++) {
      if (h.extractMin() != i) {
        sorted = false;
        break;
      }
    }
    check(sorted, "heap correctly sorts 20 inserted values");
  }

  // --- Additional Tests ---

  // Test 14: using custom comparator for max-heap
  {
    auto maxComp = [](int a, int b) { return (a < b) ? 1 : (a > b ? -1 : 0); };
    BinaryMinHeap<int> h(10, maxComp);
    h.insert(1);
    h.insert(5);
    h.insert(3);
    check(h.getMin() == 5, "max-heap comparator makes getMin return max");
  }

  // Test 15: heap with doubles
  {
    BinaryMinHeap<double> h(5);
    h.insert(3.14);
    h.insert(2.71);
    h.insert(1.41);
    check(h.getMin() == 1.41, "heap works with double type");
  }

  // Test 16: heap with strings (lex order)
  {
    BinaryMinHeap<std::string> h(5);
    h.insert("pear");
    h.insert("apple");
    h.insert("orange");
    check(h.getMin() == "apple", "heap works with std::string (lex order)");
  }

  // Test 17: heap with custom comparator on strings (longest first)
  {
    auto longFirst = [](const std::string &a, const std::string &b) {
      if (a.size() < b.size())
        return 1;
      if (a.size() > b.size())
        return -1;
      return 0;
    };
    BinaryMinHeap<std::string> h(5, longFirst);
    h.insert("a");
    h.insert("banana");
    h.insert("pear");
    check(h.getMin() == "banana", "custom comparator: longest string first");
  }

  std::cout << "\n✅ Test suite finished.\n";
  return 0;
}
