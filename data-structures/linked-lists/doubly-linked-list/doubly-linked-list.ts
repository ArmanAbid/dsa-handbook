class ListNode {
    data: number;
    prev: ListNode | null;
    next: ListNode | null;

    constructor(data: number) {
        this.data = data;
        this.prev = null;
        this.next = null;
    }
}

class DoublyLinkedList {
    private head: ListNode | null;
    private tail: ListNode | null;
    private length: number;

    constructor() {
        this.head = null;
        this.tail = null;
        this.length = 0;
    }

    // Find a node at a specific index.
    // Start from whichever end is closer.
    private nodeAt(index: number): ListNode | null {
        if (index < 0 || index >= this.length) {
            return null;
        }

        let current: ListNode | null;

        if (index < this.length / 2) {
            current = this.head;

            for (let i = 0; i < index; i++) {
                if (current === null) {
                    return null;
                }

                current = current.next;
            }
        } else {
            current = this.tail;

            for (let i = this.length - 1; i > index; i--) {
                if (current === null) {
                    return null;
                }

                current = current.prev;
            }
        }

        return current;
    }

    // Remove a specific node and return its value.
    private unlinkNode(node: ListNode): number {
        const previousNode = node.prev;
        const nextNode = node.next;

        if (previousNode === null) {
            this.head = nextNode;
        } else {
            previousNode.next = nextNode;
        }

        if (nextNode === null) {
            this.tail = previousNode;
        } else {
            nextNode.prev = previousNode;
        }

        node.prev = null;
        node.next = null;

        this.length--;

        return node.data;
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

    // DISPLAY: Traverse from head to tail.
    printForward(): void {
        let current = this.head;
        const values: number[] = [];

        while (current !== null) {
            values.push(current.data);
            current = current.next;
        }

        console.log(
            "Forward:",
            values.length > 0 ? values.join(" <-> ") : "Empty"
        );
    }

    // DISPLAY: Traverse from tail to head.
    printBackward(): void {
        let current = this.tail;
        const values: number[] = [];

        while (current !== null) {
            values.push(current.data);
            current = current.prev;
        }

        console.log(
            "Backward:",
            values.length > 0 ? values.join(" <-> ") : "Empty"
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
        } else {
            newNode.next = this.head;
            this.head.prev = newNode;
            this.head = newNode;
        }

        this.length++;
    }

    // INSERT: Add an element at the end.
    insertBack(data: number): void {
        const newNode = new ListNode(data);

        if (this.tail === null) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            newNode.prev = this.tail;
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

        const nextNode = this.nodeAt(index);

        if (nextNode === null) {
            return false;
        }

        const previousNode = nextNode.prev;

        if (previousNode === null) {
            return false;
        }

        const newNode = new ListNode(data);

        newNode.prev = previousNode;
        newNode.next = nextNode;

        previousNode.next = newNode;
        nextNode.prev = newNode;

        this.length++;
        return true;
    }

    // DELETE: Remove the first element.
    removeFront(): number | undefined {
        const node = this.head;

        if (node === null) {
            return undefined;
        }

        return this.unlinkNode(node);
    }

    // DELETE: Remove the last element.
    removeBack(): number | undefined {
        const node = this.tail;

        if (node === null) {
            return undefined;
        }

        return this.unlinkNode(node);
    }

    // DELETE: Remove an element at a specific index.
    removeAt(index: number): number | undefined {
        const node = this.nodeAt(index);

        if (node === null) {
            return undefined;
        }

        return this.unlinkNode(node);
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

        while (current !== null) {
            const nextNode = current.next;

            current.prev = null;
            current.next = null;

            current = nextNode;
        }

        this.head = null;
        this.tail = null;
        this.length = 0;
    }
}

// DEMONSTRATION

const list = new DoublyLinkedList();

console.log("==== DOUBLY LINKED LIST ====");

// INSERT
console.log("\n--- INSERT ---");

list.insertFront(20);
list.insertFront(10);
list.insertBack(30);
list.insertBack(40);

list.printForward();
list.printBackward();

list.insertAt(2, 25);

console.log("After inserting 25 at index 2:");
list.printForward();

// READ
console.log("\n--- READ ---");

console.log("First element:", list.getFirst());
console.log("Last element:", list.getLast());
console.log("Element at index 2:", list.getAt(2));

// UPDATE
console.log("\n--- UPDATE ---");

list.setAt(2, 99);

console.log("After updating index 2 to 99:");
list.printForward();

// DELETE
console.log("\n--- DELETE ---");

console.log("Removed from front:", list.removeFront());
list.printForward();

console.log("Removed from back:", list.removeBack());
list.printForward();

console.log("Removed from index 1:", list.removeAt(1));
list.printForward();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", list.sizeOf());
console.log("Is empty:", list.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

list.clearList();

list.printForward();

console.log("Size after clearing:", list.sizeOf());
console.log("Is empty:", list.isEmpty());