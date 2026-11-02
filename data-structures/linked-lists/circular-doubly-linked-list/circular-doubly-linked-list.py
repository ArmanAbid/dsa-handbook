from typing import Optional

class _ListNode:
    def __init__(self, data: int):
        self.data = data
        self.prev: Optional["_ListNode"] = None
        self.next: Optional["_ListNode"] = None


class CircularDoublyLinkedList:
    def __init__(self):
        self._head: Optional[_ListNode] = None
        self._tail: Optional[_ListNode] = None
        self._length = 0

    # Find a node at a specific index.
    # Start from whichever end is closer.
    def _node_at(self, index: int) -> Optional[_ListNode]:
        if index < 0 or index >= self._length:
            return None

        if index < self._length // 2:
            current = self._head

            for _ in range(index):
                if current is None:
                    return None

                current = current.next
        else:
            current = self._tail

            for _ in range(self._length - 1, index, -1):
                if current is None:
                    return None

                current = current.prev

        return current

    # Remove a specific node and return its value.
    def _unlink(self, node: _ListNode) -> int:
        removed_data = node.data

        # Only one node exists.
        if self._head is self._tail:
            self._head = None
            self._tail = None
        else:
            previous_node = node.prev
            next_node = node.next

            if previous_node is None or next_node is None:
                raise RuntimeError("Invalid circular list links")

            previous_node.next = next_node
            next_node.prev = previous_node

            if node is self._head:
                self._head = next_node

            if node is self._tail:
                self._tail = previous_node

        # Detach the removed node.
        node.prev = None
        node.next = None

        self._length -= 1
        return removed_data

    # READ: Get the first element.
    def get_first(self) -> Optional[int]:
        if self._head is None:
            return None

        return self._head.data

    # READ: Get the last element.
    def get_last(self) -> Optional[int]:
        if self._tail is None:
            return None

        return self._tail.data

    # READ: Get an element at a specific index.
    def get_at(self, index: int) -> Optional[int]:
        node = self._node_at(index)

        if node is None:
            return None

        return node.data

    # DISPLAY: Traverse from head to tail.
    def print_forward(self) -> None:
        current = self._head
        values = []

        for _ in range(self._length):
            if current is None:
                break

            values.append(str(current.data))
            current = current.next

        if values:
            print("Forward:", " <-> ".join(values), "-> (back to head)")
        else:
            print("Forward: Empty")

    # DISPLAY: Traverse from tail to head.
    def print_backward(self) -> None:
        current = self._tail
        values = []

        for _ in range(self._length):
            if current is None:
                break

            values.append(str(current.data))
            current = current.prev

        if values:
            print("Backward:", " <-> ".join(values), "-> (back to tail)")
        else:
            print("Backward: Empty")

    # UPDATE: Change the value at a specific index.
    def set_at(self, index: int, value: int) -> bool:
        node = self._node_at(index)

        if node is None:
            return False

        node.data = value
        return True

    # INSERT: Add an element at the beginning.
    def insert_front(self, data: int) -> None:
        new_node = _ListNode(data)

        if self._head is None:
            self._head = new_node
            self._tail = new_node

            # The only node points to itself.
            new_node.next = new_node
            new_node.prev = new_node
        else:
            old_head = self._head
            old_tail = self._tail

            new_node.next = old_head
            new_node.prev = old_tail

            old_head.prev = new_node

            if old_tail is not None:
                old_tail.next = new_node

            self._head = new_node

        self._length += 1

    # INSERT: Add an element at the end.
    def insert_back(self, data: int) -> None:
        new_node = _ListNode(data)

        if self._tail is None:
            self._head = new_node
            self._tail = new_node

            new_node.next = new_node
            new_node.prev = new_node
        else:
            old_tail = self._tail
            old_head = self._head

            new_node.prev = old_tail
            new_node.next = old_head

            old_tail.next = new_node

            if old_head is not None:
                old_head.prev = new_node

            self._tail = new_node

        self._length += 1

    # INSERT: Add an element at a specific index.
    def insert_at(self, index: int, data: int) -> bool:
        if index < 0 or index > self._length:
            return False

        if index == 0:
            self.insert_front(data)
            return True

        if index == self._length:
            self.insert_back(data)
            return True

        next_node = self._node_at(index)

        if next_node is None or next_node.prev is None:
            return False

        previous_node = next_node.prev
        new_node = _ListNode(data)

        new_node.prev = previous_node
        new_node.next = next_node

        previous_node.next = new_node
        next_node.prev = new_node

        self._length += 1
        return True

    # DELETE: Remove the first element.
    def remove_front(self) -> Optional[int]:
        if self._head is None:
            return None

        return self._unlink(self._head)

    # DELETE: Remove the last element.
    def remove_back(self) -> Optional[int]:
        if self._tail is None:
            return None

        return self._unlink(self._tail)

    # DELETE: Remove an element at a specific index.
    def remove_at(self, index: int) -> Optional[int]:
        node = self._node_at(index)

        if node is None:
            return None

        return self._unlink(node)

    # SIZE: Get the number of elements.
    def size(self) -> int:
        return self._length

    # CHECK: Check whether the list is empty.
    def is_empty(self) -> bool:
        return self._length == 0

    # CLEAR: Remove all elements.
    def clear(self) -> None:
        current = self._head

        # Visit exactly the number of nodes in the list.
        for _ in range(self._length):
            if current is None:
                break

            next_node = current.next

            current.prev = None
            current.next = None

            current = next_node

        self._head = None
        self._tail = None
        self._length = 0


# DEMONSTRATION

linked_list = CircularDoublyLinkedList()

print("=== CIRCULAR DOUBLY LINKED LIST ===")

# INSERT
print("\n--- INSERT ---")

linked_list.insert_front(20)
linked_list.insert_front(10)
linked_list.insert_back(30)
linked_list.insert_back(40)

linked_list.print_forward()
linked_list.print_backward()

linked_list.insert_at(2, 25)

print("After inserting 25 at index 2:")
linked_list.print_forward()

# READ
print("\n--- READ ---")

print("First element:", linked_list.get_first())
print("Last element:", linked_list.get_last())
print("Element at index 2:", linked_list.get_at(2))

# UPDATE
print("\n--- UPDATE ---")

linked_list.set_at(2, 99)

print("After updating index 2 to 99:")
linked_list.print_forward()

# DELETE
print("\n--- DELETE ---")

print("Removed from front:", linked_list.remove_front())
linked_list.print_forward()

print("Removed from back:", linked_list.remove_back())
linked_list.print_forward()

print("Removed from index 1:", linked_list.remove_at(1))
linked_list.print_forward()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", linked_list.size())
print("Is empty:", linked_list.is_empty())

# CLEAR
print("\n--- CLEAR ---")

linked_list.clear()

linked_list.print_forward()
linked_list.print_backward()

print("Size after clearing:", linked_list.size())
print("Is empty:", linked_list.is_empty())