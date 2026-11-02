class ListNode {
    data: number;
    next: ListNode | null;

    constructor(data: number) {
        this.data = data;
        this.next = null;
    }
}

class CircularSinglyLinkedList {
    private head: ListNode | null;
    private tail: ListNode | null;
    private length: number;

    constructor() {
        this.head = null;
        this.tail = null;
        this.length = 0;
    }

    // Find a node at a specific index.
    private nodeAt(index: number): ListNode | null {
        if (index < 0 || index >= this.length) {
            return null;
        }

        let current: ListNode | null = this.head;

        for (let i = 0; i < index; i++) {
            if (current === null) {
                return null;
            }

            current = current.next;
        }

        return current;
    }

    // READ: Get the first element.
    getFirst(): number | undefined {
        if (this.head === null) {
            return undefined;
        }

        return this.head.data;
    }

    // READ: Get the last element.
    getLast(): number | undefined {
        if (this.tail === null) {
            return undefined;
        }

        return this.tail.data;
    }

    // READ: Get an element at a specific index.
    getAt(index: number): number | undefined {
        const node = this.nodeAt(index);

        if (node === null) {
            return undefined;
        }

        return node.data;
    }

    // DISPLAY: Traverse exactly one complete cycle.
    printList(): void {
        if (this.head === null) {
            console.log("List: Empty");
            return;
        }

        let current: ListNode | null = this.head;
        const values: number[] = [];

        while (current !== null) {
            values.push(current.data);
            current = current.next;

            if (current === this.head) {
                break;
            }
        }

        console.log(
            "List:",
            values.join(" -> "),
            "-> (back to head)"
        );
    }

    // UPDATE: Change the value at a specific index.
    setAt(index: number, value: number): boolean {
        const node = this.nodeAt(index);

        if (node === null) {
            return false;
        }

        node.data = value;
        return true;
    }

    // INSERT: Add an element at the beginning.
    insertFront(data: number): void {
        const newNode = new ListNode(data);

        if (this.head === null) {
            this.head = newNode;
            this.tail = newNode;

            // The only node points to itself.
            newNode.next = newNode;
        } else {
            newNode.next = this.head;
            this.tail!.next = newNode;
            this.tail = newNode;
        }

        this.length++;
    }

    // INSERT: Add an element at the end.
    insertBack(data: number): void {
        const newNode = new ListNode(data);

        if (this.tail === null) {
            this.head = newNode;
            this.tail = newNode;

            newNode.next = newNode;
        } else {
            newNode.next = this.head;
            this.tail.next = newNode;
            this.tail = newNode;
        }

        this.length++;
    }

    // INSERT: Add an element at a specific index.
    insertAt(index: number, data: number): boolean {
        if (index < 0 || index > this.length) {
            return false;
        }

        if (index === 0) {
            this.insertFront(data);
            return true;
        }

        if (index === this.length) {
            this.insertBack(data);
            return true;
        }

        const previous = this.nodeAt(index - 1);

        if (previous === null) {
            return false;
        }

        const newNode = new ListNode(data);

        newNode.next = previous.next;
        previous.next = newNode;

        this.length++;
        return true;
    }

    // DELETE: Remove the first element.
    removeFront(): number | undefined {
        if (this.head === null) {
            return undefined;
        }

        const removedData = this.head.data;

        // Only one node exists.
        if (this.head === this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = this.head.next;
            this.tail!.next = this.head;
        }

        this.length--;
        return removedData;
    }

    // DELETE: Remove the last element.
    removeBack(): number | undefined {
        if (this.tail === null) {
            return undefined;
        }

        const removedData = this.tail.data;

        // Only one node exists.
        if (this.head === this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            let previous: ListNode = this.head!;

            while (previous.next !== this.tail) {
                previous = previous.next!;
            }

            this.tail = previous;
            this.tail.next = this.head;
        }

        this.length--;
        return removedData;
    }

    // DELETE: Remove an element at a specific index.
    removeAt(index: number): number | undefined {
        if (index < 0 || index >= this.length) {
            return undefined;
        }

        if (index === 0) {
            return this.removeFront();
        }

        if (index === this.length - 1) {
            return this.removeBack();
        }

        const previous = this.nodeAt(index - 1);

        if (previous === null || previous.next === null) {
            return undefined;
        }

        const removedNode = previous.next;

        previous.next = removedNode.next;
        removedNode.next = null;

        this.length--;
        return removedNode.data;
    }

    // SIZE: Get the number of elements.
    sizeOf(): number {
        return this.length;
    }

    // CHECK: Check whether the list is empty.
    isEmpty(): boolean {
        return this.length === 0;
    }

    // CLEAR: Remove all elements.
    clearList(): void {
        let current = this.head;

        // Visit exactly the number of nodes in the list.
        for (let i = 0; i < this.length; i++) {
            if (current === null) {
                break;
            }

            const nextNode = current.next;
            current.next = null;
            current = nextNode;
        }

        this.head = null;
        this.tail = null;
        this.length = 0;
    }
}

// DEMONSTRATION

const list = new CircularSinglyLinkedList();

console.log("==== CIRCULAR SINGLY LINKED LIST ====");

// INSERT
console.log("\n--- INSERT ---");

list.insertFront(20);
list.insertFront(10);
list.insertBack(30);
list.insertBack(40);

list.printList();

list.insertAt(2, 25);

console.log("After inserting 25 at index 2:");
list.printList();

// READ
console.log("\n--- READ ---");

console.log("First element:", list.getFirst());
console.log("Last element:", list.getLast());
console.log("Element at index 2:", list.getAt(2));

// UPDATE
console.log("\n--- UPDATE ---");

list.setAt(2, 99);

console.log("After updating index 2 to 99:");
list.printList();

// DELETE
console.log("\n--- DELETE ---");

console.log("Removed from front:", list.removeFront());
list.printList();

console.log("Removed from back:", list.removeBack());
list.printList();

console.log("Removed from index 1:", list.removeAt(1));
list.printList();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", list.sizeOf());
console.log("Is empty:", list.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

list.clearList();

list.printList();

console.log("Size after clearing:", list.sizeOf());
console.log("Is empty:", list.isEmpty());