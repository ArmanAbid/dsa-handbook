from typing import List, Sequence

# INSERTION SORT
# Sorts the list in ascending order.
# Builds a sorted portion by inserting each new element
# into its correct position.

def insertion_sort(values: List[int]) -> None:
    n = len(values)

    for i in range(1, n):
        # Store the current element.
        key = values[i]

        # Start comparing with the element immediately to the left.
        j = i

        # Shift elements greater than key one position to the right.
        while j > 0 and values[j - 1] > key:
            values[j] = values[j - 1]
            j -= 1

        # Insert key into its correct position.
        values[j] = key


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    insertion_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== INSERTION SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [5, 3, 8, 4, 2]

print("Before sorting:", values)

insertion_sort(values)

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

test_sort(
    [1, 2, 4, 3, 5],
    [1, 2, 3, 4, 5],
    "Nearly sorted"
)