from typing import List

BASE = 256
MOD = 1_000_000_007

def rabin_karp_search(text: str, pattern: str) -> List[int]:
    """
    Find every occurrence of pattern inside text using Rabin-Karp.

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

    # Calculate BASE^(m - 1) modulo MOD.
    highest_power = pow(BASE, m - 1, MOD)

    pattern_hash = 0
    window_hash = 0

    # Calculate initial hashes.
    for i in range(m):
        pattern_hash = (
            pattern_hash * BASE + ord(pattern[i])
        ) % MOD

        window_hash = (
            window_hash * BASE + ord(text[i])
        ) % MOD

    # Slide the window across the text.
    for i in range(n - m + 1):

        # A matching hash is only a candidate.
        # Verify the actual characters to handle collisions.
        if pattern_hash == window_hash:
            if text[i:i + m] == pattern:
                positions.append(i)

        # Update the hash for the next window.
        if i < n - m:
            outgoing = (
                ord(text[i]) * highest_power
            ) % MOD

            window_hash = (
                window_hash - outgoing
            ) % MOD

            window_hash = (
                window_hash * BASE + ord(text[i + m])
            ) % MOD

    return positions


def run_test(
    text: str,
    pattern: str,
    expected: List[int],
    test_name: str
) -> None:
    result = rabin_karp_search(text, pattern)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("=== RABIN-KARP STRING MATCHING ===")

    print("\n--- BASIC SEARCH ---")

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
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Single match"
    )

    run_test(
        "HELLO WORLD",
        "WORLD",
        [6],
        "Match near end"
    )

    run_test(
        "AAAAA",
        "AA",
        [0, 1, 2, 3],
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
