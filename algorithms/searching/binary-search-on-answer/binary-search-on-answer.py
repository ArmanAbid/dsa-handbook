from typing import Sequence

# FEASIBILITY CHECK
# Can all packages be shipped within the allowed days
# using the given capacity?

def can_ship_within_days(
    weights: Sequence[int],
    days: int,
    capacity: int
) -> bool:
    used_days = 1
    current_load = 0

    for weight in weights:
        if current_load + weight > capacity:
            # Start a new day.
            used_days += 1
            current_load = weight

        else:
            current_load += weight

        # No need to continue if the limit is exceeded.
        if used_days > days:
            return False

    return True


# BINARY SEARCH ON ANSWER
# Returns the minimum capacity required.
# Returns -1 for invalid input.

def minimum_ship_capacity(
    weights: Sequence[int],
    days: int
) -> int:
    if days <= 0:
        return -1

    if not weights:
        return 0

    # Package weights must be positive.
    if any(weight <= 0 for weight in weights):
        return -1

    # Define the search boundaries.
    low = max(weights)
    high = sum(weights)

    # Search for the first feasible capacity.
    while low < high:
        middle = low + (high - low) // 2

        if can_ship_within_days(weights, days, middle):
            # This capacity works.
            # Try to find a smaller one.
            high = middle

        else:
            # This capacity is insufficient.
            low = middle + 1

    return low


# Helper function for demonstration.
def test_minimum_capacity(
    weights: Sequence[int],
    days: int,
    expected: int,
    description: str
) -> None:
    result = minimum_ship_capacity(weights, days)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{description}: {result} [{status}]")


# DEMONSTRATION

print("==== BINARY SEARCH ON ANSWER ====")

weights = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# DISPLAY INPUT
print("\nWeights:", weights)

# BASIC TESTS
print("\n--- BASIC TESTS ---")

test_minimum_capacity(weights, 5, 15, "Ship within 5 days")
test_minimum_capacity(weights, 3, 21, "Ship within 3 days")
test_minimum_capacity(weights, 10, 10, "Ship within 10 days")
test_minimum_capacity(weights, 1, 55, "Ship within 1 day")

# EDGE CASES
print("\n--- EDGE CASES ---")

test_minimum_capacity([], 5, 0, "Empty package array")

test_minimum_capacity([7], 2, 7, "Single package")
test_minimum_capacity([7], 1, 7, "Single package, one day")

test_minimum_capacity(
    [5, 5, 5, 5], 2, 10, "Equal package weights"
)

test_minimum_capacity(
    [3, 2, 2, 4, 1, 4], 3, 6, "Another shipping example"
)

# INVALID INPUT
print("\n--- INVALID INPUT ---")

test_minimum_capacity(weights, 0, -1, "Zero allowed days")
test_minimum_capacity(weights, -2, -1, "Negative allowed days")

test_minimum_capacity(
    [3, 0, 5], 2, -1, "Zero package weight"
)