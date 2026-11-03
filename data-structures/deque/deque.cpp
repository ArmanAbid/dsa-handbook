#include <iostream>
#include <vector>
using namespace std;

class Deque {
private:
    vector<int> elements;
    int capacity;
    int frontIndex;
    int count;

    // Increase capacity when the deque is full.
    void grow() {
        int newCapacity = capacity * 2;
        vector<int> newElements(newCapacity);

        // Copy elements in their logical order.
        for (int i = 0; i < count; i++) {
            int oldIndex = (frontIndex + i) % capacity;
            newElements[i] = elements[oldIndex];
        }

        elements.swap(newElements);

        capacity = newCapacity;
        frontIndex = 0;
    }

public:
    // CREATE: Initialize an empty deque.
    Deque() : elements(4) {
        capacity = 4;
        frontIndex = 0;
        count = 0;
    }

    // PUSH FRONT: Insert an element at the front.
    void pushFront(int value) {
        if (count == capacity) {
            grow();
        }

        frontIndex = (frontIndex - 1 + capacity) % capacity;

        elements[frontIndex] = value;
        count++;
    }

    // PUSH BACK: Insert an element at the rear.
    void pushBack(int value) {
        if (count == capacity) {
            grow();
        }

        int rearIndex = (frontIndex + count) % capacity;

        elements[rearIndex] = value;
        count++;
    }

    // POP FRONT: Remove and return the front element.
    bool popFront(int& removedValue) {
        if (isEmpty()) {
            return false;
        }

        removedValue = elements[frontIndex];

        frontIndex = (frontIndex + 1) % capacity;
        count--;

        if (count == 0) {
            frontIndex = 0;
        }

        return true;
    }

    // POP BACK: Remove and return the rear element.
    bool popBack(int& removedValue) {
        if (isEmpty()) {
            return false;
        }

        int rearIndex = (frontIndex + count - 1) % capacity;

        removedValue = elements[rearIndex];
        count--;

        if (count == 0) {
            frontIndex = 0;
        }

        return true;
    }

    // READ: Get the front element without removing it.
    bool getFront(int& value) const {
        if (isEmpty()) {
            return false;
        }

        value = elements[frontIndex];
        return true;
    }

    // READ: Get the rear element without removing it.
    bool getRear(int& value) const {
        if (isEmpty()) {
            return false;
        }

        int rearIndex = (frontIndex + count - 1) % capacity;

        value = elements[rearIndex];
        return true;
    }

    // SIZE: Get the number of elements.
    int sizeOf() const {
        return count;
    }

    // CHECK: Check whether the deque is empty.
    bool isEmpty() const {
        return count == 0;
    }

    // DISPLAY: Show elements from front to rear.
    void printDeque() const {
        cout << "Deque: Front -> ";

        if (isEmpty()) {
            cout << "Rear (Empty)" << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            int index = (frontIndex + i) % capacity;

            cout << elements[index];

            if (i < count - 1) {
                cout << " <-> ";
            }
        }

        cout << " -> Rear" << endl;
    }

    // CLEAR: Remove all elements without changing capacity.
    void clearDeque() {
        frontIndex = 0;
        count = 0;
    }
};

// DEMONSTRATION

int main() {
    Deque deque;
    int value;

    cout << "==== DEQUE ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    deque.pushBack(10);
    deque.pushBack(20);
    deque.pushBack(30);

    deque.printDeque();

    deque.pushFront(5);

    cout << "After pushing 5 at the front:" << endl;
    deque.printDeque();

    // This insertion triggers an increase in capacity.
    deque.pushBack(40);

    cout << "After pushing 40 at the rear:" << endl;
    deque.printDeque();

    // READ
    cout << "\n--- READ ---" << endl;

    if (deque.getFront(value)) {
        cout << "Front element: " << value << endl;
    }

    if (deque.getRear(value)) {
        cout << "Rear element: " << value << endl;
    }

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    if (deque.popFront(value)) {
        cout << "Removed from front: " << value << endl;
    }

    deque.printDeque();

    if (deque.popBack(value)) {
        cout << "Removed from back: " << value << endl;
    }

    deque.printDeque();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << deque.sizeOf() << endl;
    cout << "Is empty: " << (deque.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    deque.clearDeque();

    deque.printDeque();

    cout << "Size after clearing: " << deque.sizeOf() << endl;
    cout << "Is empty: " << (deque.isEmpty() ? "Yes" : "No") << endl;

    // EMPTY DEQUE CHECK
    cout << "\n--- EMPTY DEQUE CHECK ---" << endl;

    if (!deque.popFront(value)) {
        cout << "Cannot pop from front: Deque is empty." << endl;
    }

    if (!deque.popBack(value)) {
        cout << "Cannot pop from back: Deque is empty." << endl;
    }

    if (!deque.getFront(value)) {
        cout << "Cannot get front: Deque is empty." << endl;
    }

    if (!deque.getRear(value)) {
        cout << "Cannot get rear: Deque is empty." << endl;
    }

    return 0;
}