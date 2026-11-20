from typing import List

def build_z_array(sequence: List[int]) -> List[int]:
    """
    Build the Z array for an integer sequence.

    z[i] is the length of the longest substring starting at i
    that matches a prefix of the sequence.
    """

    n = len(sequence)

    z = [0] * n

    left = 0
    right = 0

    for i in range(1, n):

        # Reuse information from the current Z box.
        if i <= right:
            mirror = i - left
            remaining = right - i + 1

            z[i] = min(z[mirror], remaining)

        # Extend the match beyond the current Z box.
        while (
            i + z[i] < n
            and sequence[z[i]] == sequence[i + z[i]]
        ):
            z[i] += 1

        # Update the Z box if this match extends farther.
        if z[i] > 0 and i + z[i] - 1 > right:
            left = i
            right = i + z[i] - 1

    return z


def z_search(text: str, pattern: str) -> List[int]:
    """
    Find every occurrence of pattern inside text using Z Algorithm.

    Returns zero-based starting indices.
    """

    positions: List[int] = []

    n = len(text)
    m = len(pattern)

    # An empty pattern matches every boundary position.
    if m == 0:
        return list(range(n + 1))

    # Pattern cannot fit inside the text.
    if m > n:
        return positions

    # Build: pattern + separator + text.
    # -1 cannot collide with Unicode character values.
    combined = (
        [ord(char) for char in pattern]
        + [-1]
        + [ord(char) for char in text]
    )

    # Calculate the Z array.
    z = build_z_array(combined)

    # Find positions where the entire pattern matches.
    for i in range(m + 1, len(combined)):
        if z[i] >= m:
            positions.append(i - m - 1)

    return positions


def run_test(
    text: str,
    pattern: str,
    expected: List[int],
    test_name: str
) -> None:
    result = z_search(text, pattern)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("==== Z ALGORITHM ====")

    print("\n--- Z ARRAY CONSTRUCTION ---")

    sample = [ord(char) for char in "ABABAC"]

    print("String: ABABAC")
    print(f"Z array: {build_z_array(sample)}")

    print("\n--- BASIC SEARCH ---")

    run_test(
        "ABABABC",
        "ABABC",
        [2],
        "LPS-style prefix reuse example"
    )

    run_test(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    )

    run_test(
        "BANANA",
        "ANA",
        [1, 3],
        "Multiple matches"
    )

    run_test(
        "ABCABCABC",
        "ABC",
        [0, 3, 6],
        "Repeated pattern"
    )

    run_test(
        "mississippi",
        "issi",
        [1, 4],
        "Pattern with repeated characters"
    )

    run_test(
        "AAAAA",
        "AAA",
        [0, 1, 2],
        "Repeated overlapping matches"
    )

    print("\n--- EDGE CASES ---")

    run_test(
        "ABCDEF",
        "XYZ",
        [],
        "No match"
    )

    run_test(
        "ABC",
        "ABCDE",
        [],
        "Pattern longer than text"
    )

    run_test(
        "ABC",
        "",
        [0, 1, 2, 3],
        "Empty pattern"
    )

    run_test(
        "",
        "",
        [0],
        "Both empty"
    )

    run_test(
        "",
        "A",
        [],
        "Empty text"
    )


if __name__ == "__main__":
    main()
