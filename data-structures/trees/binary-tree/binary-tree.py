from collections import deque
from typing import List, Optional

class _TreeNode:
    def __init__(self, data: int):
        self.data = data
        self.left: Optional["_TreeNode"] = None
        self.right: Optional["_TreeNode"] = None


class BinaryTree:
    def __init__(self):
        self._root: Optional[_TreeNode] = None
        self._size = 0

    # Find the first matching node using level-order traversal.
    def _find_node(self, value: int) -> Optional[_TreeNode]:
        if self._root is None:
            return None

        nodes = deque([self._root])

        while nodes:
            current = nodes.popleft()

            if current.data == value:
                return current

            if current.left is not None:
                nodes.append(current.left)

            if current.right is not None:
                nodes.append(current.right)

        return None

    # INSERT: Add a node at the first available position.
    def insert(self, value: int) -> bool:
        new_node = _TreeNode(value)

        # Insert the first node as the root.
        if self._root is None:
            self._root = new_node
            self._size += 1
            return True

        nodes = deque([self._root])

        while nodes:
            current = nodes.popleft()

            # Check the left child first.
            if current.left is None:
                current.left = new_node
                self._size += 1
                return True

            nodes.append(current.left)

            # Then check the right child.
            if current.right is None:
                current.right = new_node
                self._size += 1
                return True

            nodes.append(current.right)

        return False

    # SEARCH: Check whether a value exists.
    def contains(self, value: int) -> bool:
        return self._find_node(value) is not None

    # UPDATE: Change the value of an existing node.
    def update(self, old_value: int, new_value: int) -> bool:
        node = self._find_node(old_value)

        if node is None:
            return False

        node.data = new_value
        return True

    # DELETE: Remove a node and preserve the complete shape.
    def remove(self, value: int) -> bool:
        if self._root is None:
            return False

        nodes = deque([(self._root, None)])

        target = None
        deepest = None
        deepest_parent = None

        while nodes:
            current, parent = nodes.popleft()

            # Record the first matching node.
            if target is None and current.data == value:
                target = current

            # The final node visited is the deepest,
            # rightmost node in level-order traversal.
            deepest = current
            deepest_parent = parent

            if current.left is not None:
                nodes.append((current.left, current))

            if current.right is not None:
                nodes.append((current.right, current))

        if target is None or deepest is None:
            return False

        # Replace the target value with the deepest node value.
        target.data = deepest.data

        # Remove the deepest node.
        if deepest_parent is None:
            self._root = None
        elif deepest_parent.right is deepest:
            deepest_parent.right = None
        else:
            deepest_parent.left = None

        self._size -= 1
        return True

    # PREORDER: Root -> Left -> Right.
    def preorder(self) -> List[int]:
        values = []

        def traverse(node: Optional[_TreeNode]) -> None:
            if node is None:
                return

            values.append(node.data)
            traverse(node.left)
            traverse(node.right)

        traverse(self._root)
        return values

    # INORDER: Left -> Root -> Right.
    def inorder(self) -> List[int]:
        values = []

        def traverse(node: Optional[_TreeNode]) -> None:
            if node is None:
                return

            traverse(node.left)
            values.append(node.data)
            traverse(node.right)

        traverse(self._root)
        return values

    # POSTORDER: Left -> Right -> Root.
    def postorder(self) -> List[int]:
        values = []

        def traverse(node: Optional[_TreeNode]) -> None:
            if node is None:
                return

            traverse(node.left)
            traverse(node.right)
            values.append(node.data)

        traverse(self._root)
        return values

    # LEVEL-ORDER: Visit nodes level by level.
    def level_order(self) -> List[int]:
        values = []

        if self._root is None:
            return values

        nodes = deque([self._root])

        while nodes:
            current = nodes.popleft()
            values.append(current.data)

            if current.left is not None:
                nodes.append(current.left)

            if current.right is not None:
                nodes.append(current.right)

        return values

    # SIZE: Get the number of nodes.
    def size(self) -> int:
        return self._size

    # CHECK: Check whether the tree is empty.
    def is_empty(self) -> bool:
        return self._root is None

    # CLEAR: Remove all nodes.
    def clear(self) -> None:
        self._root = None
        self._size = 0


# DEMONSTRATION

tree = BinaryTree()

print("==== BINARY TREE ====")

# INSERT
print("\n--- INSERT ---")

tree.insert(10)
tree.insert(20)
tree.insert(30)
tree.insert(40)
tree.insert(50)
tree.insert(60)
tree.insert(70)

print("Inserted 7 nodes.")

# TRAVERSALS
print("\n--- TRAVERSALS ---")

print("Preorder:", tree.preorder())
print("Inorder:", tree.inorder())
print("Postorder:", tree.postorder())
print("Level-order:", tree.level_order())

# SEARCH
print("\n--- SEARCH ---")

print("Contains 50:", tree.contains(50))
print("Contains 90:", tree.contains(90))

# UPDATE
print("\n--- UPDATE ---")

if tree.update(50, 55):
    print("Updated 50 to 55.")

print("Level-order after update:", tree.level_order())

# DELETE
print("\n--- DELETE ---")

if tree.remove(20):
    print("Removed 20.")

print("Level-order after removal:", tree.level_order())
print("Contains 20:", tree.contains(20))

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", tree.size())
print("Is empty:", tree.is_empty())

# CLEAR
print("\n--- CLEAR ---")

tree.clear()

print("Size after clearing:", tree.size())
print("Is empty:", tree.is_empty())
print("Level-order after clearing:", tree.level_order())

# INSERT AFTER CLEAR
print("\n--- INSERT AFTER CLEAR ---")

tree.insert(100)
tree.insert(200)

print("Level-order:", tree.level_order())