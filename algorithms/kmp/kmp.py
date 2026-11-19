from typing import List

def build_lps(pattern: str) -> List[int]:
    """
    Build the Longest Proper Prefix which is also a Suffix array.
    """

    m = len(pattern)

    lps = [0] * m

    length = 0
    i = 1

    while i < m:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1

        elif length != 0:
            length = lps[length - 1]

        else:
            lps[i] = 0
            i += 1

    return lps


def kmp_search(text: str, pattern: str) -> List[int]:
    """
    Find all occurrences of pattern inside text using KMP.

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
    lps = build_lps(pattern)

    i = 0  # Text pointer
    j = 0  # Pattern pointer

    while i < n:
        if text[i] == pattern[j]:
            i += 1
            j += 1

            # Entire pattern matched.
            if j == m:
                positions.append(i - j)

                # Continue searching for overlapping matches.
                j = lps[j - 1]

        elif j != 0:
            # Reuse previously matched prefix information.
            j = lps[j - 1]

        else:
            i += 1

    return positions


def run_test(
    text: str,
    pattern: str,
    expected: List[int],
    test_name: str
) -> None:
    result = kmp_search(text, pattern)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("=== KMP STRING MATCHING ===")

    print("\n--- LPS CONSTRUCTION ---")

    print("Pattern: ABABC")
    print(f"LPS: {build_lps('ABABC')}")

    print("\n--- BASIC SEARCH ---")

    run_test(
        "ABABABC",
        "ABABC",
        [2],
        "LPS fallback example"
    )

    run_test(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Standard KMP example"
    )

    run_test(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    )

    run_test(
        "ABCABCABC",
        "ABC",
        [0, 3, 6],
        "Multiple matches"
    )

    run_test(
        "AAAAAAAAAB",
        "AAAAB",
        [5],
        "Repeated prefix characters"
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
