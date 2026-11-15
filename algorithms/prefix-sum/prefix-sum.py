from typing import List, Optional, Sequence

# BUILD PREFIX SUM
# prefix[i] represents the sum of the first i elements.
# Therefore, prefix[0] is always zero.

def build_prefix_sum(values: Sequence[int]) -> List[int]:
    prefix = [0]

    for value in values:
        prefix.append(prefix[-1] + value)

    return prefix


# RANGE SUM QUERY
# Returns the sum of the inclusive range [left, right].
# Returns None for an invalid range.

def range_sum(
    prefix: Sequence[int],
    left: int,
    right: int
) -> Optional[int]:
    if len(prefix) == 0:
        return None

    if left < 0 or right < left:
        return None

    n = len(prefix) - 1

    if right >= n:
        return None

    return prefix[right + 1] - prefix[left]


# Test a range sum query.
def test_range_sum(
    prefix: Sequence[int],
    left: int,
    right: int,
    expected: Optional[int],
    description: str
) -> None:
    result = range_sum(prefix, left, right)

    passed = result == expected

    status = "PASSED" if passed else "FAILED"

    display = result if result is not None else "Invalid range"

    print(f"{description}: {display} [{status}]")


# DEMONSTRATION

print("==== PREFIX SUM ====")

# BASIC EXAMPLE
print("\n--- BUILD PREFIX SUM ---")

values = [2, 4, 1, 7, 3, 6]

prefix = build_prefix_sum(values)

print("Original array:", values)
print("Prefix array:  ", prefix)


# RANGE SUM QUERIES
print("\n--- RANGE SUM QUERIES ---")

test_range_sum(prefix, 1, 4, 15, "Sum from index 1 to 4")
test_range_sum(prefix, 0, 2, 7, "Sum from index 0 to 2")
test_range_sum(prefix, 2, 5, 17, "Sum from index 2 to 5")
test_range_sum(prefix, 0, 5, 23, "Sum of entire array")
test_range_sum(prefix, 3, 3, 7, "Single element range")


# EDGE CASES
print("\n--- EDGE CASES ---")

empty_prefix = build_prefix_sum([])

test_range_sum(
    empty_prefix, 0, 0, None,
    "Empty array"
)

single_prefix = build_prefix_sum([42])

test_range_sum(
    single_prefix, 0, 0, 42,
    "Single element"
)

test_range_sum(
    prefix, -1, 2, None,
    "Negative left index"
)

test_range_sum(
    prefix, 0, 6, None,
    "Right index out of bounds"
)

test_range_sum(
    prefix, 4, 2, None,
    "Left greater than right"
)


# NEGATIVE VALUES
print("\n--- NEGATIVE VALUES ---")

negative_values = [-5, -2, -8, -1, -3]

negative_prefix = build_prefix_sum(negative_values)

print("Prefix array:", negative_prefix)

test_range_sum(
    negative_prefix, 1, 3, -11,
    "Sum of negative range"
)


# ZERO VALUES
print("\n--- ZERO VALUES ---")

zero_prefix = build_prefix_sum([0, 0, 0])

test_range_sum(
    zero_prefix, 0, 2, 0,
    "All zero values"
)


# LARGE SUM
print("\n--- LARGE SUM ---")

large_values = [2_000_000_000, 2_000_000_000, 2_000_000_000]

large_prefix = build_prefix_sum(large_values)

test_range_sum(
    large_prefix, 0, 2, 6_000_000_000,
    "Sum exceeding 32-bit integer range"
)