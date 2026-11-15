from typing import List, Sequence

# MERGE
# Combines two sorted portions:
# [left, middle) and [middle, right).

def merge(
    values: List[int],
    temp: List[int],
    left: int,
    middle: int,
    right: int
) -> None:
    i = left
    j = middle
    k = left

    # Compare elements from both halves.
    while i < middle and j < right:
        # Select the left element first when values are equal.
        # This preserves stability.
        if values[i] <= values[j]:
            temp[k] = values[i]
            i += 1
        else:
            temp[k] = values[j]
            j += 1

        k += 1

    # Copy remaining elements from the left half.
    while i < middle:
        temp[k] = values[i]

        i += 1
        k += 1

    # Copy remaining elements from the right half.
    while j < right:
        temp[k] = values[j]

        j += 1
        k += 1

    # Copy the merged portion back into the original list.
    for index in range(left, right):
        values[index] = temp[index]


# MERGE SORT RECURSIVE HELPER
# Sorts the half-open range [left, right).

def merge_sort_range(
    values: List[int],
    temp: List[int],
    left: int,
    right: int
) -> None:
    # A range containing zero or one element is already sorted.
    if right - left <= 1:
        return

    # Divide the range into two halves.
    middle = left + (right - left) // 2

    # Sort the left half.
    merge_sort_range(values, temp, left, middle)

    # Sort the right half.
    merge_sort_range(values, temp, middle, right)

    # Merge the two sorted halves.
    merge(values, temp, left, middle, right)


# MERGE SORT
# Sorts the original list in ascending order.

def merge_sort(values: List[int]) -> None:
    if len(values) <= 1:
        return

    # Allocate one temporary list and reuse it for all merges.
    temp = [0] * len(values)

    merge_sort_range(
        values,
        temp,
        0,
        len(values)
    )


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    merge_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== MERGE SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [8, 3, 5, 4, 7, 6, 1, 2]

print("Before sorting:", values)

merge_sort(values)

print("After sorting: ", values)


# EDGE CASES
print("\n--- EDGE CASES ---")

test_sort([], [], "Empty array")

test_sort([42], [42], "Single element")

test_sort(
    [9, 3],
    [3, 9],
    "Two elements"
)

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
    [9, 1, 7, 3, 5],
    [1, 3, 5, 7, 9],
    "Odd-sized array"
)