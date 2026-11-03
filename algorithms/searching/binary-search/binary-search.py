from typing import Sequence

# BINARY SEARCH
# Requires an array sorted in ascending order.
# Returns the first occurrence of the target.
# Returns -1 if the target is not found.

def binary_search(values: Sequence[int], target: int) -> int:
    left = 0
    right = len(values)

    # Search using a half-open interval [left, right).
    while left < right:
        middle = left + (right - left) // 2

        if values[middle] < target:
            # Target can only be in the right half.
            left = middle + 1
        else:
            # Keep the middle in the search range.
            # This allows us to find the first occurrence.
            right = middle

    # Check whether the target exists at the final position.
    if left < len(values) and values[left] == target:
        return left

    return -1


# Helper function for demonstration.
def test_search(
    values: Sequence[int],
    target: int,
    expected: int,
    description: str
) -> None:
    result = binary_search(values, target)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== BINARY SEARCH ====")

values = [2, 4, 4, 4, 7, 9, 12, 15]

# DISPLAY ARRAY
print("\nSorted array:", values)

# BASIC SEARCH
print("\n--- BASIC SEARCH ---")

test_search(values, 4, 1, "Search for 4")
test_search(values, 7, 4, "Search for 7")
test_search(values, 15, 7, "Search for 15")
test_search(values, 2, 0, "Search for 2")
test_search(values, 10, -1, "Search for 10")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_search([], 10, -1, "Empty array")

test_search([42], 42, 0, "Single element found")
test_search([42], 10, -1, "Single element not found")

test_search(values, 1, -1, "Target smaller than all elements")
test_search(values, 20, -1, "Target larger than all elements")

negative_values = [-10, -5, -2, 0, 5]

test_search(negative_values, -5, 1, "Negative number")

# DUPLICATE VALUES
print("\n--- DUPLICATES ---")

test_search(values, 4, 1, "First occurrence of 4")

equal_values = [5, 5, 5, 5]

test_search(equal_values, 5, 0, "All elements equal")