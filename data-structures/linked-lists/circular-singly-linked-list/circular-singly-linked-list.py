from typing import Optional

class _ListNode:
    def __init__(self, data: int):
        self.data = data
        self.next: Optional["_ListNode"] = None


class CircularSinglyLinkedList:
    def __init__(self):
        self._head: Optional[_ListNode] = None
        self._tail: Optional[_ListNode] = None
        self._length = 0

    # Find a node at a specific index.
    def _node_at(self, index: int) -> Optional[_ListNode]:
        if index < 0 or index >= self._length:
            return None

        current = self._head

        for _ in range(index):
            if current is None:
                return None

            current = current.next

        return current

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

    # DISPLAY: Traverse exactly one complete cycle.
    def print_list(self) -> None:
        if self._head is None:
            print("List: Empty")
            return

        current = self._head
        values = []

        while current is not None:
            values.append(str(current.data))
            current = current.next

            if current is self._head:
                break

        print("List:", " -> ".join(values), "-> (back to head)")

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
        else:
            new_node.next = self._head
            self._head = new_node
            self._tail.next = self._head

        self._length += 1

    # INSERT: Add an element at the end.
    def insert_back(self, data: int) -> None:
        new_node = _ListNode(data)

        if self._tail is None:
            self._head = new_node
            self._tail = new_node

            new_node.next = new_node
        else:
            new_node.next = self._head
            self._tail.next = new_node
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

        previous = self._node_at(index - 1)

        if previous is None:
            return False

        new_node = _ListNode(data)

        new_node.next = previous.next
        previous.next = new_node

        self._length += 1
        return True

    # DELETE: Remove the first element.
    def remove_front(self) -> Optional[int]:
        if self._head is None:
            return None

        removed_data = self._head.data

        # Only one node exists.
        if self._head is self._tail:
            self._head = None
            self._tail = None
        else:
            self._head = self._head.next
            self._tail.next = self._head

        self._length -= 1
        return removed_data

    # DELETE: Remove the last element.
    def remove_back(self) -> Optional[int]:
        if self._tail is None:
            return None

        removed_data = self._tail.data

        # Only one node exists.
        if self._head is self._tail:
            self._head = None
            self._tail = None
        else:
            previous = self._head

            while previous.next is not self._tail:
                previous = previous.next

            self._tail = previous
            self._tail.next = self._head

        self._length -= 1
        return removed_data

    # DELETE: Remove an element at a specific index.
    def remove_at(self, index: int) -> Optional[int]:
        if index < 0 or index >= self._length:
            return None

        if index == 0:
            return self.remove_front()

        if index == self._length - 1:
            return self.remove_back()

        previous = self._node_at(index - 1)

        if previous is None or previous.next is None:
            return None

        removed_node = previous.next
        previous.next = removed_node.next

        removed_data = removed_node.data
        removed_node.next = None

        self._length -= 1
        return removed_data

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
            current.next = None
            current = next_node

        self._head = None
        self._tail = None
        self._length = 0


# DEMONSTRATION

linked_list = CircularSinglyLinkedList()

print("==== CIRCULAR SINGLY LINKED LIST ====")

# INSERT
print("\n--- INSERT ---")

linked_list.insert_front(20)
linked_list.insert_front(10)
linked_list.insert_back(30)
linked_list.insert_back(40)

linked_list.print_list()

linked_list.insert_at(2, 25)

print("After inserting 25 at index 2:")
linked_list.print_list()

# READ
print("\n--- READ ---")

print("First element:", linked_list.get_first())
print("Last element:", linked_list.get_last())
print("Element at index 2:", linked_list.get_at(2))

# UPDATE
print("\n--- UPDATE ---")

linked_list.set_at(2, 99)

print("After updating index 2 to 99:")
linked_list.print_list()

# DELETE
print("\n--- DELETE ---")

print("Removed from front:", linked_list.remove_front())
linked_list.print_list()

print("Removed from back:", linked_list.remove_back())
linked_list.print_list()

print("Removed from index 1:", linked_list.remove_at(1))
linked_list.print_list()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", linked_list.size())
print("Is empty:", linked_list.is_empty())

# CLEAR
print("\n--- CLEAR ---")

linked_list.clear()

linked_list.print_list()

print("Size after clearing:", linked_list.size())
print("Is empty:", linked_list.is_empty())