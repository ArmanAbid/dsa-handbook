#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode* prev;
    ListNode* next;

    ListNode(int value) {
        data = value;
        prev = NULL;
        next = NULL;
    }
};

class CircularDoublyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int length;

    // Prevent accidental shallow copying of owned pointers.
    CircularDoublyLinkedList(const CircularDoublyLinkedList&);
    CircularDoublyLinkedList& operator=(
        const CircularDoublyLinkedList&
    );

    // Find a node at a specific index.
    // Start from whichever end is closer.
    ListNode* getNodeAt(int index) const {
        if (index < 0 || index >= length) {
            return NULL;
        }

        ListNode* current;

        if (index < length / 2) {
            current = head;

            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;

            for (int i = length - 1; i > index; i--) {
                current = current->prev;
            }
        }

        return current;
    }

    // Remove a specific node and free its memory.
    bool removeNode(ListNode* node, int& removedData) {
        if (node == NULL) {
            return false;
        }

        removedData = node->data;

        // Only one node exists.
        if (head == tail) {
            delete node;

            head = NULL;
            tail = NULL;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;

            if (node == head) {
                head = node->next;
            }

            if (node == tail) {
                tail = node->prev;
            }

            delete node;
        }

        length--;
        return true;
    }

public:
    // CREATE: Initialize an empty list.
    CircularDoublyLinkedList() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    // READ: Get the first element.
    bool getFirst(int& value) const {
        if (head == NULL) {
            return false;
        }

        value = head->data;
        return true;
    }

    // READ: Get the last element.
    bool getLast(int& value) const {
        if (tail == NULL) {
            return false;
        }

        value = tail->data;
        return true;
    }

    // READ: Get an element at a specific index.
    bool getAt(int index, int& value) const {
        ListNode* current = getNodeAt(index);

        if (current == NULL) {
            return false;
        }

        value = current->data;
        return true;
    }

    // DISPLAY: Traverse from head to tail.
    void printForward() const {
        cout << "Forward: ";

        if (head == NULL) {
            cout << "Empty" << endl;
            return;
        }

        ListNode* current = head;

        do {
            cout << current->data;

            if (current->next != head) {
                cout << " <-> ";
            }

            current = current->next;

        } while (current != head);

        cout << " -> (back to head)" << endl;
    }

    // DISPLAY: Traverse from tail to head.
    void printBackward() const {
        cout << "Backward: ";

        if (tail == NULL) {
            cout << "Empty" << endl;
            return;
        }

        ListNode* current = tail;

        do {
            cout << current->data;

            if (current->prev != tail) {
                cout << " <-> ";
            }

            current = current->prev;

        } while (current != tail);

        cout << " -> (back to tail)" << endl;
    }

    // UPDATE: Change the value at a specific index.
    bool setAt(int index, int value) {
        ListNode* current = getNodeAt(index);

        if (current == NULL) {
            return false;
        }

        current->data = value;
        return true;
    }

    // INSERT: Add an element at the beginning.
    void insertFront(int data) {
        ListNode* newNode = new ListNode(data);

        if (head == NULL) {
            head = newNode;
            tail = newNode;

            // The only node points to itself.
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->next = head;
            newNode->prev = tail;

            head->prev = newNode;
            tail->next = newNode;

            head = newNode;
        }

        length++;
    }

    // INSERT: Add an element at the end.
    void insertBack(int data) {
        ListNode* newNode = new ListNode(data);

        if (tail == NULL) {
            head = newNode;
            tail = newNode;

            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->prev = tail;
            newNode->next = head;

            tail->next = newNode;
            head->prev = newNode;

            tail = newNode;
        }

        length++;
    }

    // INSERT: Add an element at a specific index.
    bool insertAt(int index, int data) {
        if (index < 0 || index > length) {
            return false;
        }

        if (index == 0) {
            insertFront(data);
            return true;
        }

        if (index == length) {
            insertBack(data);
            return true;
        }

        ListNode* nextNode = getNodeAt(index);
        ListNode* previousNode = nextNode->prev;

        ListNode* newNode = new ListNode(data);

        newNode->prev = previousNode;
        newNode->next = nextNode;

        previousNode->next = newNode;
        nextNode->prev = newNode;

        length++;
        return true;
    }

    // DELETE: Remove the first element.
    bool removeFront(int& removedData) {
        if (head == NULL) {
            return false;
        }

        return removeNode(head, removedData);
    }

    // DELETE: Remove the last element.
    bool removeBack(int& removedData) {
        if (tail == NULL) {
            return false;
        }

        return removeNode(tail, removedData);
    }

    // DELETE: Remove an element at a specific index.
    bool removeAt(int index, int& removedData) {
        ListNode* current = getNodeAt(index);

        if (current == NULL) {
            return false;
        }

        return removeNode(current, removedData);
    }

    // SIZE: Get the number of elements.
    int sizeOf() const {
        return length;
    }

    // CHECK: Check whether the list is empty.
    bool isEmpty() const {
        return length == 0;
    }

    // CLEAR: Remove all nodes and free their memory.
    void clearList() {
        if (tail != NULL) {
            // Break the circular connection.
            tail->next = NULL;
        }

        ListNode* current = head;

        while (current != NULL) {
            ListNode* nextNode = current->next;

            delete current;
            current = nextNode;
        }

        head = NULL;
        tail = NULL;
        length = 0;
    }

    // Destructor: Automatically free remaining nodes.
    ~CircularDoublyLinkedList() {
        clearList();
    }
};

// DEMONSTRATION

int main() {
    CircularDoublyLinkedList list;
    int value;

    cout << "=== CIRCULAR DOUBLY LINKED LIST ===" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    list.insertFront(20);
    list.insertFront(10);
    list.insertBack(30);
    list.insertBack(40);

    list.printForward();
    list.printBackward();

    list.insertAt(2, 25);

    cout << "After inserting 25 at index 2:" << endl;
    list.printForward();

    // READ
    cout << "\n--- READ ---" << endl;

    if (list.getFirst(value)) {
        cout << "First element: " << value << endl;
    }

    if (list.getLast(value)) {
        cout << "Last element: " << value << endl;
    }

    if (list.getAt(2, value)) {
        cout << "Element at index 2: " << value << endl;
    }

    // UPDATE
    cout << "\n--- UPDATE ---" << endl;

    list.setAt(2, 99);

    cout << "After updating index 2 to 99:" << endl;
    list.printForward();

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    if (list.removeFront(value)) {
        cout << "Removed from front: " << value << endl;
    }

    list.printForward();

    if (list.removeBack(value)) {
        cout << "Removed from back: " << value << endl;
    }

    list.printForward();

    if (list.removeAt(1, value)) {
        cout << "Removed from index 1: " << value << endl;
    }

    list.printForward();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << list.sizeOf() << endl;
    cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    list.clearList();

    list.printForward();
    list.printBackward();

    cout << "Size after clearing: " << list.sizeOf() << endl;
    cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}