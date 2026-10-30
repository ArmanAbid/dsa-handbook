#include <iostream>

using namespace std;

// NODE

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

// CREATE

Node* createNode(int value) {
    return new Node(value);
}

// READ

bool getFirst(Node* head, int& value) {
    if (head == NULL) {
        return false;
    }

    value = head->data;
    return true;
}

bool getLast(Node* tail, int& value) {
    if (tail == NULL) {
        return false;
    }

    value = tail->data;
    return true;
}

bool getAt(Node* head, int index, int& value) {
    if (index < 0) {
        return false;
    }

    Node* current = head;

    for (int i = 0; current != NULL && i < index; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    value = current->data;
    return true;
}

void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        cout << current->data;

        if (current->next != NULL) {
            cout << " -> ";
        }

        current = current->next;
    }

    cout << " -> NULL\n";
}

// UPDATE

bool setAt(Node* head, int index, int value) {
    if (index < 0) {
        return false;
    }

    Node* current = head;

    for (int i = 0; current != NULL && i < index; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    current->data = value;
    return true;
}

// INSERT

void insertFront(Node*& head, Node*& tail, int& size, int value) {
    Node* node = createNode(value);

    node->next = head;
    head = node;

    if (tail == NULL) {
        tail = node;
    }

    size++;
}

void insertBack(Node*& head, Node*& tail, int& size, int value) {
    Node* node = createNode(value);

    if (head == NULL) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    size++;
}

// index == size inserts at the end.
bool insertAt(
    Node*& head,
    Node*& tail,
    int& size,
    int index,
    int value
) {
    if (index < 0 || index > size) {
        return false;
    }

    if (index == 0) {
        insertFront(head, tail, size, value);
        return true;
    }

    if (index == size) {
        insertBack(head, tail, size, value);
        return true;
    }

    Node* previous = head;

    for (int i = 0; i < index - 1; i++) {
        previous = previous->next;
    }

    Node* node = createNode(value);

    node->next = previous->next;
    previous->next = node;

    size++;

    return true;
}

// DELETE

bool removeFront(
    Node*& head,
    Node*& tail,
    int& size,
    int& removedValue
) {
    if (head == NULL) {
        return false;
    }

    Node* node = head;

    removedValue = node->data;
    head = head->next;

    delete node;

    size--;

    if (head == NULL) {
        tail = NULL;
    }

    return true;
}

bool removeBack(
    Node*& head,
    Node*& tail,
    int& size,
    int& removedValue
) {
    if (head == NULL) {
        return false;
    }

    if (head == tail) {
        return removeFront(head, tail, size, removedValue);
    }

    Node* previous = head;

    while (previous->next != tail) {
        previous = previous->next;
    }

    removedValue = tail->data;

    delete tail;

    tail = previous;
    tail->next = NULL;

    size--;

    return true;
}

bool removeAt(
    Node*& head,
    Node*& tail,
    int& size,
    int index,
    int& removedValue
) {
    if (index < 0 || index >= size) {
        return false;
    }

    if (index == 0) {
        return removeFront(head, tail, size, removedValue);
    }

    if (index == size - 1) {
        return removeBack(head, tail, size, removedValue);
    }

    Node* previous = head;

    for (int i = 0; i < index - 1; i++) {
        previous = previous->next;
    }

    Node* node = previous->next;

    removedValue = node->data;

    previous->next = node->next;

    delete node;

    size--;

    return true;
}

// SIZE AND BASIC PROPERTIES

int sizeOf(int size) {
    return size;
}

bool isEmpty(Node* head) {
    return head == NULL;
}

// CLEAR

void clearList(Node*& head, Node*& tail, int& size) {
    Node* current = head;

    while (current != NULL) {
        Node* nextNode = current->next;

        delete current;

        current = nextNode;
    }

    head = NULL;
    tail = NULL;
    size = 0;
}

// DEMONSTRATION

int main() {

    Node* head = NULL;
    Node* tail = NULL;
    int size = 0;

    cout << "==== SINGLY LINKED LIST ====\n";

    // CREATE AND INSERT
    insertBack(head, tail, size, 10);
    insertBack(head, tail, size, 20);
    insertBack(head, tail, size, 30);

    cout << "Initial list: ";
    printList(head);

    // READ
    int value = 0;

    if (getFirst(head, value)) {
        cout << "First node: " << value << '\n';
    }

    if (getLast(tail, value)) {
        cout << "Last node: " << value << '\n';
    }

    if (getAt(head, 1, value)) {
        cout << "Node at index 1: " << value << '\n';
    }

    // UPDATE
    setAt(head, 1, 25);

    cout << "After updating: ";
    printList(head);

    // INSERT
    insertFront(head, tail, size, 5);
    insertBack(head, tail, size, 40);
    insertAt(head, tail, size, 2, 15);

    cout << "After inserting: ";
    printList(head);

    // DELETE
    int removedValue = 0;

    if (removeAt(head, tail, size, 2, removedValue)) {
        cout << "Removed at index 2: " << removedValue << '\n';
    }

    if (removeFront(head, tail, size, removedValue)) {
        cout << "Removed first node: " << removedValue << '\n';
    }

    if (removeBack(head, tail, size, removedValue)) {
        cout << "Removed last node: " << removedValue << '\n';
    }

    cout << "After deleting: ";
    printList(head);

    // SIZE AND PROPERTIES
    cout << "Size: " << sizeOf(size) << '\n';
    cout << "Empty: " << (isEmpty(head) ? "true" : "false") << '\n';

    // CLEAR
    clearList(head, tail, size);

    cout << "After clearing: ";
    printList(head);

    cout << "Size after clearing: " << sizeOf(size) << '\n';
    cout << "Empty after clearing: " << (isEmpty(head) ? "true" : "false") << '\n';

    return 0;
}
