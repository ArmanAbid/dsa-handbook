from typing import List, Sequence

# SELECTION SORT
# Sorts the list in ascending order.
# Finds the minimum element in the unsorted portion
# and places it at the beginning of that portion.

def selection_sort(values: List[int]) -> None:
    n = len(values)

    for i in range(n - 1):
        # Assume the current position contains the minimum.
        min_index = i

        # Find the actual minimum in the remaining portion.
        for j in range(i + 1, n):
            if values[j] < values[min_index]:
                min_index = j

        # Swap only when the minimum is not already in place.
        if min_index != i:
            values[i], values[min_index] = values[min_index], values[i]


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    selection_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== SELECTION SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [5, 3, 8, 4, 2]

print("Before sorting:", values)

selection_sort(values)

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
    [-5, 3, -10, 0, 8],
    [-10, -5, 0, 3, 8],
    "Negative and positive values"
)