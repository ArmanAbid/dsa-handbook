from typing import Optional, Sequence, Tuple

# FIXED-SIZE SLIDING WINDOW
# Finds the maximum sum of a contiguous subarray
# containing exactly k elements.
#
# Returns (maximum_sum, start_index, end_index).
# Returns None for an invalid window size.

def maximum_sum_subarray(
    values: Sequence[int],
    k: int
) -> Optional[Tuple[int, int, int]]:
    if k <= 0 or k > len(values):
        return None

    # STEP 1: Calculate the first window sum.
    current_sum = sum(values[:k])

    # Initialize the best result using the first actual window.
    best_sum = current_sum
    best_start = 0
    best_end = k - 1

    # STEP 2: Slide the window.
    for end_index in range(k, len(values)):
        # Remove the element leaving the window.
        current_sum -= values[end_index - k]

        # Add the element entering the window.
        current_sum += values[end_index]

        # Update only when a strictly better sum is found.
        # This preserves the first window when sums are equal.
        if current_sum > best_sum:
            best_sum = current_sum
            best_start = end_index - k + 1
            best_end = end_index

    return best_sum, best_start, best_end


# Helper function for testing.
def test_maximum_sum(
    values: Sequence[int],
    k: int,
    expected: Optional[Tuple[int, int, int]],
    description: str
) -> None:
    result = maximum_sum_subarray(values, k)

    passed = result == expected

    status = "PASSED" if passed else "FAILED"

    display = result if result is not None else "No valid window"

    print(f"{description}: {display} [{status}]")


# DEMONSTRATION

print("==== SLIDING WINDOW ====")

# BASIC EXAMPLE
print("\n--- MAXIMUM SUM SUBARRAY ---")

values = [2, 1, 5, 1, 3, 2]

print("Array:", values)
print("Window size: 3")

test_maximum_sum(
    values, 3, (9, 2, 4),
    "Maximum sum"
)


# EDGE CASES
print("\n--- EDGE CASES ---")

test_maximum_sum(
    [], 2, None,
    "Empty array"
)

test_maximum_sum(
    [7], 1, (7, 0, 0),
    "Single element"
)

test_maximum_sum(
    [7], 2, None,
    "Window larger than array"
)

test_maximum_sum(
    values, 0, None,
    "Zero window size"
)

test_maximum_sum(
    values, -2, None,
    "Negative window size"
)

test_maximum_sum(
    values, 6, (14, 0, 5),
    "Window equals array size"
)


# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-5, -2, -8, -1, -3]

test_maximum_sum(
    negative_values, 2, (-4, 3, 4),
    "All negative values"
)


# DUPLICATE MAXIMUM WINDOWS
print("\n--- EQUAL MAXIMUM WINDOWS ---")

equal_values = [4, 4, 4, 4]

test_maximum_sum(
    equal_values, 2, (8, 0, 1),
    "First window among equal maximum sums"
)


# MAXIMUM AT DIFFERENT POSITIONS
print("\n--- MAXIMUM WINDOW POSITIONS ---")

test_maximum_sum(
    [10, 2, 3, 1], 2, (12, 0, 1),
    "Maximum at first window"
)

test_maximum_sum(
    [1, 2, 3, 10], 2, (13, 2, 3),
    "Maximum at last window"
)