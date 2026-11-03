#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HashSet {
private:
    enum EntryState {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Entry {
        string value;
        EntryState state;

        Entry() {
            value = "";
            state = EMPTY;
        }
    };

    vector<Entry> table;
    int capacity;
    int count;
    int deletedCount;

    // HASH: Convert a string into an array index.
    int hashValue(const string& value) const {
        unsigned long hash = 0;

        for (unsigned int i = 0; i < value.length(); i++) {
            hash = (
                hash * 31 +
                static_cast<unsigned char>(value[i])
            ) % capacity;
        }

        return static_cast<int>(hash);
    }

    // Find an existing element.
    int findIndex(const string& value) const {
        int index = hashValue(value);

        for (int i = 0; i < capacity; i++) {
            const Entry& entry = table[index];

            if (entry.state == EMPTY) {
                return -1;
            }

            if (entry.state == OCCUPIED && entry.value == value) {
                return index;
            }

            index = (index + 1) % capacity;
        }

        return -1;
    }

    // Find an available slot for insertion.
    // Prefer the first deleted slot encountered.
    int findInsertIndex(const string& value) const {
        int index = hashValue(value);
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

    // Insert an existing element without triggering another resize.
    void insertWithoutResize(const string& value) {
        int index = hashValue(value);

        while (table[index].state == OCCUPIED) {
            index = (index + 1) % capacity;
        }

        table[index].value = value;
        table[index].state = OCCUPIED;

        count++;
    }

    // RESIZE: Create a larger table and reinsert active elements.
    void resizeTable(int newCapacity) {
        vector<Entry> oldTable = table;

        capacity = newCapacity;
        table.clear();
        table.resize(capacity);

        count = 0;
        deletedCount = 0;

        for (unsigned int i = 0; i < oldTable.size(); i++) {
            if (oldTable[i].state == OCCUPIED) {
                insertWithoutResize(oldTable[i].value);
            }
        }
    }

public:
    // CREATE: Initialize an empty set.
    HashSet() : table(8) {
        capacity = 8;
        count = 0;
        deletedCount = 0;
    }

    // ADD: Insert an element if it does not already exist.
    bool add(const string& value) {
        // Prevent duplicate elements.
        if (contains(value)) {
            return false;
        }

        // Resize when occupied and deleted slots exceed 70%.
        if ((count + deletedCount + 1) * 10 > capacity * 7) {
            resizeTable(capacity * 2);
        }

        int index = findInsertIndex(value);

        if (index == -1) {
            resizeTable(capacity * 2);
            index = findInsertIndex(value);
        }

        if (table[index].state == DELETED) {
            deletedCount--;
        }

        table[index].value = value;
        table[index].state = OCCUPIED;

        count++;
        return true;
    }

    // CONTAINS: Check whether an element exists.
    bool contains(const string& value) const {
        return findIndex(value) != -1;
    }

    // REMOVE: Delete an element.
    bool remove(const string& value) {
        int index = findIndex(value);

        if (index == -1) {
            return false;
        }

        table[index].value.clear();
        table[index].state = DELETED;

        count--;
        deletedCount++;

        return true;
    }

    // SIZE: Get the number of active elements.
    int sizeOf() const {
        return count;
    }

    // CHECK: Check whether the set is empty.
    bool isEmpty() const {
        return count == 0;
    }

    // DISPLAY: Show all active elements.
    void printSet() const {
        cout << "Set: { ";

        bool first = true;

        for (int i = 0; i < capacity; i++) {
            if (table[i].state == OCCUPIED) {
                if (!first) {
                    cout << ", ";
                }

                cout << table[i].value;
                first = false;
            }
        }

        if (first) {
            cout << "Empty";
        }

        cout << " }" << endl;
    }

    // CLEAR: Remove all elements while retaining capacity.
    void clearSet() {
        for (int i = 0; i < capacity; i++) {
            table[i].value.clear();
            table[i].state = EMPTY;
        }

        count = 0;
        deletedCount = 0;
    }
};

// DEMONSTRATION

int main() {
    HashSet set;

    cout << "==== HASH SET ====" << endl;

    // ADD
    cout << "\n--- ADD ---" << endl;

    set.add("apple");
    set.add("banana");
    set.add("orange");
    set.add("grape");

    set.printSet();

    // Try adding a duplicate.
    cout << "Adding apple again: "
         << (set.add("apple") ? "Added" : "Already exists") << endl;

    set.printSet();

    // CONTAINS
    cout << "\n--- CONTAINS ---" << endl;

    cout << "Contains apple: "
         << (set.contains("apple") ? "Yes" : "No") << endl;

    cout << "Contains mango: "
         << (set.contains("mango") ? "Yes" : "No") << endl;

    // REMOVE
    cout << "\n--- REMOVE ---" << endl;

    cout << "Remove banana: "
         << (set.remove("banana") ? "Removed" : "Not found") << endl;

    cout << "Remove mango: "
         << (set.remove("mango") ? "Removed" : "Not found") << endl;

    set.printSet();

    // Check that other elements are still accessible.
    cout << "Contains orange after removal: "
         << (set.contains("orange") ? "Yes" : "No") << endl;

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << set.sizeOf() << endl;
    cout << "Is empty: " << (set.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    set.clearSet();

    set.printSet();

    cout << "Size after clearing: " << set.sizeOf() << endl;
    cout << "Is empty: " << (set.isEmpty() ? "Yes" : "No") << endl;

    // ADD AFTER CLEAR
    cout << "\n--- ADD AFTER CLEAR ---" << endl;

    set.add("mango");
    set.add("lemon");

    set.printSet();

    return 0;
}