from typing import List, Optional

# Represents an occupied slot.
class _Entry:
    def __init__(self, key: str, value: int):
        self.key = key
        self.value = value


# Marks a slot that previously contained a deleted entry.
_DELETED = object()


class HashTable:
    def __init__(self):
        self._capacity = 8
        self._table: List[object] = [None] * self._capacity
        self._count = 0
        self._deleted_count = 0

    # HASH: Convert a string key into an array index.
    def _hash_key(self, key: str) -> int:
        hash_value = 0

        for char in key:
            hash_value = (
                hash_value * 31 + ord(char)
            ) % self._capacity

        return hash_value

    # Find an existing key.
    def _find_index(self, key: str) -> Optional[int]:
        index = self._hash_key(key)

        for _ in range(self._capacity):
            entry = self._table[index]

            if entry is None:
                return None

            if entry is not _DELETED:
                assert isinstance(entry, _Entry)

                if entry.key == key:
                    return index

            index = (index + 1) % self._capacity

        return None

    # Find an available slot for insertion.
    # Prefer the first deleted slot encountered.
    def _find_insert_index(self, key: str) -> Optional[int]:
        index = self._hash_key(key)
        first_deleted = None

        for _ in range(self._capacity):
            entry = self._table[index]

            if entry is None:
                if first_deleted is not None:
                    return first_deleted

                return index

            if entry is _DELETED and first_deleted is None:
                first_deleted = index

            index = (index + 1) % self._capacity

        return first_deleted

    # Insert an existing entry without triggering another resize.
    def _insert_without_resize(self, entry: _Entry) -> None:
        index = self._hash_key(entry.key)

        while self._table[index] is not None:
            index = (index + 1) % self._capacity

        self._table[index] = entry
        self._count += 1

    # RESIZE: Create a larger table and reinsert active entries.
    def _resize(self, new_capacity: int) -> None:
        old_table = self._table

        self._capacity = new_capacity
        self._table = [None] * self._capacity

        self._count = 0
        self._deleted_count = 0

        for entry in old_table:
            if isinstance(entry, _Entry):
                self._insert_without_resize(entry)

    # SET: Insert a key-value pair or update an existing key.
    def set(self, key: str, value: int) -> None:
        existing_index = self._find_index(key)

        # Update an existing key.
        if existing_index is not None:
            entry = self._table[existing_index]
            assert isinstance(entry, _Entry)

            entry.value = value
            return

        # Resize when occupied and deleted slots exceed 70%.
        if (
            (self._count + self._deleted_count + 1) * 10
            > self._capacity * 7
        ):
            self._resize(self._capacity * 2)

        index = self._find_insert_index(key)

        if index is None:
            self._resize(self._capacity * 2)
            index = self._find_insert_index(key)

        if index is None:
            raise RuntimeError("No available slot in hash table")

        if self._table[index] is _DELETED:
            self._deleted_count -= 1

        self._table[index] = _Entry(key, value)
        self._count += 1

    # GET: Retrieve the value associated with a key.
    def get(self, key: str) -> Optional[int]:
        index = self._find_index(key)

        if index is None:
            return None

        entry = self._table[index]
        assert isinstance(entry, _Entry)

        return entry.value

    # CONTAINS: Check whether a key exists.
    def contains(self, key: str) -> bool:
        return self._find_index(key) is not None

    # REMOVE: Delete a key-value pair.
    def remove(self, key: str) -> bool:
        index = self._find_index(key)

        if index is None:
            return False

        self._table[index] = _DELETED

        self._count -= 1
        self._deleted_count += 1

        return True

    # SIZE: Get the number of active entries.
    def size(self) -> int:
        return self._count

    # CHECK: Check whether the table is empty.
    def is_empty(self) -> bool:
        return self._count == 0

    # DISPLAY: Show the internal table.
    def print_table(self) -> None:
        print("Hash Table:")

        for index, entry in enumerate(self._table):
            if entry is None:
                print(f"[{index}] Empty")
            elif entry is _DELETED:
                print(f"[{index}] Deleted")
            else:
                assert isinstance(entry, _Entry)
                print(f"[{index}] {entry.key}: {entry.value}")

    # CLEAR: Remove all entries while retaining capacity.
    def clear(self) -> None:
        self._table = [None] * self._capacity
        self._count = 0
        self._deleted_count = 0


# DEMONSTRATION

table = HashTable()

print("==== HASH TABLE ====")

# SET
print("\n--- SET ---")

table.set("apple", 100)
table.set("banana", 200)
table.set("orange", 300)
table.set("grape", 400)
table.set("mango", 500)
table.set("lemon", 600)

table.print_table()

# UPDATE
print("\n--- UPDATE ---")

table.set("banana", 250)

print("After updating banana:")
print("banana:", table.get("banana"))

# GET
print("\n--- GET ---")

print("apple:", table.get("apple"))
print("mango:", table.get("mango"))
print("Unknown key:", table.get("unknown"))

# CONTAINS
print("\n--- CONTAINS ---")

print("Contains apple:", table.contains("apple"))
print("Contains unknown:", table.contains("unknown"))

# REMOVE
print("\n--- REMOVE ---")

print("Removed orange:", table.remove("orange"))
print("Remove unknown:", table.remove("unknown"))

table.print_table()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", table.size())
print("Is empty:", table.is_empty())

# CLEAR
print("\n--- CLEAR ---")

table.clear()

print("Size after clearing:", table.size())
print("Is empty:", table.is_empty())

table.print_table()

# INSERT AFTER CLEAR
print("\n--- INSERT AFTER CLEAR ---")

table.set("mango", 500)

table.print_table()