from typing import List

def naive_string_search(text: str, pattern: str) -> List[int]:
    """
    Find every occurrence of pattern inside text.

    Returns a list of zero-based starting indices.
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

    # Try every possible starting position.
    for i in range(n - m + 1):
        j = 0

        # Compare characters one by one.
        while j < m and text[i + j] == pattern[j]:
            j += 1

        # The entire pattern matched.
        if j == m:
            positions.append(i)

    return positions


def run_test(
    text: str,
    pattern: str,
    expected: List[int],
    test_name: str
) -> None:
    result = naive_string_search(text, pattern)

    status = "PASSED" if result == expected else "FAILED"

    print(f"{test_name}: {result} [{status}]")

    if result != expected:
        print(f"  Expected: {expected}")


def main() -> None:
    print("=== NAIVE STRING MATCHING ===")

    print("\n--- BASIC SEARCH ---")

    run_test(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    )

    run_test(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Single match"
    )

    run_test(
        "ABCDEF",
        "XYZ",
        [],
        "No match"
    )

    run_test(
        "HELLO WORLD",
        "WORLD",
        [6],
        "Match near end"
    )

    print("\n--- EDGE CASES ---")

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

    print("\n--- REPEATED CHARACTERS ---")

    run_test(
        "AAAAA",
        "AA",
        [0, 1, 2, 3],
        "Repeated overlapping matches"
    )

    run_test(
        "AAAA",
        "AA",
        [0, 1, 2],
        "Consecutive matches"
    )


if __name__ == "__main__":
    main()