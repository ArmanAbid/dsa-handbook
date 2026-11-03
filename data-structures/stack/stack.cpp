#include <iostream>
#include <vector>
using namespace std;

class Stack {
private:
    vector<int> elements;

public:
    // CREATE: Initialize an empty stack.
    Stack() {
        // vector is empty by default.
    }

    // PUSH: Add an element to the top.
    void push(int value) {
        elements.push_back(value);
    }

    // POP: Remove and return the top element.
    bool pop(int& removedValue) {
        if (elements.empty()) {
            return false;
        }

        removedValue = elements.back();
        elements.pop_back();

        return true;
    }

    // PEEK: Read the top element without removing it.
    bool peek(int& value) const {
        if (elements.empty()) {
            return false;
        }

        value = elements.back();
        return true;
    }

    // SIZE: Get the number of elements.
    int sizeOf() const {
        return static_cast<int>(elements.size());
    }

    // CHECK: Check whether the stack is empty.
    bool isEmpty() const {
        return elements.empty();
    }

    // DISPLAY: Show elements from top to bottom.
    void printStack() const {
        cout << "Top -> ";

        if (elements.empty()) {
            cout << "Bottom (Empty)" << endl;
            return;
        }

        for (int i = static_cast<int>(elements.size()) - 1;
             i >= 0; i--) {

            cout << elements[i];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << " -> Bottom" << endl;
    }

    // CLEAR: Remove all elements.
    void clearStack() {
        elements.clear();
    }
};

// DEMONSTRATION

int main() {
    Stack stack;
    int value;

    cout << "==== STACK ====" << endl;

    // PUSH
    cout << "\n--- PUSH ---" << endl;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.printStack();

    stack.push(40);

    cout << "After pushing 40:" << endl;
    stack.printStack();

    // PEEK
    cout << "\n--- PEEK ---" << endl;

    if (stack.peek(value)) {
        cout << "Top element: " << value << endl;
    }

    stack.printStack();

    // POP
    cout << "\n--- POP ---" << endl;

    if (stack.pop(value)) {
        cout << "Removed element: " << value << endl;
    }

    stack.printStack();

    if (stack.pop(value)) {
        cout << "Removed element: " << value << endl;
    }

    stack.printStack();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << stack.sizeOf() << endl;
    cout << "Is empty: " << (stack.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    stack.clearStack();

    stack.printStack();

    cout << "Size after clearing: " << stack.sizeOf() << endl;
    cout << "Is empty: " << (stack.isEmpty() ? "Yes" : "No") << endl;

    // EMPTY STACK CHECK
    cout << "\n--- EMPTY STACK CHECK ---" << endl;

    if (!stack.pop(value)) {
        cout << "Cannot pop: Stack is empty." << endl;
    }

    if (!stack.peek(value)) {
        cout << "Cannot peek: Stack is empty." << endl;
    }

    return 0;
}