#include "../lib/dynamic_array.h"

using namespace std;

int main() {
    DynamicArray<char> darr(20);

    for(int i = 0; i < 60; i++) {
      darr.push(i+65);
      darr.display();
    }

    for(int i = 0; i < 50; i++) {
      darr.pop();
      darr.display();
    }

    darr.display();

    cout << "index 5: " << darr.getIndex(5) << "\n";

    try {
      cout << "index 50: " << darr.getIndex(50) << "\n";
    } catch (...) {
      cout << "error\n";
    }

    return 0;
}
