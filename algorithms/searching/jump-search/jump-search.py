from math import isqrt
from typing import Sequence

# JUMP SEARCH
# Requires an array sorted in ascending order.
# Returns the first occurrence of the target.
# Returns -1 if the target is not found.

def jump_search(values: Sequence[int], target: int) -> int:
    n = len(values)

    if n == 0:
        return -1

    # Calculate the optimal block size: floor(sqrt(n)).
    block_size = isqrt(n)

    start = 0
    end = block_size

    if end > n:
        end = n

    # STAGE 1: Find the candidate block.
    while values[end - 1] < target:
        start = end

        if start >= n:
            return -1

        end = min(end + block_size, n)

    # STAGE 2: Linear Search inside the candidate block.
    for index in range(start, end):
        if values[index] == target:
            return index

        # The array is sorted, so no later value can match.
        if values[index] > target:
            return -1

    return -1


# Helper function for demonstration.
def test_search(
    values: Sequence[int],
    target: int,
    expected: int,
    description: str
) -> None:
    result = jump_search(values, target)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== JUMP SEARCH ====")

values = [
    1, 3, 5, 7, 9, 11, 13, 15,
    17, 19, 21, 23, 25, 27, 29
]

# DISPLAY ARRAY
print("\nSorted array:", values)

# BASIC SEARCH
print("\n--- BASIC SEARCH ---")

test_search(values, 19, 9, "Search for 19")
test_search(values, 1, 0, "Search for 1")
test_search(values, 15, 7, "Search for 15")
test_search(values, 29, 14, "Search for 29")
test_search(values, 20, -1, "Search for 20")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_search([], 10, -1, "Empty array")

test_search([42], 42, 0, "Single element found")
test_search([42], 10, -1, "Single element not found")

test_search(values, 0, -1, "Target smaller than all elements")
test_search(values, 40, -1, "Target larger than all elements")

# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-20, -10, -5, 0, 5]

test_search(negative_values, -10, 1, "Search for -10")

# DUPLICATES
print("\n--- DUPLICATES ---")

duplicate_values = [1, 2, 2, 2, 2, 3]

test_search(
    duplicate_values,
    2,
    1,
    "First occurrence of 2"
)

equal_values = [5, 5, 5, 5]

test_search(
    equal_values,
    5,
    0,
    "All elements equal"
)