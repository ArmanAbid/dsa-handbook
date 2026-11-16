from typing import Sequence, List

class DifferenceArray:
    def __init__(self, values: Sequence[int]):
        # BUILD: Construct the difference array.
        self._diff: List[int] = [0] * len(values)

        if not values:
            return

        self._diff[0] = values[0]

        for i in range(1, len(values)):
            self._diff[i] = values[i] - values[i - 1]

    # RANGE UPDATE:
    # Add value to every element in inclusive range [left, right].
    # Returns False if the range is invalid.
    def range_add(self, left: int, right: int, value: int) -> bool:
        if left < 0 or right < left or right >= len(self._diff):
            return False

        self._diff[left] += value

        # Cancel the update immediately after the requested range.
        if right + 1 < len(self._diff):
            self._diff[right + 1] -= value

        return True

    # RECONSTRUCT: Build the final array using Prefix Sum.
    def build_array(self) -> List[int]:
        result = []
        current = 0

        for difference in self._diff:
            current += difference
            result.append(current)

        return result

    # SIZE: Get the number of elements.
    def size(self) -> int:
        return len(self._diff)

    # CHECK: Is the structure empty?
    def is_empty(self) -> bool:
        return len(self._diff) == 0


# Test a range update.
def test_update(
    values: DifferenceArray,
    left: int,
    right: int,
    delta: int,
    expected: bool,
    description: str
) -> None:
    result = values.range_add(left, right, delta)

    status = "PASSED" if result == expected else "FAILED"

    display = "Updated" if result else "Rejected"

    print(f"{description}: {display} [{status}]")


# Test reconstructed output.
def test_array(
    values: DifferenceArray,
    expected: Sequence[int],
    description: str
) -> None:
    result = values.build_array()

    status = "PASSED" if result == list(expected) else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== DIFFERENCE ARRAY ====")

# BASIC EXAMPLE
print("\n--- BUILD DIFFERENCE ARRAY ---")

initial = [10, 20, 30, 40, 50]

values = DifferenceArray(initial)

print("Original array:", initial)
print("Size:", values.size())
print("Is empty:", values.is_empty())


# RANGE UPDATES
print("\n--- RANGE UPDATES ---")

test_update(
    values, 1, 3, 5, True,
    "Add 5 to range [1, 3]"
)

test_update(
    values, 0, 2, -3, True,
    "Add -3 to range [0, 2]"
)

test_update(
    values, 2, 4, 10, True,
    "Add 10 to range [2, 4]"
)

test_array(
    values,
    [7, 22, 42, 55, 60],
    "Final array after three updates"
)


# EDGE CASES
print("\n--- EDGE CASES ---")

empty_array = DifferenceArray([])

print("Empty array size:", empty_array.size())
print("Empty check:", empty_array.is_empty())

test_update(
    empty_array, 0, 0, 5, False,
    "Update empty array"
)

single_array = DifferenceArray([10])

test_update(
    single_array, 0, 0, 5, True,
    "Single-element update"
)

test_array(
    single_array,
    [15],
    "Single-element result"
)


# FULL ARRAY UPDATE
print("\n--- FULL ARRAY UPDATE ---")

full_array = DifferenceArray([1, 2, 3])

test_update(
    full_array, 0, 2, 10, True,
    "Add 10 to entire array"
)

test_array(
    full_array,
    [11, 12, 13],
    "Full array result"
)


# OVERLAPPING UPDATES
print("\n--- OVERLAPPING UPDATES ---")

overlapping = DifferenceArray([0, 0, 0, 0, 0])

overlapping.range_add(0, 2, 5)
overlapping.range_add(1, 4, 3)

test_array(
    overlapping,
    [5, 8, 8, 3, 3],
    "Overlapping range updates"
)


# INVALID RANGES
print("\n--- INVALID RANGES ---")

test_update(
    overlapping, -1, 2, 5, False,
    "Negative left index"
)

test_update(
    overlapping, 0, 5, 5, False,
    "Right index out of bounds"
)

test_update(
    overlapping, 3, 1, 5, False,
    "Left greater than right"
)