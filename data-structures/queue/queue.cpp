#include <iostream>
#include <vector>
using namespace std;

class Queue {
private:
    vector<int> elements;
    int capacity;
    int frontIndex;
    int count;

    // Increase capacity when the queue is full.
    void grow() {
        int newCapacity = capacity * 2;
        vector<int> newElements(newCapacity);

        // Copy elements in their logical queue order.
        for (int i = 0; i < count; i++) {
            int oldIndex = (frontIndex + i) % capacity;
            newElements[i] = elements[oldIndex];
        }

        elements.swap(newElements);

        capacity = newCapacity;
        frontIndex = 0;
    }

public:
    // CREATE: Initialize an empty queue.
    Queue() : elements(4) {
        capacity = 4;
        frontIndex = 0;
        count = 0;
    }

    // ENQUEUE: Add an element at the rear.
    void enqueue(int value) {
        if (count == capacity) {
            grow();
        }

        int rearIndex = (frontIndex + count) % capacity;

        elements[rearIndex] = value;
        count++;
    }

    // DEQUEUE: Remove and return the front element.
    bool dequeue(int& removedValue) {
        if (isEmpty()) {
            return false;
        }

        removedValue = elements[frontIndex];

        frontIndex = (frontIndex + 1) % capacity;
        count--;

        // Reset the front position when the queue becomes empty.
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

    // CHECK: Check whether the queue is empty.
    bool isEmpty() const {
        return count == 0;
    }

    // DISPLAY: Show elements from front to rear.
    void printQueue() const {
        cout << "Queue: Front -> ";

        if (isEmpty()) {
            cout << "Rear (Empty)" << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            int index = (frontIndex + i) % capacity;

            cout << elements[index];

            if (i < count - 1) {
                cout << " -> ";
            }
        }

        cout << " -> Rear" << endl;
    }

    // CLEAR: Remove all elements without changing capacity.
    void clearQueue() {
        frontIndex = 0;
        count = 0;
    }
};

// DEMONSTRATION

int main() {
    Queue queue;
    int value;

    cout << "==== QUEUE ====" << endl;

    // ENQUEUE
    cout << "\n--- ENQUEUE ---" << endl;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    queue.printQueue();

    // This insertion triggers an increase in capacity.
    queue.enqueue(50);

    cout << "After enqueuing 50:" << endl;
    queue.printQueue();

    // READ
    cout << "\n--- READ ---" << endl;

    if (queue.getFront(value)) {
        cout << "Front element: " << value << endl;
    }

    if (queue.getRear(value)) {
        cout << "Rear element: " << value << endl;
    }

    // DEQUEUE
    cout << "\n--- DEQUEUE ---" << endl;

    if (queue.dequeue(value)) {
        cout << "Removed element: " << value << endl;
    }

    queue.printQueue();

    if (queue.dequeue(value)) {
        cout << "Removed element: " << value << endl;
    }

    queue.printQueue();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << queue.sizeOf() << endl;
    cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    queue.clearQueue();

    queue.printQueue();

    cout << "Size after clearing: " << queue.sizeOf() << endl;
    cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << endl;

    // EMPTY QUEUE CHECK
    cout << "\n--- EMPTY QUEUE CHECK ---" << endl;

    if (!queue.dequeue(value)) {
        cout << "Cannot dequeue: Queue is empty." << endl;
    }

    if (!queue.getFront(value)) {
        cout << "Cannot get front: Queue is empty." << endl;
    }

    if (!queue.getRear(value)) {
        cout << "Cannot get rear: Queue is empty." << endl;
    }

    return 0;
}