from typing import List, Sequence

# COUNTING SORT
# Supports negative and positive integers.
# Sorts the original list in ascending order.
# Uses cumulative counts to preserve stability.

def counting_sort(values: List[int]) -> None:
    if len(values) <= 1:
        return

    # STEP 1: Find minimum and maximum values.
    minimum = min(values)
    maximum = max(values)

    # Calculate the number of possible integer values.
    value_range = maximum - minimum + 1

    # STEP 2: Create the counting array.
    counts = [0] * value_range

    # Count the occurrences of each value.
    for value in values:
        index = value - minimum
        counts[index] += 1

    # STEP 3: Calculate cumulative counts.
    for i in range(1, value_range):
        counts[i] += counts[i - 1]

    # STEP 4: Construct the output array.
    output = [0] * len(values)

    # Traverse backwards to preserve stability.
    for value in reversed(values):
        index = value - minimum

        counts[index] -= 1

        output[counts[index]] = value

    # Copy the sorted output back into the original list.
    values[:] = output


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    counting_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== COUNTING SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [4, 2, 2, 8, 3, 3, 1]

print("Before sorting:", values)

counting_sort(values)

print("After sorting: ", values)


# EDGE CASES
print("\n--- EDGE CASES ---")

test_sort([], [], "Empty array")

test_sort([42], [42], "Single element")

test_sort(
    [1, 2, 3, 4, 5],
    [1, 2, 3, 4, 5],
    "Already sorted"
)

test_sort(
    [5, 4, 3, 2, 1],
    [1, 2, 3, 4, 5],
    "Reverse sorted"
)

test_sort(
    [4, 2, 4, 1, 2],
    [1, 2, 2, 4, 4],
    "Duplicate values"
)

test_sort(
    [7, 7, 7, 7],
    [7, 7, 7, 7],
    "All elements equal"
)

test_sort(
    [-5, -2, -5, 0, 3, -2],
    [-5, -5, -2, -2, 0, 3],
    "Negative and positive values"
)

test_sort(
    [0, -3, 2, -1, 3, -2],
    [-3, -2, -1, 0, 2, 3],
    "Mixed negative and positive values"
)