from typing import List, Sequence

# BUBBLE SORT
# Sorts the list in ascending order.
# Uses early exit when a pass makes no swaps.

def bubble_sort(values: List[int]) -> None:
    n = len(values)

    for i in range(n - 1):
        swapped = False

        # The last i elements are already sorted.
        for j in range(n - i - 1):
            if values[j] > values[j + 1]:
                values[j], values[j + 1] = values[j + 1], values[j]

                swapped = True

        # No swaps means the array is already sorted.
        if not swapped:
            break


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    bubble_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== BUBBLE SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [5, 3, 8, 4, 2]

print("Before sorting:", values)

bubble_sort(values)

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