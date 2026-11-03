#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
private:
    vector<int> elements;
    bool isMinHeap;

    // Check whether the first value has higher priority.
    bool hasHigherPriority(int first, int second) const {
        if (isMinHeap) {
            return first < second;
        }

        return first > second;
    }

    // Swap two elements.
    void swapElements(int first, int second) {
        int temp = elements[first];
        elements[first] = elements[second];
        elements[second] = temp;
    }

    // SIFT UP: Restore the heap property after insertion.
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (!hasHigherPriority(elements[index], elements[parent])) {
                break;
            }

            swapElements(index, parent);
            index = parent;
        }
    }

    // SIFT DOWN: Restore the heap property after extraction.
    void siftDown(int index) {
        int length = static_cast<int>(elements.size());

        while (true) {
            int best = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            // Check the left child.
            if (
                left < length &&
                hasHigherPriority(elements[left], elements[best])
            ) {
                best = left;
            }

            // Check the right child.
            if (
                right < length &&
                hasHigherPriority(elements[right], elements[best])
            ) {
                best = right;
            }

            // Heap property is already satisfied.
            if (best == index) {
                break;
            }

            swapElements(index, best);
            index = best;
        }
    }

public:
    // CREATE: Initialize an empty heap.
    // true = Min Heap, false = Max Heap.
    BinaryHeap(bool minHeap = true) {
        isMinHeap = minHeap;
    }

    // INSERT: Add a value to the heap.
    void insert(int value) {
        elements.push_back(value);

        // Move the new element to its correct position.
        siftUp(static_cast<int>(elements.size()) - 1);
    }

    // PEEK: Read the root without removing it.
    bool peek(int& value) const {
        if (isEmpty()) {
            return false;
        }

        value = elements[0];
        return true;
    }

    // EXTRACT ROOT: Remove and return the root.
    bool extractRoot(int& removedValue) {
        if (isEmpty()) {
            return false;
        }

        removedValue = elements[0];

        // If only one element exists, simply remove it.
        if (elements.size() == 1) {
            elements.pop_back();
            return true;
        }

        // Move the last element to the root.
        elements[0] = elements.back();
        elements.pop_back();

        // Restore the heap property.
        siftDown(0);

        return true;
    }

    // CONTAINS: Check whether a value exists.
    bool contains(int value) const {
        for (unsigned int i = 0; i < elements.size(); i++) {
            if (elements[i] == value) {
                return true;
            }
        }

        return false;
    }

    // SIZE: Get the number of elements.
    int sizeOf() const {
        return static_cast<int>(elements.size());
    }

    // CHECK: Check whether the heap is empty.
    bool isEmpty() const {
        return elements.empty();
    }

    // DISPLAY: Show the internal array representation.
    void printHeap() const {
        cout << "Heap: [";

        for (unsigned int i = 0; i < elements.size(); i++) {
            cout << elements[i];

            if (i < elements.size() - 1) {
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }

    // CLEAR: Remove all elements.
    void clearHeap() {
        elements.clear();
    }
};

// DEMONSTRATION

int main() {
    BinaryHeap minHeap(true);
    BinaryHeap maxHeap(false);
    int value;

    cout << "==== BINARY HEAP ====" << endl;

    // MIN HEAP

    cout << "\n==== MIN HEAP ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    minHeap.insert(40);
    minHeap.insert(20);
    minHeap.insert(30);
    minHeap.insert(10);
    minHeap.insert(50);
    minHeap.insert(5);
    minHeap.insert(35);

    minHeap.printHeap();

    // PEEK
    cout << "\n--- PEEK ---" << endl;

    if (minHeap.peek(value)) {
        cout << "Minimum element: " << value << endl;
    }

    // CONTAINS
    cout << "\n--- CONTAINS ---" << endl;

    cout << "Contains 30: "
         << (minHeap.contains(30) ? "Yes" : "No") << endl;

    cout << "Contains 100: "
         << (minHeap.contains(100) ? "Yes" : "No") << endl;

    // EXTRACT ROOT
    cout << "\n--- EXTRACT ROOT ---" << endl;

    if (minHeap.extractRoot(value)) {
        cout << "Extracted minimum: " << value << endl;
    }

    minHeap.printHeap();

    if (minHeap.extractRoot(value)) {
        cout << "Extracted minimum: " << value << endl;
    }

    minHeap.printHeap();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << minHeap.sizeOf() << endl;
    cout << "Is empty: "
         << (minHeap.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR MIN HEAP ---" << endl;

    minHeap.clearHeap();

    minHeap.printHeap();

    cout << "Size after clearing: " << minHeap.sizeOf() << endl;

    // EMPTY HEAP CHECK
    cout << "\n--- EMPTY MIN HEAP CHECK ---" << endl;

    if (!minHeap.extractRoot(value)) {
        cout << "Cannot extract: Heap is empty." << endl;
    }

    if (!minHeap.peek(value)) {
        cout << "Cannot peek: Heap is empty." << endl;
    }

    // INSERT AFTER CLEAR
    minHeap.insert(15);
    minHeap.insert(8);

    cout << "After inserting again:" << endl;
    minHeap.printHeap();

    // MAX HEAP

    cout << "\n==== MAX HEAP ====" << endl;

    // INSERT
    maxHeap.insert(40);
    maxHeap.insert(20);
    maxHeap.insert(30);
    maxHeap.insert(10);
    maxHeap.insert(50);
    maxHeap.insert(5);
    maxHeap.insert(35);

    maxHeap.printHeap();

    // PEEK
    cout << "\n--- PEEK ---" << endl;

    if (maxHeap.peek(value)) {
        cout << "Maximum element: " << value << endl;
    }

    // EXTRACT ROOT
    cout << "\n--- EXTRACT ROOT ---" << endl;

    if (maxHeap.extractRoot(value)) {
        cout << "Extracted maximum: " << value << endl;
    }

    maxHeap.printHeap();

    return 0;
}