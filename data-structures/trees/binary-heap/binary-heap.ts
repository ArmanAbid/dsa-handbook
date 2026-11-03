class BinaryHeap {
    private elements: number[];
    private isMinHeap: boolean;

    constructor(isMinHeap: boolean = true) {
        this.elements = [];
        this.isMinHeap = isMinHeap;
    }

    // Check whether the first value has higher priority.
    private hasHigherPriority(first: number, second: number): boolean {
        if (this.isMinHeap) {
            return first < second;
        }

        return first > second;
    }

    // Swap two elements.
    private swap(first: number, second: number): void {
        const firstValue = this.elements[first];
        const secondValue = this.elements[second];

        if (firstValue === undefined || secondValue === undefined) {
            return;
        }

        this.elements[first] = secondValue;
        this.elements[second] = firstValue;
    }

    // SIFT UP: Restore the heap property after insertion.
    private siftUp(index: number): void {
        while (index > 0) {
            const parent = Math.floor((index - 1) / 2);

            const currentValue = this.elements[index];
            const parentValue = this.elements[parent];

            if (
                currentValue === undefined ||
                parentValue === undefined
            ) {
                break;
            }

            if (!this.hasHigherPriority(currentValue, parentValue)) {
                break;
            }

            this.swap(index, parent);
            index = parent;
        }
    }

    // SIFT DOWN: Restore the heap property after extraction.
    private siftDown(index: number): void {
        const length = this.elements.length;

        while (true) {
            let best = index;

            const left = 2 * index + 1;
            const right = 2 * index + 2;

            const bestValue = this.elements[best];

            if (bestValue === undefined) {
                break;
            }

            // Check the left child.
            const leftValue = this.elements[left];

            if (
                left < length &&
                leftValue !== undefined &&
                this.hasHigherPriority(leftValue, bestValue)
            ) {
                best = left;
            }

            // Check the right child.
            const rightValue = this.elements[right];
            const currentBest = this.elements[best];

            if (
                right < length &&
                rightValue !== undefined &&
                currentBest !== undefined &&
                this.hasHigherPriority(rightValue, currentBest)
            ) {
                best = right;
            }

            // Heap property is already satisfied.
            if (best === index) {
                break;
            }

            this.swap(index, best);
            index = best;
        }
    }

    // INSERT: Add a value to the heap.
    insert(value: number): void {
        this.elements.push(value);

        // Move the new element to its correct position.
        this.siftUp(this.elements.length - 1);
    }

    // PEEK: Read the root without removing it.
    peek(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        return this.elements[0];
    }

    // EXTRACT ROOT: Remove and return the root.
    extractRoot(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        const removedValue = this.elements[0];

        if (removedValue === undefined) {
            return undefined;
        }

        // If only one element exists, remove it directly.
        if (this.elements.length === 1) {
            this.elements.pop();
            return removedValue;
        }

        // Move the last element to the root.
        const lastValue = this.elements.pop();

        if (lastValue === undefined) {
            return undefined;
        }

        this.elements[0] = lastValue;

        // Restore the heap property.
        this.siftDown(0);

        return removedValue;
    }

    // CONTAINS: Check whether a value exists.
    contains(value: number): boolean {
        return this.elements.includes(value);
    }

    // SIZE: Get the number of elements.
    sizeOf(): number {
        return this.elements.length;
    }

    // CHECK: Check whether the heap is empty.
    isEmpty(): boolean {
        return this.elements.length === 0;
    }

    // DISPLAY: Show the internal array representation.
    printHeap(): void {
        console.log("Heap:", this.elements);
    }

    // CLEAR: Remove all elements.
    clearHeap(): void {
        this.elements.length = 0;
    }
}

// DEMONSTRATION

console.log("==== BINARY HEAP ====");

// MIN HEAP

const minHeap = new BinaryHeap(true);

console.log("\n==== MIN HEAP ====");

// INSERT
console.log("\n--- INSERT ---");

[40, 20, 30, 10, 50, 5, 35].forEach(value => {
    minHeap.insert(value);
});

minHeap.printHeap();

// PEEK
console.log("\n--- PEEK ---");

console.log("Minimum element:", minHeap.peek());

// CONTAINS
console.log("\n--- CONTAINS ---");

console.log("Contains 30:", minHeap.contains(30));
console.log("Contains 100:", minHeap.contains(100));

// EXTRACT ROOT
console.log("\n--- EXTRACT ROOT ---");

console.log("Extracted minimum:", minHeap.extractRoot());
minHeap.printHeap();

console.log("Extracted minimum:", minHeap.extractRoot());
minHeap.printHeap();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", minHeap.sizeOf());
console.log("Is empty:", minHeap.isEmpty());

// CLEAR
console.log("\n--- CLEAR MIN HEAP ---");

minHeap.clearHeap();

minHeap.printHeap();

console.log("Size after clearing:", minHeap.sizeOf());

// EMPTY HEAP CHECK
console.log("\n--- EMPTY MIN HEAP CHECK ---");

console.log("Extract from empty heap:", minHeap.extractRoot());
console.log("Peek into empty heap:", minHeap.peek());

// INSERT AFTER CLEAR
minHeap.insert(15);
minHeap.insert(8);

console.log("After inserting again:");
minHeap.printHeap();

// MAX HEAP

const maxHeap = new BinaryHeap(false);

console.log("\n==== MAX HEAP ====");

// INSERT
[40, 20, 30, 10, 50, 5, 35].forEach(value => {
    maxHeap.insert(value);
});

maxHeap.printHeap();

// PEEK
console.log("\n--- PEEK ---");

console.log("Maximum element:", maxHeap.peek());

// EXTRACT ROOT
console.log("\n--- EXTRACT ROOT ---");

console.log("Extracted maximum:", maxHeap.extractRoot());
maxHeap.printHeap();