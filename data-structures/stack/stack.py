from typing import List, Optional

class Stack:
    def __init__(self):
        # Internal storage for stack elements.
        self._elements: List[int] = []

    # PUSH: Add an element to the top.
    def push(self, value: int) -> None:
        self._elements.append(value)

    # POP: Remove and return the top element.
    def pop(self) -> Optional[int]:
        if self.is_empty():
            return None

        return self._elements.pop()

    # PEEK: Read the top element without removing it.
    def peek(self) -> Optional[int]:
        if self.is_empty():
            return None

        return self._elements[-1]

    # SIZE: Get the number of elements.
    def size(self) -> int:
        return len(self._elements)

    # CHECK: Check whether the stack is empty.
    def is_empty(self) -> bool:
        return len(self._elements) == 0

    # DISPLAY: Show elements from top to bottom.
    def print_stack(self) -> None:
        if self.is_empty():
            print("Stack: Top -> Bottom (Empty)")
            return

        values = " -> ".join(
            str(value) for value in reversed(self._elements)
        )

        print(f"Stack: Top -> {values} -> Bottom")

    # CLEAR: Remove all elements.
    def clear(self) -> None:
        self._elements.clear()


# DEMONSTRATION

stack = Stack()

print("==== STACK ====")

# PUSH
print("\n--- PUSH ---")

stack.push(10)
stack.push(20)
stack.push(30)

stack.print_stack()

stack.push(40)

print("After pushing 40:")
stack.print_stack()

# PEEK
print("\n--- PEEK ---")

print("Top element:", stack.peek())

stack.print_stack()

# POP
print("\n--- POP ---")

print("Removed element:", stack.pop())
stack.print_stack()

print("Removed element:", stack.pop())
stack.print_stack()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", stack.size())
print("Is empty:", stack.is_empty())

# CLEAR
print("\n--- CLEAR ---")

stack.clear()

stack.print_stack()

print("Size after clearing:", stack.size())
print("Is empty:", stack.is_empty())

# EMPTY STACK CHECK
print("\n--- EMPTY STACK CHECK ---")

print("Pop from empty stack:", stack.pop())
print("Peek into empty stack:", stack.peek())