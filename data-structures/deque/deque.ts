class Deque {
    private buffer: (number | undefined)[];
    private capacity: number;
    private frontIndex: number;
    private count: number;

    constructor() {
        this.capacity = 4;
        this.buffer = new Array<number | undefined>(this.capacity);
        this.frontIndex = 0;
        this.count = 0;
    }

    // Increase capacity when the deque is full.
    private grow(): void {
        const newCapacity = this.capacity * 2;
        const newBuffer = new Array<number | undefined>(newCapacity);

        // Copy elements in their logical order.
        for (let i = 0; i < this.count; i++) {
            const oldIndex = (this.frontIndex + i) % this.capacity;
            newBuffer[i] = this.buffer[oldIndex];
        }

        this.buffer = newBuffer;
        this.capacity = newCapacity;
        this.frontIndex = 0;
    }

    // PUSH FRONT: Insert an element at the front.
    pushFront(value: number): void {
        if (this.count === this.capacity) {
            this.grow();
        }

        this.frontIndex =
            (this.frontIndex - 1 + this.capacity) % this.capacity;

        this.buffer[this.frontIndex] = value;
        this.count++;
    }

    // PUSH BACK: Insert an element at the rear.
    pushBack(value: number): void {
        if (this.count === this.capacity) {
            this.grow();
        }

        const rearIndex =
            (this.frontIndex + this.count) % this.capacity;

        this.buffer[rearIndex] = value;
        this.count++;
    }

    // POP FRONT: Remove and return the front element.
    popFront(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        const removedValue = this.buffer[this.frontIndex];

        this.buffer[this.frontIndex] = undefined;

        this.frontIndex = (this.frontIndex + 1) % this.capacity;
        this.count--;

        if (this.count === 0) {
            this.frontIndex = 0;
        }

        return removedValue;
    }

    // POP BACK: Remove and return the rear element.
    popBack(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        const rearIndex =
            (this.frontIndex + this.count - 1) % this.capacity;

        const removedValue = this.buffer[rearIndex];

        this.buffer[rearIndex] = undefined;
        this.count--;

        if (this.count === 0) {
            this.frontIndex = 0;
        }

        return removedValue;
    }

    // READ: Get the front element without removing it.
    getFront(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        return this.buffer[this.frontIndex];
    }

    // READ: Get the rear element without removing it.
    getRear(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        const rearIndex =
            (this.frontIndex + this.count - 1) % this.capacity;

        return this.buffer[rearIndex];
    }

    // SIZE: Get the number of elements.
    sizeOf(): number {
        return this.count;
    }

    // CHECK: Check whether the deque is empty.
    isEmpty(): boolean {
        return this.count === 0;
    }

    // DISPLAY: Show elements from front to rear.
    printDeque(): void {
        if (this.isEmpty()) {
            console.log("Deque: Front -> Rear (Empty)");
            return;
        }

        const values: string[] = [];

        for (let i = 0; i < this.count; i++) {
            const index = (this.frontIndex + i) % this.capacity;
            values.push(String(this.buffer[index]));
        }

        console.log("Deque: Front ->", values.join(" <-> "), "-> Rear");
    }

    // CLEAR: Remove all elements without changing capacity.
    clearDeque(): void {
        this.frontIndex = 0;
        this.count = 0;
    }
}

// DEMONSTRATION

const deque = new Deque();

console.log("==== DEQUE ====");

// INSERT
console.log("\n--- INSERT ---");

deque.pushBack(10);
deque.pushBack(20);
deque.pushBack(30);

deque.printDeque();

deque.pushFront(5);

console.log("After pushing 5 at the front:");
deque.printDeque();

// This insertion triggers an increase in capacity.
deque.pushBack(40);

console.log("After pushing 40 at the rear:");
deque.printDeque();

// READ
console.log("\n--- READ ---");

console.log("Front element:", deque.getFront());
console.log("Rear element:", deque.getRear());

// DELETE
console.log("\n--- DELETE ---");

console.log("Removed from front:", deque.popFront());
deque.printDeque();

console.log("Removed from back:", deque.popBack());
deque.printDeque();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", deque.sizeOf());
console.log("Is empty:", deque.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

deque.clearDeque();

deque.printDeque();

console.log("Size after clearing:", deque.sizeOf());
console.log("Is empty:", deque.isEmpty());

// EMPTY DEQUE CHECK
console.log("\n--- EMPTY DEQUE CHECK ---");

console.log("Pop from front:", deque.popFront());
console.log("Pop from back:", deque.popBack());
console.log("Get front:", deque.getFront());
console.log("Get rear:", deque.getRear());