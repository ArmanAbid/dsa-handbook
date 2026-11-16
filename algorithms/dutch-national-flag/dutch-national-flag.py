from typing import List

def dutch_national_flag(values: List[int]) -> bool:
    """
    Sorts an array containing only 0, 1, and 2 in-place.

    Returns False if the array contains an invalid value.
    """

    # Validate before modifying the array.
    for value in values:
        if (
            not isinstance(value, int)
            or isinstance(value, bool)
            or value not in (0, 1, 2)
        ):
            return False

    low = 0
    mid = 0
    high = len(values)

    while mid < high:
        if values[mid] == 0:
            # Move zero to the beginning.
            values[low], values[mid] = values[mid], values[low]

            low += 1
            mid += 1

        elif values[mid] == 1:
            # One is already in the correct partition.
            mid += 1

        else:
            # Move two to the end.
            high -= 1

            values[mid], values[high] = (
                values[high],
                values[mid]
            )

            # Do not increment mid.
            # The swapped value is still unprocessed.

    return True


def test_sort(
    values: List[int],
    expected: List[int],
    label: str
) -> None:
    valid = dutch_national_flag(values)
    passed = valid and values == expected

    print(
        f"{label}: {values} "
        f"{'[PASSED]' if passed else '[FAILED]'}"
    )


def main() -> None:
    print("==== DUTCH NATIONAL FLAG ====")

    print("\n--- BASIC EXAMPLE ---")

    values = [2, 0, 2, 1, 1, 0]

    print(f"Original array: {values}")

    valid = dutch_national_flag(values)

    print(
        f"Sorted array: {values} "
        f"{'[PASSED]' if valid else '[FAILED]'}"
    )

    print("\n--- TEST CASES ---")

    test_sort(
        [2, 0, 1, 2, 1, 0],
        [0, 0, 1, 1, 2, 2],
        "Mixed values"
    )

    test_sort(
        [0, 1, 2],
        [0, 1, 2],
        "Already sorted"
    )

    test_sort(
        [2, 1, 0],
        [0, 1, 2],
        "Reverse order"
    )

    test_sort(
        [0, 0, 0],
        [0, 0, 0],
        "All zeros"
    )

    test_sort(
        [1, 1, 1],
        [1, 1, 1],
        "All ones"
    )

    test_sort(
        [2, 2, 2],
        [2, 2, 2],
        "All twos"
    )

    test_sort(
        [2, 2, 1, 0, 1, 0],
        [0, 0, 1, 1, 2, 2],
        "Repeated values"
    )

    test_sort(
        [2],
        [2],
        "Single element"
    )

    test_sort(
        [],
        [],
        "Empty array"
    )

    print("\n--- INVALID INPUT ---")

    invalid = [2, 0, 3, 1]
    original = invalid.copy()

    accepted = dutch_national_flag(invalid)
    unchanged = invalid == original

    passed = not accepted and unchanged

    print(
        f"Invalid value: "
        f"{'Rejected and unchanged' if passed else 'FAILED'}"
        f" {'[PASSED]' if passed else '[FAILED]'}"
    )


if __name__ == "__main__":
    main()