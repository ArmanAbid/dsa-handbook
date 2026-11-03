from collections import deque
from typing import List, Optional, Tuple

class _TreeNode:
    def __init__(self, data: int):
        self.data = data
        self.height = 1
        self.left: Optional["_TreeNode"] = None
        self.right: Optional["_TreeNode"] = None


class AVLTree:
    def __init__(self):
        self._root: Optional[_TreeNode] = None
        self._size = 0

    # HEIGHT: Get the height of a node.
    def _height(self, node: Optional[_TreeNode]) -> int:
        if node is None:
            return 0

        return node.height

    # Update the height of a node.
    def _update_height(self, node: _TreeNode) -> None:
        left_height = self._height(node.left)
        right_height = self._height(node.right)

        node.height = 1 + max(left_height, right_height)

    # BALANCE FACTOR: Left subtree height minus right subtree height.
    def _balance_factor(self, node: Optional[_TreeNode]) -> int:
        if node is None:
            return 0

        return self._height(node.left) - self._height(node.right)

    # RIGHT ROTATION: Used for LL imbalance.
    def _rotate_right(self, y: _TreeNode) -> _TreeNode:
        x = y.left

        if x is None:
            return y

        subtree = x.right

        x.right = y
        y.left = subtree

        # Update the lower node first.
        self._update_height(y)
        self._update_height(x)

        return x

    # LEFT ROTATION: Used for RR imbalance.
    def _rotate_left(self, x: _TreeNode) -> _TreeNode:
        y = x.right

        if y is None:
            return x

        subtree = y.left

        y.left = x
        x.right = subtree

        # Update the lower node first.
        self._update_height(x)
        self._update_height(y)

        return y

    # REBALANCE: Restore AVL balance after modification.
    def _rebalance(self, node: Optional[_TreeNode]) -> Optional[_TreeNode]:
        if node is None:
            return None

        self._update_height(node)

        balance = self._balance_factor(node)

        # Left-heavy subtree.
        if balance > 1:
            # LR case: Left rotation on the left child first.
            if (
                node.left is not None
                and self._balance_factor(node.left) < 0
            ):
                node.left = self._rotate_left(node.left)

            # LL case.
            return self._rotate_right(node)

        # Right-heavy subtree.
        if balance < -1:
            # RL case: Right rotation on the right child first.
            if (
                node.right is not None
                and self._balance_factor(node.right) > 0
            ):
                node.right = self._rotate_right(node.right)

            # RR case.
            return self._rotate_left(node)

        return node

    # INSERT: Recursively insert while preserving AVL balance.
    def _insert_node(
        self,
        node: Optional[_TreeNode],
        value: int
    ) -> Tuple[Optional[_TreeNode], bool]:
        if node is None:
            return _TreeNode(value), True

        if value < node.data:
            node.left, inserted = self._insert_node(node.left, value)
        elif value > node.data:
            node.right, inserted = self._insert_node(node.right, value)
        else:
            # Duplicate values are not inserted.
            return node, False

        return self._rebalance(node), inserted

    # SEARCH: Find a node containing the given value.
    def _find_node(self, value: int) -> Optional[_TreeNode]:
        current = self._root

        while current is not None:
            if value == current.data:
                return current

            if value < current.data:
                current = current.left
            else:
                current = current.right

        return None

    # Find the node with the smallest value in a subtree.
    def _minimum_node(
        self,
        node: Optional[_TreeNode]
    ) -> Optional[_TreeNode]:
        if node is None:
            return None

        while node.left is not None:
            node = node.left

        return node

    # Find the node with the largest value in a subtree.
    def _maximum_node(
        self,
        node: Optional[_TreeNode]
    ) -> Optional[_TreeNode]:
        if node is None:
            return None

        while node.right is not None:
            node = node.right

        return node

    # DELETE: Remove a value while preserving AVL balance.
    def _remove_node(
        self,
        node: Optional[_TreeNode],
        value: int
    ) -> Tuple[Optional[_TreeNode], bool]:
        if node is None:
            return None, False

        if value < node.data:
            node.left, removed = self._remove_node(node.left, value)

        elif value > node.data:
            node.right, removed = self._remove_node(node.right, value)

        else:
            # Case 1: No left child.
            if node.left is None:
                return node.right, True

            # Case 2: No right child.
            if node.right is None:
                return node.left, True

            # Case 3: Two children.
            # Replace with the inorder successor.
            successor = self._minimum_node(node.right)

            if successor is None:
                return node, False

            node.data = successor.data

            node.right, _ = self._remove_node(
                node.right,
                successor.data
            )

            return self._rebalance(node), True

        return self._rebalance(node), removed

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

    # INSERT: Add a value.
    def insert(self, value: int) -> bool:
        self._root, inserted = self._insert_node(self._root, value)

        if inserted:
            self._size += 1

        return inserted

    # SEARCH: Check whether a value exists.
    def contains(self, value: int) -> bool:
        return self._find_node(value) is not None

    # UPDATE: Change a value while preserving AVL ordering.
    def update(self, old_value: int, new_value: int) -> bool:
        if not self.contains(old_value):
            return False

        if old_value == new_value:
            return True

        # Duplicate values are not allowed.
        if self.contains(new_value):
            return False

        # Remove the old value and insert the new value.
        self.remove(old_value)
        self.insert(new_value)

        return True

    # DELETE: Remove a value.
    def remove(self, value: int) -> bool:
        self._root, removed = self._remove_node(self._root, value)

        if removed:
            self._size -= 1

        return removed

    # MINIMUM: Get the smallest value.
    def get_minimum(self) -> Optional[int]:
        node = self._minimum_node(self._root)

        if node is None:
            return None

        return node.data

    # MAXIMUM: Get the largest value.
    def get_maximum(self) -> Optional[int]:
        node = self._maximum_node(self._root)

        if node is None:
            return None

        return node.data

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

tree = AVLTree()

print("==== AVL TREE ====")

# INSERT
print("\n--- INSERT ---")

for value in [10, 20, 30, 40, 50, 25]:
    tree.insert(value)

print("Inserted 6 values.")

print("Insert duplicate 30:", tree.insert(30))

# TRAVERSALS
print("\n--- TRAVERSALS ---")

print("Preorder:", tree.preorder())
print("Inorder:", tree.inorder())
print("Postorder:", tree.postorder())
print("Level-order:", tree.level_order())

# SEARCH
print("\n--- SEARCH ---")

print("Contains 25:", tree.contains(25))
print("Contains 90:", tree.contains(90))

# MINIMUM AND MAXIMUM
print("\n--- MINIMUM AND MAXIMUM ---")

print("Minimum:", tree.get_minimum())
print("Maximum:", tree.get_maximum())

# UPDATE
print("\n--- UPDATE ---")

print("Update 25 to 35:", tree.update(25, 35))
print("Update 35 to 40:", tree.update(35, 40), "(duplicate value)")

print("Inorder after update:", tree.inorder())

# DELETE
print("\n--- DELETE ---")

print("Remove leaf 10:", tree.remove(10))
print("Remove node 30:", tree.remove(30))
print("Remove missing 100:", tree.remove(100))

print("Inorder after removal:", tree.inorder())

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", tree.size())
print("Is empty:", tree.is_empty())

# CLEAR
print("\n--- CLEAR ---")

tree.clear()

print("Size after clearing:", tree.size())
print("Is empty:", tree.is_empty())

print("Inorder after clearing:", tree.inorder())

# INSERT AFTER CLEAR
print("\n--- INSERT AFTER CLEAR ---")

tree.insert(100)
tree.insert(50)
tree.insert(150)

print("Inorder:", tree.inorder())