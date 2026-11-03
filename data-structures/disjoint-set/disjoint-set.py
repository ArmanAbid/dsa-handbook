from typing import Dict, List

class DisjointSet:
    def __init__(self, n: int):
        if n < 0:
            raise ValueError("Number of elements cannot be negative.")

        self._parent: List[int] = list(range(n))
        self._component_size: List[int] = [1] * n
        self._component_count = n

    # Check whether an element index is valid.
    def _is_valid(self, element: int) -> bool:
        return 0 <= element < len(self._parent)

    # FIND: Get the representative of an element.
    # Uses path compression.
    def find(self, element: int) -> int:
        if not self._is_valid(element):
            return -1

        if self._parent[element] != element:
            self._parent[element] = self.find(
                self._parent[element]
            )

        return self._parent[element]

    # UNION: Merge the components of two elements.
    # Uses union by size.
    def union_sets(self, first: int, second: int) -> bool:
        root_first = self.find(first)
        root_second = self.find(second)

        if root_first == -1 or root_second == -1:
            return False

        # Already in the same component.
        if root_first == root_second:
            return False

        # Attach the smaller component beneath the larger one.
        if (
            self._component_size[root_first]
            < self._component_size[root_second]
        ):
            root_first, root_second = root_second, root_first

        self._parent[root_second] = root_first

        self._component_size[root_first] += (
            self._component_size[root_second]
        )

        self._component_count -= 1

        return True

    # CONNECTED: Check whether two elements belong to the same set.
    def connected(self, first: int, second: int) -> bool:
        root_first = self.find(first)
        root_second = self.find(second)

        if root_first == -1 or root_second == -1:
            return False

        return root_first == root_second

    # GET COMPONENT SIZE: Return the size of an element's component.
    def get_component_size(self, element: int) -> int:
        representative = self.find(element)

        if representative == -1:
            return 0

        return self._component_size[representative]

    # GET COMPONENT COUNT: Number of separate components.
    def get_component_count(self) -> int:
        return self._component_count

    # SIZE: Get the total number of elements.
    def size(self) -> int:
        return len(self._parent)

    # CHECK: Check whether the DSU contains no elements.
    def is_empty(self) -> bool:
        return len(self._parent) == 0

    # DISPLAY: Show all components.
    def print_components(self) -> None:
        groups: Dict[int, List[int]] = {}

        for element in range(self.size()):
            representative = self.find(element)

            if representative not in groups:
                groups[representative] = []

            groups[representative].append(element)

        if not groups:
            print("Components: Empty")
            return

        formatted = [
            "{" + ", ".join(map(str, members)) + "}"
            for members in groups.values()
        ]

        print("Components:", " ".join(formatted))

    # RESET: Restore every element as its own component.
    def reset(self) -> None:
        n = self.size()

        self._parent = list(range(n))
        self._component_size = [1] * n
        self._component_count = n


# DEMONSTRATION

dsu = DisjointSet(7)

print("==== DISJOINT SET UNION ====")

# INITIAL STATE
print("\n--- INITIAL STATE ---")

dsu.print_components()

print("Elements:", dsu.size())
print("Components:", dsu.get_component_count())

# UNION
print("\n--- UNION ---")

dsu.union_sets(0, 1)
dsu.union_sets(1, 2)
dsu.union_sets(3, 4)
dsu.union_sets(5, 6)

dsu.print_components()

print("Components:", dsu.get_component_count())

# UNION ALREADY CONNECTED ELEMENTS
print("\n--- DUPLICATE UNION ---")

print("Union 0 and 2:", dsu.union_sets(0, 2))

print("Components:", dsu.get_component_count())

# FIND
print("\n--- FIND ---")

print("Representative of 0:", dsu.find(0))
print("Representative of 2:", dsu.find(2))
print("Representative of 4:", dsu.find(4))

# CONNECTED
print("\n--- CONNECTED ---")

print("Are 0 and 2 connected:", dsu.connected(0, 2))
print("Are 0 and 4 connected:", dsu.connected(0, 4))

# UNION COMPONENTS
print("\n--- MERGE COMPONENTS ---")

dsu.union_sets(2, 4)

dsu.print_components()

print("Components:", dsu.get_component_count())

# COMPONENT SIZE
print("\n--- COMPONENT SIZE ---")

print("Component size of 0:", dsu.get_component_size(0))
print("Component size of 3:", dsu.get_component_size(3))
print("Component size of 5:", dsu.get_component_size(5))

# INVALID ELEMENT
print("\n--- INVALID ELEMENT ---")

print("Find 10:", dsu.find(10))
print("Get size of 10:", dsu.get_component_size(10))

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Total elements:", dsu.size())
print("Is empty:", dsu.is_empty())

# RESET
print("\n--- RESET ---")

dsu.reset()

dsu.print_components()

print("Components after reset:", dsu.get_component_count())
print("Are 0 and 1 connected:", dsu.connected(0, 1))

# EMPTY DSU
print("\n--- EMPTY DSU ---")

empty_set = DisjointSet(0)

print("Is empty:", empty_set.is_empty())
print("Components:", empty_set.get_component_count())