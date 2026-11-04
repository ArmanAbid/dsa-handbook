from typing import Sequence

# BINARY SEARCH WITHIN A KNOWN RANGE.
# Returns the first occurrence of the target.

def binary_search_first_occurrence(
    values: Sequence[int],
    target: int,
    left: int,
    right: int
) -> int:
    answer = -1

    while left <= right:
        middle = left + (right - left) // 2

        if values[middle] >= target:
            if values[middle] == target:
                answer = middle

            # Continue looking for an earlier occurrence.
            right = middle - 1

        else:
            left = middle + 1

    return answer


# EXPONENTIAL SEARCH
# Requires ascending sorted input.
# Returns the first occurrence, or -1 if not found.

def exponential_search(
    values: Sequence[int],
    target: int
) -> int:
    n = len(values)

    if n == 0:
        return -1

    if values[0] == target:
        return 0

    if values[0] > target:
        return -1

    low = 0
    high = 1

    # Find a range that can contain the target.
    while high < n and values[high] < target:
        low = high
        high *= 2

    # The previous boundary is known to be smaller
    # than the target, so search starts after it.
    left = low + 1
    right = min(high, n - 1)

    return binary_search_first_occurrence(
        values,
        target,
        left,
        right
    )


# Helper function for demonstration.
def test_search(
    values: Sequence[int],
    target: int,
    expected: int,
    description: str
) -> None:
    result = exponential_search(values, target)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== EXPONENTIAL SEARCH ====")

values = [
    2, 4, 6, 8, 10, 12, 14, 16,
    18, 20, 22, 24, 26, 28, 30
]

# DISPLAY ARRAY
print("\nSorted array:", values)

# BASIC SEARCH
print("\n--- BASIC SEARCH ---")

test_search(values, 22, 10, "Search for 22")
test_search(values, 2, 0, "Search for 2")
test_search(values, 4, 1, "Search for 4")
test_search(values, 30, 14, "Search for 30")
test_search(values, 17, -1, "Search for 17")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_search([], 10, -1, "Empty array")

test_search([42], 42, 0, "Single element found")
test_search([42], 10, -1, "Single element not found")

test_search(values, 1, -1, "Target smaller than all elements")
test_search(values, 50, -1, "Target larger than all elements")

# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-20, -10, -5, 0, 5]

test_search(negative_values, -10, 1, "Search for -10")

# DUPLICATES
print("\n--- DUPLICATES ---")

duplicate_values = [2, 4, 4, 4, 6, 8]

test_search(
    duplicate_values,
    4,
    1,
    "First occurrence of 4"
)