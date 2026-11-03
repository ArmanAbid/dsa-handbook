from typing import List, Optional

class BinaryHeap:
    def __init__(self, is_min_heap: bool = True):
        self._elements: List[int] = []
        self._is_min_heap = is_min_heap

    # Check whether the first value has higher priority.
    def _has_higher_priority(self, first: int, second: int) -> bool:
        if self._is_min_heap:
            return first < second

        return first > second

    # Swap two elements.
    def _swap(self, first: int, second: int) -> None:
        self._elements[first], self._elements[second] = (
            self._elements[second],
            self._elements[first]
        )

    # SIFT UP: Restore the heap property after insertion.
    def _sift_up(self, index: int) -> None:
        while index > 0:
            parent = (index - 1) // 2

            if not self._has_higher_priority(
                self._elements[index],
                self._elements[parent]
            ):
                break

            self._swap(index, parent)
            index = parent

    # SIFT DOWN: Restore the heap property after extraction.
    def _sift_down(self, index: int) -> None:
        length = len(self._elements)

        while True:
            best = index
            left = 2 * index + 1
            right = 2 * index + 2

            # Check the left child.
            if (
                left < length
                and self._has_higher_priority(
                    self._elements[left],
                    self._elements[best]
                )
            ):
                best = left

            # Check the right child.
            if (
                right < length
                and self._has_higher_priority(
                    self._elements[right],
                    self._elements[best]
                )
            ):
                best = right

            # Heap property is already satisfied.
            if best == index:
                break

            self._swap(index, best)
            index = best

    # INSERT: Add a value to the heap.
    def insert(self, value: int) -> None:
        self._elements.append(value)

        # Move the new element to its correct position.
        self._sift_up(len(self._elements) - 1)

    # PEEK: Read the root without removing it.
    def peek(self) -> Optional[int]:
        if self.is_empty():
            return None

        return self._elements[0]

    # EXTRACT ROOT: Remove and return the root.
    def extract_root(self) -> Optional[int]:
        if self.is_empty():
            return None

        removed_value = self._elements[0]

        # If only one element exists, remove it directly.
        if len(self._elements) == 1:
            self._elements.pop()
            return removed_value

        # Move the last element to the root.
        self._elements[0] = self._elements.pop()

        # Restore the heap property.
        self._sift_down(0)

        return removed_value

    # CONTAINS: Check whether a value exists.
    def contains(self, value: int) -> bool:
        return value in self._elements

    # SIZE: Get the number of elements.
    def size(self) -> int:
        return len(self._elements)

    # CHECK: Check whether the heap is empty.
    def is_empty(self) -> bool:
        return len(self._elements) == 0

    # DISPLAY: Show the internal array representation.
    def print_heap(self) -> None:
        print("Heap:", self._elements)

    # CLEAR: Remove all elements.
    def clear(self) -> None:
        self._elements.clear()


# DEMONSTRATION

print("==== BINARY HEAP ====")

# MIN HEAP

min_heap = BinaryHeap(is_min_heap=True)

print("\n==== MIN HEAP ====")

# INSERT
print("\n--- INSERT ---")

for value in [40, 20, 30, 10, 50, 5, 35]:
    min_heap.insert(value)

min_heap.print_heap()

# PEEK
print("\n--- PEEK ---")

print("Minimum element:", min_heap.peek())

# CONTAINS
print("\n--- CONTAINS ---")

print("Contains 30:", min_heap.contains(30))
print("Contains 100:", min_heap.contains(100))

# EXTRACT ROOT
print("\n--- EXTRACT ROOT ---")

print("Extracted minimum:", min_heap.extract_root())
min_heap.print_heap()

print("Extracted minimum:", min_heap.extract_root())
min_heap.print_heap()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", min_heap.size())
print("Is empty:", min_heap.is_empty())

# CLEAR
print("\n--- CLEAR MIN HEAP ---")

min_heap.clear()

min_heap.print_heap()

print("Size after clearing:", min_heap.size())

# EMPTY HEAP CHECK
print("\n--- EMPTY MIN HEAP CHECK ---")

print("Extract from empty heap:", min_heap.extract_root())
print("Peek into empty heap:", min_heap.peek())

# INSERT AFTER CLEAR
min_heap.insert(15)
min_heap.insert(8)

print("After inserting again:")
min_heap.print_heap()

# MAX HEAP

max_heap = BinaryHeap(is_min_heap=False)

print("\n==== MAX HEAP ====")

# INSERT
for value in [40, 20, 30, 10, 50, 5, 35]:
    max_heap.insert(value)

max_heap.print_heap()

# PEEK
print("\n--- PEEK ---")

print("Maximum element:", max_heap.peek())

# EXTRACT ROOT
print("\n--- EXTRACT ROOT ---")

print("Extracted maximum:", max_heap.extract_root())
max_heap.print_heap()