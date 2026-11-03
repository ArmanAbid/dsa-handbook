#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HashTable {
private:
    enum EntryState {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Entry {
        string key;
        int value;
        EntryState state;

        Entry() {
            key = "";
            value = 0;
            state = EMPTY;
        }
    };

    vector<Entry> table;
    int capacity;
    int count;
    int deletedCount;

    // HASH: Convert a string key into an array index.
    int hashKey(const string& key) const {
        unsigned long hash = 0;

        for (unsigned int i = 0; i < key.length(); i++) {
            hash = (hash * 31 +
                    static_cast<unsigned char>(key[i])) % capacity;
        }

        return static_cast<int>(hash);
    }

    // Find an existing key.
    int findIndex(const string& key) const {
        int index = hashKey(key);

        for (int i = 0; i < capacity; i++) {
            const Entry& entry = table[index];

            if (entry.state == EMPTY) {
                return -1;
            }

            if (entry.state == OCCUPIED && entry.key == key) {
                return index;
            }

            index = (index + 1) % capacity;
        }

        return -1;
    }

    // Find an available slot for insertion.
    // Prefer the first deleted slot encountered.
    int findInsertIndex(const string& key) const {
        int index = hashKey(key);
        int firstDeleted = -1;

        for (int i = 0; i < capacity; i++) {
            const Entry& entry = table[index];

            if (entry.state == EMPTY) {
                if (firstDeleted != -1) {
                    return firstDeleted;
                }

                return index;
            }

            if (entry.state == DELETED && firstDeleted == -1) {
                firstDeleted = index;
            }

            index = (index + 1) % capacity;
        }

        return firstDeleted;
    }

    // Insert an existing entry without triggering another resize.
    void insertWithoutResize(const Entry& entry) {
        int index = hashKey(entry.key);

        while (table[index].state == OCCUPIED) {
            index = (index + 1) % capacity;
        }

        table[index].key = entry.key;
        table[index].value = entry.value;
        table[index].state = OCCUPIED;

        count++;
    }

    // RESIZE: Create a larger table and reinsert active entries.
    void resizeTable(int newCapacity) {
        vector<Entry> oldTable = table;

        capacity = newCapacity;
        table.clear();
        table.resize(capacity);

        count = 0;
        deletedCount = 0;

        for (unsigned int i = 0; i < oldTable.size(); i++) {
            if (oldTable[i].state == OCCUPIED) {
                insertWithoutResize(oldTable[i]);
            }
        }
    }

public:
    // CREATE: Initialize an empty hash table.
    HashTable() : table(8) {
        capacity = 8;
        count = 0;
        deletedCount = 0;
    }

    // SET: Insert a key-value pair or update an existing key.
    void set(const string& key, int value) {
        int existingIndex = findIndex(key);

        // Update an existing key.
        if (existingIndex != -1) {
            table[existingIndex].value = value;
            return;
        }

        // Resize when occupied and deleted slots exceed 70%.
        if ((count + deletedCount + 1) * 10 > capacity * 7) {
            resizeTable(capacity * 2);
        }

        int index = findInsertIndex(key);

        if (index == -1) {
            resizeTable(capacity * 2);
            index = findInsertIndex(key);
        }

        if (table[index].state == DELETED) {
            deletedCount--;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].state = OCCUPIED;

        count++;
    }

    // GET: Retrieve the value associated with a key.
    bool get(const string& key, int& value) const {
        int index = findIndex(key);

        if (index == -1) {
            return false;
        }

        value = table[index].value;
        return true;
    }

    // CONTAINS: Check whether a key exists.
    bool contains(const string& key) const {
        return findIndex(key) != -1;
    }

    // REMOVE: Delete a key-value pair.
    bool remove(const string& key) {
        int index = findIndex(key);

        if (index == -1) {
            return false;
        }

        table[index].key.clear();
        table[index].value = 0;
        table[index].state = DELETED;

        count--;
        deletedCount++;

        return true;
    }

    // SIZE: Get the number of active entries.
    int sizeOf() const {
        return count;
    }

    // CHECK: Check whether the table is empty.
    bool isEmpty() const {
        return count == 0;
    }

    // DISPLAY: Show the internal table.
    void printTable() const {
        cout << "Hash Table:" << endl;

        for (int i = 0; i < capacity; i++) {
            cout << "[" << i << "] ";

            if (table[i].state == EMPTY) {
                cout << "Empty";
            } else if (table[i].state == DELETED) {
                cout << "Deleted";
            } else {
                cout << table[i].key << ": "
                     << table[i].value;
            }

            cout << endl;
        }
    }

    // CLEAR: Remove all entries while retaining capacity.
    void clearTable() {
        for (int i = 0; i < capacity; i++) {
            table[i].key.clear();
            table[i].value = 0;
            table[i].state = EMPTY;
        }

        count = 0;
        deletedCount = 0;
    }
};

// DEMONSTRATION

int main() {
    HashTable table;
    int value;

    cout << "==== HASH TABLE ====" << endl;

    // SET
    cout << "\n--- SET ---" << endl;

    table.set("apple", 100);
    table.set("banana", 200);
    table.set("orange", 300);
    table.set("grape", 400);

    table.printTable();

    // UPDATE
    cout << "\n--- UPDATE ---" << endl;

    table.set("banana", 250);

    cout << "After updating banana:" << endl;

    if (table.get("banana", value)) {
        cout << "banana: " << value << endl;
    }

    // GET
    cout << "\n--- GET ---" << endl;

    if (table.get("apple", value)) {
        cout << "apple: " << value << endl;
    }

    if (!table.get("mango", value)) {
        cout << "mango was not found." << endl;
    }

    // CONTAINS
    cout << "\n--- CONTAINS ---" << endl;

    cout << "Contains apple: "
         << (table.contains("apple") ? "Yes" : "No") << endl;

    cout << "Contains mango: "
         << (table.contains("mango") ? "Yes" : "No") << endl;

    // REMOVE
    cout << "\n--- REMOVE ---" << endl;

    if (table.remove("orange")) {
        cout << "Removed orange." << endl;
    }

    table.printTable();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << table.sizeOf() << endl;
    cout << "Is empty: " << (table.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    table.clearTable();

    cout << "Size after clearing: " << table.sizeOf() << endl;
    cout << "Is empty: " << (table.isEmpty() ? "Yes" : "No") << endl;

    table.printTable();

    // INSERT AFTER CLEAR
    cout << "\n--- INSERT AFTER CLEAR ---" << endl;

    table.set("mango", 500);

    table.printTable();

    return 0;
}