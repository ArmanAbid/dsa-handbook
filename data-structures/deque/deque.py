from typing import List, Optional

class Deque:
    def __init__(self):
        self._capacity = 4
        self._buffer: List[Optional[int]] = [None] * self._capacity
        self._front = 0
        self._size = 0

    # Increase capacity when the deque is full.
    def _grow(self) -> None:
        new_capacity = self._capacity * 2
        new_buffer: List[Optional[int]] = [None] * new_capacity

        # Copy elements in their logical order.
        for i in range(self._size):
            old_index = (self._front + i) % self._capacity
            new_buffer[i] = self._buffer[old_index]

        self._buffer = new_buffer
        self._capacity = new_capacity
        self._front = 0

    # PUSH FRONT: Insert an element at the front.
    def push_front(self, value: int) -> None:
        if self._size == self._capacity:
            self._grow()

        self._front = (self._front - 1) % self._capacity

        self._buffer[self._front] = value
        self._size += 1

    # PUSH BACK: Insert an element at the rear.
    def push_back(self, value: int) -> None:
        if self._size == self._capacity:
            self._grow()

        rear_index = (self._front + self._size) % self._capacity

        self._buffer[rear_index] = value
        self._size += 1

    # POP FRONT: Remove and return the front element.
    def pop_front(self) -> Optional[int]:
        if self.is_empty():
            return None

        removed_value = self._buffer[self._front]

        self._buffer[self._front] = None

        self._front = (self._front + 1) % self._capacity
        self._size -= 1

        if self._size == 0:
            self._front = 0

        return removed_value

    # POP BACK: Remove and return the rear element.
    def pop_back(self) -> Optional[int]:
        if self.is_empty():
            return None

        rear_index = (self._front + self._size - 1) % self._capacity

        removed_value = self._buffer[rear_index]

        self._buffer[rear_index] = None
        self._size -= 1

        if self._size == 0:
            self._front = 0

        return removed_value

    # READ: Get the front element without removing it.
    def get_front(self) -> Optional[int]:
        if self.is_empty():
            return None

        return self._buffer[self._front]

    # READ: Get the rear element without removing it.
    def get_rear(self) -> Optional[int]:
        if self.is_empty():
            return None

        rear_index = (self._front + self._size - 1) % self._capacity

        return self._buffer[rear_index]

    # SIZE: Get the number of elements.
    def size(self) -> int:
        return self._size

    # CHECK: Check whether the deque is empty.
    def is_empty(self) -> bool:
        return self._size == 0

    # DISPLAY: Show elements from front to rear.
    def print_deque(self) -> None:
        if self.is_empty():
            print("Deque: Front -> Rear (Empty)")
            return

        values = []

        for i in range(self._size):
            index = (self._front + i) % self._capacity
            values.append(str(self._buffer[index]))

        print("Deque: Front ->", " <-> ".join(values), "-> Rear")

    # CLEAR: Remove all elements without changing capacity.
    def clear(self) -> None:
        self._buffer = [None] * self._capacity
        self._front = 0
        self._size = 0


# DEMONSTRATION

deque = Deque()

print("==== DEQUE ====")

# INSERT
print("\n--- INSERT ---")

deque.push_back(10)
deque.push_back(20)
deque.push_back(30)

deque.print_deque()

deque.push_front(5)

print("After pushing 5 at the front:")
deque.print_deque()

# This insertion triggers an increase in capacity.
deque.push_back(40)

print("After pushing 40 at the rear:")
deque.print_deque()

# READ
print("\n--- READ ---")

print("Front element:", deque.get_front())
print("Rear element:", deque.get_rear())

# DELETE
print("\n--- DELETE ---")

print("Removed from front:", deque.pop_front())
deque.print_deque()

print("Removed from back:", deque.pop_back())
deque.print_deque()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", deque.size())
print("Is empty:", deque.is_empty())

# CLEAR
print("\n--- CLEAR ---")

deque.clear()

deque.print_deque()

print("Size after clearing:", deque.size())
print("Is empty:", deque.is_empty())

# EMPTY DEQUE CHECK
print("\n--- EMPTY DEQUE CHECK ---")

print("Pop from front:", deque.pop_front())
print("Pop from back:", deque.pop_back())
print("Get front:", deque.get_front())
print("Get rear:", deque.get_rear())