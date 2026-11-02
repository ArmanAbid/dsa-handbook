#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode* next;

    ListNode(int value) {
        data = value;
        next = NULL;
    }
};

class CircularSinglyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int length;

    // Find a node at a specific index.
    ListNode* getNodeAt(int index) const {
        if (index < 0 || index >= length) {
            return NULL;
        }

        ListNode* current = head;

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
    }

public:
    // CREATE: Initialize an empty list.
    CircularSinglyLinkedList() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    // Prevent accidental shallow copying of owned pointers.
    CircularSinglyLinkedList(const CircularSinglyLinkedList&);
    CircularSinglyLinkedList& operator=(
        const CircularSinglyLinkedList&
    );

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

    // DISPLAY: Traverse exactly one complete cycle.
    void printList() const {
        cout << "List: ";

        if (head == NULL) {
            cout << "Empty" << endl;
            return;
        }

        ListNode* current = head;

        do {
            cout << current->data;

            if (current->next != head) {
                cout << " -> ";
            }

            current = current->next;

        } while (current != head);

        cout << " -> (back to head)" << endl;
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
        } else {
            newNode->next = head;
            head = newNode;
            tail->next = head;
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
        } else {
            newNode->next = head;
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

        ListNode* previous = getNodeAt(index - 1);
        ListNode* newNode = new ListNode(data);

        newNode->next = previous->next;
        previous->next = newNode;

        length++;
        return true;
    }

    // DELETE: Remove the first element.
    bool removeFront(int& removedData) {
        if (head == NULL) {
            return false;
        }

        removedData = head->data;

        // Only one node exists.
        if (head == tail) {
            delete head;

            head = NULL;
            tail = NULL;
        } else {
            ListNode* oldHead = head;

            head = head->next;
            tail->next = head;

            delete oldHead;
        }

        length--;
        return true;
    }

    // DELETE: Remove the last element.
    bool removeBack(int& removedData) {
        if (tail == NULL) {
            return false;
        }

        removedData = tail->data;

        // Only one node exists.
        if (head == tail) {
            delete tail;

            head = NULL;
            tail = NULL;
        } else {
            ListNode* previous = head;

            while (previous->next != tail) {
                previous = previous->next;
            }

            delete tail;

            tail = previous;
            tail->next = head;
        }

        length--;
        return true;
    }

    // DELETE: Remove an element at a specific index.
    bool removeAt(int index, int& removedData) {
        if (index < 0 || index >= length) {
            return false;
        }

        if (index == 0) {
            return removeFront(removedData);
        }

        if (index == length - 1) {
            return removeBack(removedData);
        }

        ListNode* previous = getNodeAt(index - 1);
        ListNode* current = previous->next;

        removedData = current->data;

        previous->next = current->next;

        delete current;

        length--;
        return true;
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
    ~CircularSinglyLinkedList() {
        clearList();
    }
};

// DEMONSTRATION

int main() {
    CircularSinglyLinkedList list;
    int value;

    cout << "==== CIRCULAR SINGLY LINKED LIST ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    list.insertFront(20);
    list.insertFront(10);
    list.insertBack(30);
    list.insertBack(40);

    list.printList();

    list.insertAt(2, 25);

    cout << "After inserting 25 at index 2:" << endl;
    list.printList();

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
    list.printList();

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    if (list.removeFront(value)) {
        cout << "Removed from front: " << value << endl;
    }

    list.printList();

    if (list.removeBack(value)) {
        cout << "Removed from back: " << value << endl;
    }

    list.printList();

    if (list.removeAt(1, value)) {
        cout << "Removed from index 1: " << value << endl;
    }

    list.printList();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << list.sizeOf() << endl;
    cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    list.clearList();

    list.printList();

    cout << "Size after clearing: " << list.sizeOf() << endl;
    cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}