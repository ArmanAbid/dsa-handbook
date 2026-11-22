from typing import Dict, List

def build_shift_table(pattern: str) -> Dict[str, int]:
    """
    Build the shift table.

    Characters absent from the table use the pattern length
    as their default shift.
    """

    m = len(pattern)

    shift: Dict[str, int] = {}

    # Exclude the final character.
    for i in range(m - 1):
        shift[pattern[i]] = m - 1 - i

    return shift


def boyer_moore_horspool_search(
    text: str,
    pattern: str
) -> List[int]:
    """
    Find every occurrence of pattern inside text.

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

    # Preprocess the pattern.
    shift = build_shift_table(pattern)

    start = 0

    while start <= n - m:
        j = m - 1

        # Compare from right to left.
        while j >= 0 and pattern[j] == text[start + j]:
            j -= 1

        # Entire pattern matched.
        if j < 0:
            positions.append(start)

        # Shift using the last character of the text window.
        last_char = text[start + m - 1]

        start += shift.get(last_char, m)

    return positions


def run_test(
    text: str,
    pattern: str,
    expected: List[int],
    test_name: str
) -> None:
    result = boyer_moore_horspool_search(text, pattern)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("==== BOYER-MOORE-HORSPOOL ====")

    print("\n--- SHIFT TABLE ---")

    print(f"Pattern: ABC")
    print(f"Character shifts: {build_shift_table('ABC')}")

    print("\n--- BASIC SEARCH ---")

    run_test(
        "ABAAABCD",
        "ABC",
        [4],
        "Shift-based search"
    )

    run_test(
        "HERE IS A SIMPLE EXAMPLE",
        "EXAMPLE",
        [17],
        "Classic example"
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
        "mississippi",
        "issi",
        [1, 4],
        "Repeated characters"
    )

    run_test(
        "AAAAA",
        "AAA",
        [0, 1, 2],
        "Repeated overlapping matches"
    )

    print("\n--- EDGE CASES ---")

    run_test("ABCDEF", "XYZ", [], "No match")
    run_test("ABC", "ABCDE", [], "Pattern longer than text")
    run_test("ABC", "", [0, 1, 2, 3], "Empty pattern")
    run_test("", "", [0], "Both empty")
    run_test("", "A", [], "Empty text")
    run_test("aaaa", "a", [0, 1, 2, 3], "Single-character pattern")


if __name__ == "__main__":
    main()
