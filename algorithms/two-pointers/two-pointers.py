from typing import Optional, Sequence, Tuple

# TWO POINTERS: PAIR SUM
# Requires ascending sorted input.
# Returns the matching indices.
# Returns None when no matching pair exists.

def find_pair_with_sum(
    values: Sequence[int],
    target: int
) -> Optional[Tuple[int, int]]:
    if len(values) < 2:
        return None

    left = 0
    right = len(values) - 1

    while left < right:
        current_sum = values[left] + values[right]

        if current_sum == target:
            return left, right

        if current_sum < target:
            # Increase the sum by moving the left pointer.
            left += 1

        else:
            # Decrease the sum by moving the right pointer.
            right -= 1

    return None


# Helper function for demonstration.
def test_pair(
    values: Sequence[int],
    target: int,
    expected: Optional[Tuple[int, int]],
    description: str
) -> None:
    result = find_pair_with_sum(values, target)

    passed = result == expected

    status = "PASSED" if passed else "FAILED"

    display = result if result is not None else "Not found"

    print(f"{description}: {display} [{status}]")


# DEMONSTRATION

print("==== TWO POINTERS ====")

# BASIC EXAMPLE
print("\n--- BASIC PAIR SUM ---")

values = [1, 2, 4, 6, 8, 9, 11]

print("Sorted array:", values)

test_pair(
    values, 10, (0, 5),
    "Find pair with sum 10"
)

test_pair(
    values, 13, (1, 6),
    "Find pair with sum 13"
)

test_pair(
    values, 21, None,
    "No pair with sum 21"
)


# EDGE CASES
print("\n--- EDGE CASES ---")

test_pair(
    [], 10, None,
    "Empty array"
)

test_pair(
    [5], 10, None,
    "Single element"
)

test_pair(
    [3, 7], 10, (0, 1),
    "Two elements"
)

test_pair(
    [3, 7], 8, None,
    "Two elements without a pair"
)


# DUPLICATES
print("\n--- DUPLICATES ---")

duplicate_values = [1, 2, 2, 2, 4]

test_pair(
    duplicate_values, 4, (1, 3),
    "Duplicate values"
)

equal_values = [5, 5, 5]

test_pair(
    equal_values, 10, (0, 2),
    "All elements equal"
)


# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-8, -3, 0, 4, 9]

test_pair(
    negative_values, 1, (0, 4),
    "Negative and positive pair"
)

test_pair(
    negative_values, -11, (0, 1),
    "Negative pair"
)

test_pair(
    negative_values, 100, None,
    "Target too large"
)