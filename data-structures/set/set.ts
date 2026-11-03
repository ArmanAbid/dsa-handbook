const DELETED = Symbol("DELETED");

class HashSet {
    private table: (string | null | typeof DELETED)[];
    private capacity: number;
    private count: number;
    private deletedCount: number;

    constructor() {
        this.capacity = 8;
        this.table = new Array<string | null | typeof DELETED>(
            this.capacity
        ).fill(null);

        this.count = 0;
        this.deletedCount = 0;
    }

    // HASH: Convert a string into an array index.
    private hashValue(value: string): number {
        let hashValue = 0;

        for (let i = 0; i < value.length; i++) {
            hashValue =
                (hashValue * 31 + value.charCodeAt(i)) % this.capacity;
        }

        return hashValue;
    }

    // Find an existing element.
    private findIndex(value: string): number {
        let index = this.hashValue(value);

        for (let i = 0; i < this.capacity; i++) {
            const entry = this.table[index];

            if (entry === null) {
                return -1;
            }

            if (entry !== DELETED && entry === value) {
                return index;
            }

            index = (index + 1) % this.capacity;
        }

        return -1;
    }

    // Find an available slot for insertion.
    // Prefer the first deleted slot encountered.
    private findInsertIndex(value: string): number {
        let index = this.hashValue(value);
        let firstDeleted = -1;

        for (let i = 0; i < this.capacity; i++) {
            const entry = this.table[index];

            if (entry === null) {
                if (firstDeleted !== -1) {
                    return firstDeleted;
                }

                return index;
            }

            if (entry === DELETED && firstDeleted === -1) {
                firstDeleted = index;
            }

            index = (index + 1) % this.capacity;
        }

        return firstDeleted;
    }

    // Insert an existing element without triggering another resize.
    private insertWithoutResize(value: string): void {
        let index = this.hashValue(value);

        while (this.table[index] !== null) {
            index = (index + 1) % this.capacity;
        }

        this.table[index] = value;
        this.count++;
    }

    // RESIZE: Create a larger table and reinsert active elements.
    private resize(newCapacity: number): void {
        const oldTable = this.table;

        this.capacity = newCapacity;

        this.table = new Array<string | null | typeof DELETED>(
            this.capacity
        ).fill(null);

        this.count = 0;
        this.deletedCount = 0;

        for (const entry of oldTable) {
            if (entry !== null && entry !== DELETED) {
                this.insertWithoutResize(entry);
            }
        }
    }

    // ADD: Insert an element if it does not already exist.
    add(value: string): boolean {
        // Prevent duplicate elements.
        if (this.contains(value)) {
            return false;
        }

        // Resize when occupied and deleted slots exceed 70%.
        if (
            (this.count + this.deletedCount + 1) * 10
            > this.capacity * 7
        ) {
            this.resize(this.capacity * 2);
        }

        let index = this.findInsertIndex(value);

        if (index === -1) {
            this.resize(this.capacity * 2);
            index = this.findInsertIndex(value);
        }

        if (index === -1) {
            throw new Error("No available slot in hash set");
        }

        if (this.table[index] === DELETED) {
            this.deletedCount--;
        }

        this.table[index] = value;
        this.count++;

        return true;
    }

    // CONTAINS: Check whether an element exists.
    contains(value: string): boolean {
        return this.findIndex(value) !== -1;
    }

    // REMOVE: Delete an element.
    remove(value: string): boolean {
        const index = this.findIndex(value);

        if (index === -1) {
            return false;
        }

        this.table[index] = DELETED;

        this.count--;
        this.deletedCount++;

        return true;
    }

    // SIZE: Get the number of active elements.
    sizeOf(): number {
        return this.count;
    }

    // CHECK: Check whether the set is empty.
    isEmpty(): boolean {
        return this.count === 0;
    }

    // DISPLAY: Show all active elements.
    printSet(): void {
        const values: string[] = [];

        for (const entry of this.table) {
            if (entry !== null && entry !== DELETED) {
                values.push(entry);
            }
        }

        if (values.length === 0) {
            console.log("Set: { Empty }");
        } else {
            console.log("Set: {", values.join(", "), "}");
        }
    }

    // CLEAR: Remove all elements while retaining capacity.
    clearSet(): void {
        this.table.fill(null);
        this.count = 0;
        this.deletedCount = 0;
    }
}

// DEMONSTRATION

const set = new HashSet();

console.log("==== HASH SET ====");

// ADD
console.log("\n--- ADD ---");

set.add("apple");
set.add("banana");
set.add("orange");
set.add("grape");

set.printSet();

// Try adding a duplicate.
console.log("Adding apple again:", set.add("apple"));

set.printSet();

// CONTAINS
console.log("\n--- CONTAINS ---");

console.log("Contains apple:", set.contains("apple"));
console.log("Contains mango:", set.contains("mango"));

// REMOVE
console.log("\n--- REMOVE ---");

console.log("Remove banana:", set.remove("banana"));
console.log("Remove mango:", set.remove("mango"));

set.printSet();

// Check that other elements are still accessible.
console.log(
    "Contains orange after removal:",
    set.contains("orange")
);

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", set.sizeOf());
console.log("Is empty:", set.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

set.clearSet();

set.printSet();

console.log("Size after clearing:", set.sizeOf());
console.log("Is empty:", set.isEmpty());

// ADD AFTER CLEAR
console.log("\n--- ADD AFTER CLEAR ---");

set.add("mango");
set.add("lemon");

set.printSet();