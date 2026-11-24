def longest_common_subsequence(
    first: str,
    second: str
) -> str:
    """
    Return one longest common subsequence of two strings.
    """

    n = len(first)
    m = len(second)

    # Create an (n + 1) x (m + 1) DP table.
    dp = [
        [0] * (m + 1)
        for _ in range(n + 1)
    ]

    # Fill the DP table.
    for i in range(1, n + 1):
        for j in range(1, m + 1):

            if first[i - 1] == second[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1

            else:
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                )

    # Reconstruct the subsequence.
    result = []

    i = n
    j = m

    while i > 0 and j > 0:

        if first[i - 1] == second[j - 1]:
            result.append(first[i - 1])

            i -= 1
            j -= 1

        elif dp[i - 1][j] >= dp[i][j - 1]:
            i -= 1

        else:
            j -= 1

    # Reverse because reconstruction happens backwards.
    result.reverse()

    return "".join(result)


def run_test(
    first: str,
    second: str,
    expected: str,
    test_name: str
) -> None:
    result = longest_common_subsequence(first, second)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"(length {len(result)}) "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("==== LONGEST COMMON SUBSEQUENCE ====")

    print("\n--- BASIC EXAMPLES ---")

    run_test("ABC", "AC", "AC", "Simple example")

    run_test(
        "AGGTAB",
        "GXTXAYB",
        "GTAB",
        "Classic example"
    )

    run_test(
        "ABCDEF",
        "ACE",
        "ACE",
        "Characters with gaps"
    )

    print("\n--- ADDITIONAL CASES ---")

    run_test("ABCD", "AEBD", "ABD", "Different lengths")
    run_test("HELLO", "WORLD", "L", "Single common character")
    run_test("ABC", "ABC", "ABC", "Identical strings")
    run_test("AAAA", "AA", "AA", "Repeated characters")
    run_test("ABC", "DEF", "", "No common characters")

    print("\n--- EDGE CASES ---")

    run_test("", "", "", "Both empty")
    run_test("ABC", "", "", "Second string empty")
    run_test("", "ABC", "", "First string empty")


if __name__ == "__main__":
    main()
