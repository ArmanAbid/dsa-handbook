from typing import List, Optional

class _Entry:
    def __init__(self, value: str):
        self.value = value


# Marks a slot that previously contained a deleted element.
_DELETED = object()


class HashSet:
    def __init__(self):
        self._capacity = 8
        self._table: List[object] = [None] * self._capacity
        self._count = 0
        self._deleted_count = 0

    # HASH: Convert a string into an array index.
    def _hash_value(self, value: str) -> int:
        hash_value = 0

        for char in value:
            hash_value = (
                hash_value * 31 + ord(char)
            ) % self._capacity

        return hash_value

    # Find an existing element.
    def _find_index(self, value: str) -> Optional[int]:
        index = self._hash_value(value)

        for _ in range(self._capacity):
            entry = self._table[index]

            if entry is None:
                return None

            if entry is not _DELETED:
                assert isinstance(entry, _Entry)

                if entry.value == value:
                    return index

            index = (index + 1) % self._capacity

        return None

    # Find an available slot for insertion.
    # Prefer the first deleted slot encountered.
    def _find_insert_index(self, value: str) -> Optional[int]:
        index = self._hash_value(value)
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

    # Insert an existing element without triggering another resize.
    def _insert_without_resize(self, value: str) -> None:
        index = self._hash_value(value)

        while self._table[index] is not None:
            index = (index + 1) % self._capacity

        self._table[index] = _Entry(value)
        self._count += 1

    # RESIZE: Create a larger table and reinsert active elements.
    def _resize(self, new_capacity: int) -> None:
        old_table = self._table

        self._capacity = new_capacity
        self._table = [None] * self._capacity

        self._count = 0
        self._deleted_count = 0

        for entry in old_table:
            if isinstance(entry, _Entry):
                self._insert_without_resize(entry.value)

    # ADD: Insert an element if it does not already exist.
    def add(self, value: str) -> bool:
        # Prevent duplicate elements.
        if self.contains(value):
            return False

        # Resize when occupied and deleted slots exceed 70%.
        if (
            (self._count + self._deleted_count + 1) * 10
            > self._capacity * 7
        ):
            self._resize(self._capacity * 2)

        index = self._find_insert_index(value)

        if index is None:
            self._resize(self._capacity * 2)
            index = self._find_insert_index(value)

        if index is None:
            raise RuntimeError("No available slot in hash set")

        if self._table[index] is _DELETED:
            self._deleted_count -= 1

        self._table[index] = _Entry(value)
        self._count += 1

        return True

    # CONTAINS: Check whether an element exists.
    def contains(self, value: str) -> bool:
        return self._find_index(value) is not None

    # REMOVE: Delete an element.
    def remove(self, value: str) -> bool:
        index = self._find_index(value)

        if index is None:
            return False

        self._table[index] = _DELETED

        self._count -= 1
        self._deleted_count += 1

        return True

    # SIZE: Get the number of active elements.
    def size(self) -> int:
        return self._count

    # CHECK: Check whether the set is empty.
    def is_empty(self) -> bool:
        return self._count == 0

    # DISPLAY: Show all active elements.
    def print_set(self) -> None:
        values = []

        for entry in self._table:
            if isinstance(entry, _Entry):
                values.append(entry.value)

        if values:
            print("Set:", "{" + ", ".join(values) + "}")
        else:
            print("Set: { Empty }")

    # CLEAR: Remove all elements while retaining capacity.
    def clear(self) -> None:
        self._table = [None] * self._capacity
        self._count = 0
        self._deleted_count = 0


# DEMONSTRATION

set_collection = HashSet()

print("==== HASH SET ====")

# ADD
print("\n--- ADD ---")

set_collection.add("apple")
set_collection.add("banana")
set_collection.add("orange")
set_collection.add("grape")

set_collection.print_set()

# Try adding a duplicate.
print("Adding apple again:", set_collection.add("apple"))

set_collection.print_set()

# CONTAINS
print("\n--- CONTAINS ---")

print("Contains apple:", set_collection.contains("apple"))
print("Contains mango:", set_collection.contains("mango"))

# REMOVE
print("\n--- REMOVE ---")

print("Remove banana:", set_collection.remove("banana"))
print("Remove mango:", set_collection.remove("mango"))

set_collection.print_set()

# Check that other elements are still accessible.
print(
    "Contains orange after removal:",
    set_collection.contains("orange")
)

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", set_collection.size())
print("Is empty:", set_collection.is_empty())

# CLEAR
print("\n--- CLEAR ---")

set_collection.clear()

set_collection.print_set()

print("Size after clearing:", set_collection.size())
print("Is empty:", set_collection.is_empty())

# ADD AFTER CLEAR
print("\n--- ADD AFTER CLEAR ---")

set_collection.add("mango")
set_collection.add("lemon")

set_collection.print_set()