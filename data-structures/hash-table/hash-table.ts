class HashEntry {
    key: string;
    value: number;

    constructor(key: string, value: number) {
        this.key = key;
        this.value = value;
    }
}

// Marks a slot that previously contained a deleted entry.
const DELETED = Symbol("DELETED");

class HashTable {
    private table: (HashEntry | null | typeof DELETED)[];
    private capacity: number;
    private count: number;
    private deletedCount: number;

    constructor() {
        this.capacity = 8;

        this.table = new Array<HashEntry | null | typeof DELETED>(
            this.capacity
        ).fill(null);

        this.count = 0;
        this.deletedCount = 0;
    }

    // HASH: Convert a string key into an array index.
    private hashKey(key: string): number {
        let hashValue = 0;

        for (let i = 0; i < key.length; i++) {
            hashValue =
                (hashValue * 31 + key.charCodeAt(i)) % this.capacity;
        }

        return hashValue;
    }

    // Find an existing key.
    private findIndex(key: string): number {
        let index = this.hashKey(key);

        for (let i = 0; i < this.capacity; i++) {
            const entry = this.table[index];

            if (entry === null || entry === undefined) {
                return -1;
            }

            if (entry !== DELETED && entry.key === key) {
                return index;
            }

            index = (index + 1) % this.capacity;
        }

        return -1;
    }

    // Find an available slot for insertion.
    // Prefer the first deleted slot encountered.
    private findInsertIndex(key: string): number {
        let index = this.hashKey(key);
        let firstDeleted = -1;

        for (let i = 0; i < this.capacity; i++) {
            const entry = this.table[index];

            if (entry === null || entry === undefined) {
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

    // Insert an existing entry without triggering another resize.
    private insertWithoutResize(entry: HashEntry): void {
        let index = this.hashKey(entry.key);

        for (let i = 0; i < this.capacity; i++) {
            const current = this.table[index];

            if (current === null || current === undefined) {
                this.table[index] = entry;
                this.count++;
                return;
            }

            index = (index + 1) % this.capacity;
        }

        throw new Error("No available slot during rehashing");
    }

    // RESIZE: Create a larger table and reinsert active entries.
    private resize(newCapacity: number): void {
        const oldTable = this.table;

        this.capacity = newCapacity;

        this.table = new Array<HashEntry | null | typeof DELETED>(
            this.capacity
        ).fill(null);

        this.count = 0;
        this.deletedCount = 0;

        for (let i = 0; i < oldTable.length; i++) {
            const entry = oldTable[i];

            if (
                entry !== null &&
                entry !== undefined &&
                entry !== DELETED
            ) {
                this.insertWithoutResize(entry);
            }
        }
    }

    // SET: Insert a key-value pair or update an existing key.
    set(key: string, value: number): void {
        const existingIndex = this.findIndex(key);

        // Update an existing key.
        if (existingIndex !== -1) {
            const entry = this.table[existingIndex];

            if (
                entry !== null &&
                entry !== undefined &&
                entry !== DELETED
            ) {
                entry.value = value;
            }

            return;
        }

        // Resize when occupied and deleted slots exceed 70%.
        if (
            (this.count + this.deletedCount + 1) * 10
            > this.capacity * 7
        ) {
            this.resize(this.capacity * 2);
        }

        let index = this.findInsertIndex(key);

        if (index === -1) {
            this.resize(this.capacity * 2);
            index = this.findInsertIndex(key);
        }

        if (index === -1) {
            throw new Error("No available slot in hash table");
        }

        if (this.table[index] === DELETED) {
            this.deletedCount--;
        }

        this.table[index] = new HashEntry(key, value);
        this.count++;
    }

    // GET: Retrieve the value associated with a key.
    get(key: string): number | undefined {
        const index = this.findIndex(key);

        if (index === -1) {
            return undefined;
        }

        const entry = this.table[index];

        if (
            entry === null ||
            entry === undefined ||
            entry === DELETED
        ) {
            return undefined;
        }

        return entry.value;
    }

    // CONTAINS: Check whether a key exists.
    contains(key: string): boolean {
        return this.findIndex(key) !== -1;
    }

    // REMOVE: Delete a key-value pair.
    remove(key: string): boolean {
        const index = this.findIndex(key);

        if (index === -1) {
            return false;
        }

        this.table[index] = DELETED;

        this.count--;
        this.deletedCount++;

        return true;
    }

    // SIZE: Get the number of active entries.
    sizeOf(): number {
        return this.count;
    }

    // CHECK: Check whether the table is empty.
    isEmpty(): boolean {
        return this.count === 0;
    }

    // DISPLAY: Show the internal table.
    printTable(): void {
        console.log("Hash Table:");

        for (let i = 0; i < this.capacity; i++) {
            const entry = this.table[i];

            if (entry === null || entry === undefined) {
                console.log(`[${i}] Empty`);
            } else if (entry === DELETED) {
                console.log(`[${i}] Deleted`);
            } else {
                console.log(`[${i}] ${entry.key}: ${entry.value}`);
            }
        }
    }

    // CLEAR: Remove all entries while retaining capacity.
    clearTable(): void {
        this.table.fill(null);

        this.count = 0;
        this.deletedCount = 0;
    }
}

// DEMONSTRATION

const table = new HashTable();

console.log("==== HASH TABLE ====");

// SET
console.log("\n--- SET ---");

table.set("apple", 100);
table.set("banana", 200);
table.set("orange", 300);
table.set("grape", 400);
table.set("mango", 500);
table.set("lemon", 600);

table.printTable();

// UPDATE
console.log("\n--- UPDATE ---");

table.set("banana", 250);

console.log("After updating banana:");
console.log("banana:", table.get("banana"));

// GET
console.log("\n--- GET ---");

console.log("apple:", table.get("apple"));
console.log("mango:", table.get("mango"));
console.log("Unknown key:", table.get("unknown"));

// CONTAINS
console.log("\n--- CONTAINS ---");

console.log("Contains apple:", table.contains("apple"));
console.log("Contains unknown:", table.contains("unknown"));

// REMOVE
console.log("\n--- REMOVE ---");

console.log("Removed orange:", table.remove("orange"));
console.log("Remove unknown:", table.remove("unknown"));

table.printTable();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", table.sizeOf());
console.log("Is empty:", table.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

table.clearTable();

console.log("Size after clearing:", table.sizeOf());
console.log("Is empty:", table.isEmpty());

table.printTable();

// INSERT AFTER CLEAR
console.log("\n--- INSERT AFTER CLEAR ---");

table.set("mango", 500);

table.printTable();