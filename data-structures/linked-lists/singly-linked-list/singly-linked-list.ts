class ListNode {
    data: number;
    next: ListNode | null;

    constructor(data: number) {
        this.data = data;
        this.next = null;
    }
}

class SinglyLinkedList {
    private head: ListNode | null;
    private tail: ListNode | null;
    private length: number;

    constructor() {
        this.head = null;
        this.tail = null;
        this.length = 0;
    }

    // READ
    getFirst(): number | undefined {
        if (this.head === null) {
            return undefined;
        }

        return this.head.data;
    }

    getLast(): number | undefined {
        if (this.tail === null) {
            return undefined;
        }

        return this.tail.data;
    }

    getAt(index: number): number | undefined {
        if (index < 0 || index >= this.length) {
            return undefined;
        }

        let current: ListNode | null = this.head;

        for (let i = 0; i < index; i++) {
            current = current!.next;
        }

        return current!.data;
    }

    printList(): void {
        let current: ListNode | null = this.head;
        const values: number[] = [];

        while (current !== null) {
            values.push(current.data);
            current = current.next;
        }

        console.log("List:", values.length > 0 ? values.join(" -> ") : "Empty");
    }

    // UPDATE
    setAt(index: number, value: number): boolean {
        if (index < 0 || index >= this.length) {
            return false;
        }

        let current: ListNode | null = this.head;

        for (let i = 0; i < index; i++) {
            current = current!.next;
        }

        current!.data = value;
        return true;
    }

    // INSERT
    insertFront(data: number): void {
        const newNode = new ListNode(data);

        newNode.next = this.head;
        this.head = newNode;

        if (this.tail === null) {
            this.tail = newNode;
        }

        this.length++;
    }

    insertBack(data: number): void {
        const newNode = new ListNode(data);

        if (this.tail === null) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            this.tail.next = newNode;
            this.tail = newNode;
        }

        this.length++;
    }

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

        let previous: ListNode | null = this.head;

        for (let i = 0; i < index - 1; i++) {
            previous = previous!.next;
        }

        const newNode = new ListNode(data);

        newNode.next = previous!.next;
        previous!.next = newNode;

        this.length++;
        return true;
    }

    // DELETE
    removeFront(): number | undefined {
        if (this.head === null) {
            return undefined;
        }

        const removedData = this.head.data;

        this.head = this.head.next;
        this.length--;

        if (this.head === null) {
            this.tail = null;
        }

        return removedData;
    }

    removeBack(): number | undefined {
        if (this.head === null) {
            return undefined;
        }

        const removedData = this.tail!.data;

        // Only one node exists
        if (this.head === this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            let current: ListNode = this.head;

            // Find the node before the tail
            while (current.next !== this.tail) {
                current = current.next!;
            }

            this.tail = current;
            this.tail.next = null;
        }

        this.length--;
        return removedData;
    }

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

        let previous: ListNode | null = this.head;

        for (let i = 0; i < index - 1; i++) {
            previous = previous!.next;
        }

        const removedNode = previous!.next;

        if (removedNode === null) {
            return undefined;
        }

        previous!.next = removedNode.next;
        this.length--;

        return removedNode.data;
    }

    // SIZE
    sizeOf(): number {
        return this.length;
    }

    // CHECK
    isEmpty(): boolean {
        return this.length === 0;
    }

    // CLEAR
    clearList(): void {
        this.head = null;
        this.tail = null;
        this.length = 0;
    }
}

// DEMONSTRATION

const list = new SinglyLinkedList();

console.log("=== SINGLY LINKED LIST ===");

// Insert elements
console.log("\n--- INSERT ---");

list.insertFront(20);
list.insertFront(10);
list.insertBack(30);
list.insertBack(40);

list.printList();

list.insertAt(2, 25);
console.log("After inserting 25 at index 2:");
list.printList();

// Read elements
console.log("\n--- READ ---");

console.log("First element:", list.getFirst());
console.log("Last element:", list.getLast());
console.log("Element at index 2:", list.getAt(2));

// Update an element
console.log("\n--- UPDATE ---");

list.setAt(2, 99);
console.log("After updating index 2 to 99:");
list.printList();

// Delete elements
console.log("\n--- DELETE ---");

console.log("Removed from front:", list.removeFront());
list.printList();

console.log("Removed from back:", list.removeBack());
list.printList();

console.log("Removed from index 1:", list.removeAt(1));
list.printList();

// Size and empty check
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", list.sizeOf());
console.log("Is empty:", list.isEmpty());

// Clear the list
console.log("\n--- CLEAR ---");

list.clearList();
list.printList();

console.log("Size after clearing:", list.sizeOf());
console.log("Is empty:", list.isEmpty());