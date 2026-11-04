from typing import Callable, Sequence

# DISCRETE TERNARY SEARCH
# Finds the index of the maximum element in a unimodal array.
# Returns -1 if the array is empty.

def ternary_search_maximum(values: Sequence[int]) -> int:
    if not values:
        return -1

    left = 0
    right = len(values) - 1

    # Narrow the search interval.
    while right - left > 2:
        third = (right - left) // 3

        middle_one = left + third
        middle_two = right - third

        if values[middle_one] < values[middle_two]:
            # The maximum must be to the right.
            left = middle_one + 1
        else:
            # The maximum must be to the left.
            right = middle_two - 1

    # Check the remaining elements.
    best_index = left

    for index in range(left + 1, right + 1):
        if values[index] > values[best_index]:
            best_index = index

    return best_index


# CONTINUOUS TERNARY SEARCH
# Finds the approximate maximum position of a unimodal function.
# The function is evaluated 100 times.

def ternary_search_continuous_maximum(
    function: Callable[[float], float],
    left: float,
    right: float
) -> float:
    if left > right:
        left, right = right, left

    for _ in range(100):
        third = (right - left) / 3.0

        middle_one = left + third
        middle_two = right - third

        if function(middle_one) < function(middle_two):
            left = middle_one
        else:
            right = middle_two

    return left + (right - left) / 2.0


# Example function:
# f(x) = -(x - 3)^2 + 10
# Maximum is at x = 3, with value 10.

def objective_function(x: float) -> float:
    difference = x - 3.0

    return -(difference * difference) + 10.0


# Helper function for discrete search tests.
def test_discrete_search(
    values: Sequence[int],
    expected_index: int,
    description: str
) -> None:
    result = ternary_search_maximum(values)

    status = "PASSED" if result == expected_index else "FAILED"

    print(f"{description}: {result} [{status}]")


# Helper function for continuous search tests.
def test_continuous_search(
    left: float,
    right: float,
    expected: float,
    description: str
) -> None:
    result = ternary_search_continuous_maximum(
        objective_function,
        left,
        right
    )

    status = "PASSED" if abs(result - expected) < 0.0000001 else "FAILED"

    print(f"{description}: {result:.8f} [{status}]")


# DEMONSTRATION

print("==== TERNARY SEARCH ====")

# DISCRETE TERNARY SEARCH
print("\n--- DISCRETE TERNARY SEARCH ---")

values = [1, 3, 8, 12, 14, 11, 7, 4, 2]

print("Array:", values)

peak_index = ternary_search_maximum(values)

print("Maximum index:", peak_index)
print("Maximum value:", values[peak_index])

# DISCRETE EDGE CASES
print("\n--- DISCRETE EDGE CASES ---")

test_discrete_search(
    [], -1, "Empty array"
)

test_discrete_search(
    [42], 0, "Single element"
)

test_discrete_search(
    [1, 2, 3, 4, 5], 4, "Increasing array"
)

test_discrete_search(
    [5, 4, 3, 2, 1], 0, "Decreasing array"
)

test_discrete_search(
    [1, 3, 5, 5, 5, 4, 2], 2, "Maximum plateau"
)

# CONTINUOUS TERNARY SEARCH
print("\n--- CONTINUOUS TERNARY SEARCH ---")

test_continuous_search(
    -10.0, 10.0, 3.0, "Search in [-10, 10]"
)

test_continuous_search(
    0.0, 10.0, 3.0, "Search in [0, 10]"
)

test_continuous_search(
    4.0, 10.0, 4.0, "Maximum at left boundary"
)

test_continuous_search(
    -10.0, 2.0, 2.0, "Maximum at right boundary"
)