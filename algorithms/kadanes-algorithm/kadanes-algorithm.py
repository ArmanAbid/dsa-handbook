from typing import Optional, Sequence, Tuple

def max_subarray_sum(
    values: Sequence[int]
) -> Optional[Tuple[int, int, int]]:
    """
    Returns:
        (maximum_sum, start_index, end_index)

    Returns None for an empty array.
    """

    if not values:
        return None

    current_sum = values[0]
    best_sum = values[0]

    current_start = 0
    best_start = 0
    best_end = 0

    for i in range(1, len(values)):
        value = values[i]
        extended_sum = current_sum + value

        # Extend the previous subarray or start a new one.
        if value > extended_sum:
            current_sum = value
            current_start = i
        else:
            current_sum = extended_sum

        # Update the best result.
        if current_sum > best_sum:
            best_sum = current_sum
            best_start = current_start
            best_end = i

    return best_sum, best_start, best_end


def test_result(
    values: Sequence[int],
    expected: Tuple[int, int, int],
    label: str
) -> None:
    result = max_subarray_sum(values)

    passed = result == expected

    print(
        f"{label}: {result}"
        f" {'[PASSED]' if passed else '[FAILED]'}"
    )


def main() -> None:
    print("=== KADANE'S ALGORITHM ===")

    print("\n--- BASIC EXAMPLE ---")

    values = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

    result = max_subarray_sum(values)

    print(f"Original array: {values}")

    if result is not None:
        best_sum, start, end = result

        subarray = values[start:end + 1]

        print(f"Maximum subarray sum: {best_sum}")
        print(f"Start index: {start}")
        print(f"End index: {end}")
        print(f"Maximum subarray: {subarray}")

    print("\n--- TEST CASES ---")

    test_result(
        [-8, -3, -6, -2, -5, -4],
        (-2, 3, 3),
        "All negative numbers"
    )

    test_result(
        [1, 2, 3, 4],
        (10, 0, 3),
        "All positive numbers"
    )

    test_result(
        [-7],
        (-7, 0, 0),
        "Single element"
    )

    test_result(
        [5, -1, 5],
        (9, 0, 2),
        "Positive values with a negative value"
    )

    test_result(
        [1, -1, 1],
        (1, 0, 0),
        "Multiple maximum subarrays"
    )

    print("\n--- EDGE CASES ---")

    empty_result = max_subarray_sum([])

    print(
        f"Empty array: "
        f"{'Rejected [PASSED]' if empty_result is None else '[FAILED]'}"
    )


if __name__ == "__main__":
    main()