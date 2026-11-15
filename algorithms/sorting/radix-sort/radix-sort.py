from typing import List, Sequence

# STABLE COUNTING SORT BY DIGIT
# Sorts values according to one decimal digit.
# The original values and their transformed keys move together.

def counting_sort_by_digit(
    values: List[int],
    keys: List[int],
    exponent: int
) -> None:
    n = len(values)

    counts = [0] * 10

    # STEP 1: Count occurrences of each digit.
    for key in keys:
        digit = (key // exponent) % 10
        counts[digit] += 1

    # STEP 2: Calculate cumulative counts.
    for i in range(1, 10):
        counts[i] += counts[i - 1]

    # STEP 3: Construct output backwards to preserve stability.
    output = [0] * n
    output_keys = [0] * n

    for i in range(n - 1, -1, -1):
        value = values[i]
        key = keys[i]

        digit = (key // exponent) % 10

        counts[digit] -= 1

        position = counts[digit]

        output[position] = value
        output_keys[position] = key

    # Copy the sorted result back.
    values[:] = output
    keys[:] = output_keys


# RADIX SORT
# Supports negative and positive integers.
# Sorts the original list in ascending order.

def radix_sort(values: List[int]) -> None:
    if len(values) <= 1:
        return

    # STEP 1: Find minimum and maximum values.
    minimum = min(values)
    maximum = max(values)

    # STEP 2: Transform values into non-negative keys.
    keys = [value - minimum for value in values]

    max_key = maximum - minimum

    # STEP 3: Process decimal digits from right to left.
    exponent = 1

    while max_key // exponent > 0:
        counting_sort_by_digit(
            values,
            keys,
            exponent
        )

        exponent *= 10


# Test a sorting case.
def test_sort(
    input_values: Sequence[int],
    expected: Sequence[int],
    description: str
) -> None:
    values = list(input_values)

    radix_sort(values)

    passed = values == list(expected)

    status = "PASSED" if passed else "FAILED"

    print(f"{description}: {values} [{status}]")


# DEMONSTRATION

print("==== RADIX SORT ====")

# BASIC EXAMPLE
print("\n--- BASIC SORTING ---")

values = [170, 45, 75, 90, 802, 24, 2, 66]

print("Before sorting:", values)

radix_sort(values)

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

# DIFFERENT NUMBER OF DIGITS
print("\n--- DIFFERENT DIGIT LENGTHS ---")

test_sort(
    [1000, 5, 50, 500, 1],
    [1, 5, 50, 500, 1000],
    "Different digit lengths"
)

# LARGE INTEGER VALUES
print("\n--- LARGE INTEGER VALUES ---")

test_sort(
    [10**20, -10**20, 0, -5, 5],
    [-10**20, -5, 0, 5, 10**20],
    "Very large integers"
)