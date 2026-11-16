from typing import List, Optional, Sequence, Tuple

Interval = Tuple[int, int]

def merge_intervals(
    intervals: Sequence[Interval]
) -> Optional[List[Interval]]:
    """
    Merges overlapping intervals.

    Returns:
        A list of merged intervals.

    Returns None if an interval has start > end.
    """

    # Validate before processing.
    for start, end in intervals:
        if start > end:
            return None

    # Sort by starting point, then ending point.
    sorted_intervals = sorted(
        intervals,
        key=lambda interval: (interval[0], interval[1])
    )

    merged: List[Interval] = []

    for start, end in sorted_intervals:
        if not merged or start > merged[-1][1]:
            # No overlap: add a new interval.
            merged.append((start, end))
        else:
            # Overlap: extend the previous interval.
            previous_start, previous_end = merged[-1]

            merged[-1] = (
                previous_start,
                max(previous_end, end)
            )

    return merged


def test_merge(
    intervals: Sequence[Interval],
    expected: List[Interval],
    label: str
) -> None:
    result = merge_intervals(intervals)

    passed = result == expected

    print(
        f"{label}: {result} "
        f"{'[PASSED]' if passed else '[FAILED]'}"
    )


def main() -> None:
    print("=== MERGE INTERVALS ===")

    print("\n--- BASIC EXAMPLE ---")

    intervals = [
        (1, 3),
        (2, 6),
        (8, 10),
        (15, 18)
    ]

    print(f"Original intervals: {intervals}")

    merged = merge_intervals(intervals)

    print(f"Merged intervals: {merged}")

    print("\n--- TEST CASES ---")

    test_merge(
        [(8, 10), (1, 3), (15, 18), (2, 6)],
        [(1, 6), (8, 10), (15, 18)],
        "Unsorted intervals"
    )

    test_merge(
        [(1, 4), (4, 5)],
        [(1, 5)],
        "Touching intervals"
    )

    test_merge(
        [(1, 2), (4, 5), (7, 8)],
        [(1, 2), (4, 5), (7, 8)],
        "Non-overlapping intervals"
    )

    test_merge(
        [(1, 10), (2, 3), (4, 8)],
        [(1, 10)],
        "Nested intervals"
    )

    test_merge(
        [(1, 4), (1, 2), (1, 5)],
        [(1, 5)],
        "Same starting points"
    )

    test_merge(
        [(5, 7)],
        [(5, 7)],
        "Single interval"
    )

    test_merge(
        [],
        [],
        "Empty input"
    )

    print("\n--- INVALID INPUT ---")

    invalid = [(1, 3), (5, 2)]
    result = merge_intervals(invalid)

    passed = result is None

    print(
        f"Invalid interval: "
        f"{'Rejected' if passed else 'Accepted'} "
        f"{'[PASSED]' if passed else '[FAILED]'}"
    )


if __name__ == "__main__":
    main()