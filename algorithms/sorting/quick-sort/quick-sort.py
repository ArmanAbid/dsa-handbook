from typing import List, Sequence

# QUICK SORT RANGE
# Uses three-way partitioning:
#
# [left, less - 1]       Values smaller than pivot.
# [less, greater]        Values equal to pivot.
# [greater + 1, right]   Values greater than pivot.
#
# Recursively sorts the smaller partition and iteratively
# processes the larger partition to limit stack usage.

def quick_sort_range(
    values: List[int],
    left: int,
    right: int
) -> None:
    while left < right:
        # Choose the middle-position element as the pivot.
        middle = left + (right - left) // 2
        pivot = values[middle]

        less = left
        current = left
        greater = right

        # THREE-WAY PARTITIONING
        while current <= greater:
            if values[current] < pivot:
                # Move smaller element into the left region.
                values[less], values[current] = (
                    values[current],
                    values[less]
                )

                less += 1
                current += 1

            elif values[current] > pivot:
                # Move greater element into the right region.
                values[current], values[greater] = (
                    values[greater],
                    values[current]
                )

                greater -= 1

                # Do not increment current.
                # The incoming element still needs examination.

            else:
                # Equal element belongs to the middle region.
                current += 1

        # Calculate the sizes of the unsorted portions.
        left_size = less - left
        right_size = right - greater

        # Recursively sort the smaller portion.
        # Process the larger portion using the loop.
        if left_size < right_size:
            quick_sort_range(
                values,
                left,
                less - 1
            )

            left = greater + 1

        else:
            quick_sort_range(
                values,
                greater + 1,
                right
            )

            right = less - 1


# QUICK SORT
# Sorts the original list in ascending order.

def quick_sort(values: List[int]) -> None:
    if len(values) <= 1:
        return

    quick_sort_range(
        values,
        0,
        len(values) - 1
    )


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    quick_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("=== QUICK SORT ===")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [8, 3, 5, 4, 7, 6, 1, 2]

print("Before sorting:", values)

quick_sort(values)

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
    [7, 7, 7, 7, 7],
    [7, 7, 7, 7, 7],
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