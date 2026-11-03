class Queue {
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

    // Increase capacity when the queue is full.
    private grow(): void {
        const newCapacity = this.capacity * 2;
        const newBuffer = new Array<number | undefined>(newCapacity);

        // Copy elements in their logical queue order.
        for (let i = 0; i < this.count; i++) {
            const oldIndex = (this.frontIndex + i) % this.capacity;
            newBuffer[i] = this.buffer[oldIndex];
        }

        this.buffer = newBuffer;
        this.capacity = newCapacity;
        this.frontIndex = 0;
    }

    // ENQUEUE: Add an element at the rear.
    enqueue(value: number): void {
        if (this.count === this.capacity) {
            this.grow();
        }

        const rearIndex =
            (this.frontIndex + this.count) % this.capacity;

        this.buffer[rearIndex] = value;
        this.count++;
    }

    // DEQUEUE: Remove and return the front element.
    dequeue(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        const removedValue = this.buffer[this.frontIndex];

        // Release the slot for future use.
        this.buffer[this.frontIndex] = undefined;

        this.frontIndex = (this.frontIndex + 1) % this.capacity;
        this.count--;

        // Reset the front position when the queue becomes empty.
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

    // CHECK: Check whether the queue is empty.
    isEmpty(): boolean {
        return this.count === 0;
    }

    // DISPLAY: Show elements from front to rear.
    printQueue(): void {
        if (this.isEmpty()) {
            console.log("Queue: Front -> Rear (Empty)");
            return;
        }

        const values: string[] = [];

        for (let i = 0; i < this.count; i++) {
            const index = (this.frontIndex + i) % this.capacity;
            values.push(String(this.buffer[index]));
        }

        console.log("Queue: Front ->", values.join(" -> "), "-> Rear");
    }

    // CLEAR: Remove all elements without changing capacity.
    clearQueue(): void {
        this.frontIndex = 0;
        this.count = 0;
    }
}

// DEMONSTRATION

const queue = new Queue();

console.log("==== QUEUE ====");

// ENQUEUE
console.log("\n--- ENQUEUE ---");

queue.enqueue(10);
queue.enqueue(20);
queue.enqueue(30);
queue.enqueue(40);

queue.printQueue();

// This insertion triggers an increase in capacity.
queue.enqueue(50);

console.log("After enqueuing 50:");
queue.printQueue();

// READ
console.log("\n--- READ ---");

console.log("Front element:", queue.getFront());
console.log("Rear element:", queue.getRear());

// DEQUEUE
console.log("\n--- DEQUEUE ---");

console.log("Removed element:", queue.dequeue());
queue.printQueue();

console.log("Removed element:", queue.dequeue());
queue.printQueue();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", queue.sizeOf());
console.log("Is empty:", queue.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

queue.clearQueue();

queue.printQueue();

console.log("Size after clearing:", queue.sizeOf());
console.log("Is empty:", queue.isEmpty());

// EMPTY QUEUE CHECK
console.log("\n--- EMPTY QUEUE CHECK ---");

console.log("Dequeue from empty queue:", queue.dequeue());
console.log("Get front from empty queue:", queue.getFront());
console.log("Get rear from empty queue:", queue.getRear());