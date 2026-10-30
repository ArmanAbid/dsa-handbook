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

class DoublyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int length;

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

        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next != NULL) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }

        delete node;
        length--;

        return true;
    }

public:
    // CREATE: Initialize an empty list.
    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    // Prevent accidental shallow copying of owned pointers.
    DoublyLinkedList(const DoublyLinkedList&);
    DoublyLinkedList& operator=(const DoublyLinkedList&);

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
        ListNode* current = head;

        cout << "Forward: ";

        if (current == NULL) {
            cout << "Empty";
        }

        while (current != NULL) {
            cout << current->data;

            if (current->next != NULL) {
                cout << " <-> ";
            }

            current = current->next;
        }

        cout << endl;
    }

    // DISPLAY: Traverse from tail to head.
    void printBackward() const {
        ListNode* current = tail;

        cout << "Backward: ";

        if (current == NULL) {
            cout << "Empty";
        }

        while (current != NULL) {
            cout << current->data;

            if (current->prev != NULL) {
                cout << " <-> ";
            }

            current = current->prev;
        }

        cout << endl;
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
        } else {
            newNode->next = head;
            head->prev = newNode;
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
        } else {
            newNode->prev = tail;
            tail->next = newNode;
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

    // CLEAR: Remove all elements and free their memory.
    void clearList() {
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
    ~DoublyLinkedList() {
        clearList();
    }
};

// DEMONSTRATION

int main() {
    DoublyLinkedList list;
    int value;

    cout << "==== DOUBLY LINKED LIST ====" << endl;

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

    cout << "Size after clearing: " << list.sizeOf() << endl;
    cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}