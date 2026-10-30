from typing import Optional

# NODE
class Node:
    def __init__(self, value: int):
        self.data = value
        self.next: Optional[Node] = None


# SINGLY LINKED LIST

class SinglyLinkedList:

    def __init__(self):
        self.head: Optional[Node] = None
        self.tail: Optional[Node] = None
        self.size = 0

    # READ

    def get_first(self) -> Optional[int]:
        if self.head is None:
            return None

        return self.head.data

    def get_last(self) -> Optional[int]:
        if self.tail is None:
            return None

        return self.tail.data

    def get_at(self, index: int) -> Optional[int]:
        if not isinstance(index, int) or index < 0 or index >= self.size:
            return None

        current = self.head

        for _ in range(index):
            current = current.next

        return current.data

    def print_list(self) -> None:
        current = self.head

        while current is not None:
            print(current.data, end=" -> ")
            current = current.next

        print("None")

    # UPDATE

    def set_at(self, index: int, value: int) -> bool:
        if not isinstance(index, int) or index < 0 or index >= self.size:
            return False

        current = self.head

        for _ in range(index):
            current = current.next

        current.data = value
        return True

    # INSERT

    def insert_front(self, value: int) -> None:
        node = Node(value)

        node.next = self.head
        self.head = node

        if self.tail is None:
            self.tail = node

        self.size += 1

    def insert_back(self, value: int) -> None:
        node = Node(value)

        if self.head is None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            self.tail = node

        self.size += 1

    # index == size inserts at the end.
    def insert_at(self, index: int, value: int) -> bool:
        if not isinstance(index, int) or index < 0 or index > self.size:
            return False

        if index == 0:
            self.insert_front(value)
            return True

        if index == self.size:
            self.insert_back(value)
            return True

        previous = self.head

        for _ in range(index - 1):
            previous = previous.next

        node = Node(value)

        node.next = previous.next
        previous.next = node

        self.size += 1

        return True

    # DELETE

    def remove_front(self) -> Optional[int]:
        if self.head is None:
            return None

        removed_value = self.head.data

        self.head = self.head.next
        self.size -= 1

        if self.head is None:
            self.tail = None

        return removed_value

    def remove_back(self) -> Optional[int]:
        if self.head is None:
            return None

        if self.head is self.tail:
            return self.remove_front()

        previous = self.head

        while previous.next is not self.tail:
            previous = previous.next

        removed_value = self.tail.data

        previous.next = None
        self.tail = previous

        self.size -= 1

        return removed_value

    def remove_at(self, index: int) -> Optional[int]:
        if not isinstance(index, int) or index < 0 or index >= self.size:
            return None

        if index == 0:
            return self.remove_front()

        if index == self.size - 1:
            return self.remove_back()

        previous = self.head

        for _ in range(index - 1):
            previous = previous.next

        node = previous.next
        removed_value = node.data

        previous.next = node.next

        self.size -= 1

        return removed_value

    # SIZE AND BASIC PROPERTIES

    def size_of(self) -> int:
        return self.size

    def is_empty(self) -> bool:
        return self.head is None

    # CLEAR

    def clear(self) -> None:
        self.head = None
        self.tail = None
        self.size = 0


# DEMONSTRATION

def main() -> None:

    linked_list = SinglyLinkedList()

    print("=== SINGLY LINKED LIST ===")

    # CREATE AND INSERT
    linked_list.insert_back(10)
    linked_list.insert_back(20)
    linked_list.insert_back(30)

    print("Initial list:", end=" ")
    linked_list.print_list()

    # READ
    print("First node:", linked_list.get_first())
    print("Last node:", linked_list.get_last())
    print("Node at index 1:", linked_list.get_at(1))

    # UPDATE
    linked_list.set_at(1, 25)

    print("After updating:", end=" ")
    linked_list.print_list()

    # INSERT
    linked_list.insert_front(5)
    linked_list.insert_back(40)
    linked_list.insert_at(2, 15)

    print("After inserting:", end=" ")
    linked_list.print_list()

    # DELETE
    print("Removed at index 2:", linked_list.remove_at(2))
    print("Removed first node:", linked_list.remove_front())
    print("Removed last node:", linked_list.remove_back())

    print("After deleting:", end=" ")
    linked_list.print_list()

    # SIZE AND PROPERTIES
    print("Size:", linked_list.size_of())
    print("Empty:", linked_list.is_empty())

    # CLEAR
    linked_list.clear()

    print("After clearing:", end=" ")
    linked_list.print_list()

    print("Size after clearing:", linked_list.size_of())
    print("Empty after clearing:", linked_list.is_empty())


if __name__ == "__main__":
    main()
