from typing import List, Optional

class Queue:
    def __init__(self):
        self._capacity = 4
        self._buffer: List[Optional[int]] = [None] * self._capacity
        self._front = 0
        self._size = 0

    # Increase capacity when the queue is full.
    def _grow(self) -> None:
        new_capacity = self._capacity * 2
        new_buffer: List[Optional[int]] = [None] * new_capacity

        # Copy elements in their logical queue order.
        for i in range(self._size):
            old_index = (self._front + i) % self._capacity
            new_buffer[i] = self._buffer[old_index]

        self._buffer = new_buffer
        self._capacity = new_capacity
        self._front = 0

    # ENQUEUE: Add an element at the rear.
    def enqueue(self, value: int) -> None:
        if self._size == self._capacity:
            self._grow()

        rear_index = (self._front + self._size) % self._capacity

        self._buffer[rear_index] = value
        self._size += 1

    # DEQUEUE: Remove and return the front element.
    def dequeue(self) -> Optional[int]:
        if self.is_empty():
            return None

        removed_value = self._buffer[self._front]

        # Release the slot for future use.
        self._buffer[self._front] = None

        self._front = (self._front + 1) % self._capacity
        self._size -= 1

        # Reset the front position when the queue becomes empty.
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

    # CHECK: Check whether the queue is empty.
    def is_empty(self) -> bool:
        return self._size == 0

    # DISPLAY: Show elements from front to rear.
    def print_queue(self) -> None:
        if self.is_empty():
            print("Queue: Front -> Rear (Empty)")
            return

        values = []

        for i in range(self._size):
            index = (self._front + i) % self._capacity
            values.append(str(self._buffer[index]))

        print("Queue: Front ->", " -> ".join(values), "-> Rear")

    # CLEAR: Remove all elements without changing capacity.
    def clear(self) -> None:
        self._front = 0
        self._size = 0


# DEMONSTRATION

queue = Queue()

print("===== QUEUE =====")

# ENQUEUE
print("\n--- ENQUEUE ---")

queue.enqueue(10)
queue.enqueue(20)
queue.enqueue(30)
queue.enqueue(40)

queue.print_queue()

# This insertion triggers an increase in capacity.
queue.enqueue(50)

print("After enqueuing 50:")
queue.print_queue()

# READ
print("\n--- READ ---")

print("Front element:", queue.get_front())
print("Rear element:", queue.get_rear())

# DEQUEUE
print("\n--- DEQUEUE ---")

print("Removed element:", queue.dequeue())
queue.print_queue()

print("Removed element:", queue.dequeue())
queue.print_queue()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", queue.size())
print("Is empty:", queue.is_empty())

# CLEAR
print("\n--- CLEAR ---")

queue.clear()

queue.print_queue()

print("Size after clearing:", queue.size())
print("Is empty:", queue.is_empty())

# EMPTY QUEUE CHECK
print("\n--- EMPTY QUEUE CHECK ---")

print("Dequeue from empty queue:", queue.dequeue())
print("Get front from empty queue:", queue.get_front())
print("Get rear from empty queue:", queue.get_rear())