from typing import Sequence

# INTERPOLATION SEARCH
# Requires ascending sorted input.
# Returns the first occurrence, or -1 if not found.

def interpolation_search(
    values: Sequence[int],
    target: int
) -> int:
    if not values:
        return -1

    low = 0
    high = len(values) - 1

    answer = -1

    while (
        low <= high
        and values[low] <= target <= values[high]
    ):
        # Avoid division by zero.
        if values[low] == values[high]:
            if values[low] == target:
                answer = low

            break

        # Estimate the target's likely position.
        numerator = (target - values[low]) * (high - low)
        denominator = values[high] - values[low]

        position = low + numerator // denominator

        # Keep the estimated position within the search range.
        position = max(low, min(position, high))

        current_value = values[position]

        if current_value < target:
            low = position + 1

        else:
            if current_value == target:
                answer = position

            # Continue searching for an earlier occurrence.
            high = position - 1

    return answer


# Helper function for demonstration.
def test_search(
    values: Sequence[int],
    target: int,
    expected: int,
    description: str
) -> None:
    result = interpolation_search(values, target)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== INTERPOLATION SEARCH ====")

# UNIFORMLY DISTRIBUTED VALUES
print("\n--- UNIFORM DISTRIBUTION ---")

values = list(range(10, 101, 10))

print("Sorted array:", values)

test_search(values, 80, 7, "Search for 80")
test_search(values, 10, 0, "Search for 10")
test_search(values, 100, 9, "Search for 100")
test_search(values, 55, -1, "Search for 55")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_search([], 10, -1, "Empty array")

test_search([42], 42, 0, "Single element found")
test_search([42], 10, -1, "Single element not found")

test_search(values, 5, -1, "Target smaller than all elements")
test_search(values, 110, -1, "Target larger than all elements")

# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-50, -40, -30, -20, -10, 0]

test_search(negative_values, -30, 2, "Search for -30")

# DUPLICATES
print("\n--- DUPLICATES ---")

duplicate_values = [1, 2, 2, 2, 2, 3]

test_search(
    duplicate_values,
    2,
    1,
    "First occurrence of 2"
)

# ALL ELEMENTS EQUAL
print("\n--- ALL ELEMENTS EQUAL ---")

equal_values = [5, 5, 5, 5]

test_search(equal_values, 5, 0, "Search for 5")
test_search(equal_values, 8, -1, "Search for 8")

# NONUNIFORM DISTRIBUTION
print("\n--- NONUNIFORM DISTRIBUTION ---")

nonuniform_values = [1, 2, 3, 4, 1000]

test_search(
    nonuniform_values,
    1000,
    4,
    "Search in nonuniform data"
)

# LARGE INTEGER VALUES
print("\n--- LARGE INTEGER VALUES ---")

large_values = [-10**18, 0, 10**18]

test_search(
    large_values,
    10**18,
    2,
    "Search with large integers"
)