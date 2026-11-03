from typing import Sequence


# LINEAR SEARCH
# Returns the index of the first occurrence.
# Returns -1 if the target is not found.

def linear_search(values: Sequence[int], target: int) -> int:
    for index, value in enumerate(values):
        if value == target:
            return index

    return -1


# Helper function for demonstration.
def test_search(
    values: Sequence[int],
    target: int,
    expected: int,
    description: str
) -> None:
    result = linear_search(values, target)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== LINEAR SEARCH ====")

values = [8, 3, 6, 3, 9]

# DISPLAY ARRAY
print("\nArray:", values)

# BASIC SEARCH
print("\n--- BASIC SEARCH ---")

test_search(values, 3, 1, "Search for 3")
test_search(values, 6, 2, "Search for 6")
test_search(values, 9, 4, "Search for 9")
test_search(values, 5, -1, "Search for 5")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_search([], 10, -1, "Empty array")

test_search([42], 42, 0, "Single element found")
test_search([42], 10, -1, "Single element not found")

test_search([-5, -2, -8], -2, 1, "Negative number")

# DUPLICATE VALUES
print("\n--- DUPLICATES ---")

test_search(values, 3, 1, "First occurrence of 3")