def levenshtein_distance(first: str, second: str) -> int:
    """
    Calculate the minimum number of insertions, deletions,
    and substitutions needed to transform first into second.

    Uses two DP rows to optimize memory.
    """

    # Use the shorter string as the columns.
    if len(second) > len(first):
        first, second = second, first

    n = len(first)
    m = len(second)

    # Initial row: converting an empty string into each prefix.
    previous = list(range(m + 1))

    for i in range(1, n + 1):
        # Initial column: deleting i characters.
        current = [i] + [0] * m

        for j in range(1, m + 1):

            if first[i - 1] == second[j - 1]:
                # Characters match: no additional edit.
                current[j] = previous[j - 1]

            else:
                # Three possible operations.
                deletion = previous[j]
                insertion = current[j - 1]
                substitution = previous[j - 1]

                current[j] = 1 + min(
                    deletion,
                    insertion,
                    substitution
                )

        # Move to the next row.
        previous = current

    return previous[m]


def run_test(
    first: str,
    second: str,
    expected: int,
    test_name: str
) -> None:
    result = levenshtein_distance(first, second)

    passed = result == expected

    print(
        f"{test_name}: {result} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f"  Expected: {expected}")


def main() -> None:
    print("==== LEVENSHTEIN DISTANCE ====")

    print("\n--- BASIC EXAMPLES ---")

    run_test("kitten", "sitting", 3, "Kitten to sitting")
    run_test("saturday", "sunday", 3, "Saturday to Sunday")
    run_test("flaw", "lawn", 2, "Flaw to lawn")
    run_test("intention", "execution", 5, "Classic example")

    print("\n--- EDIT OPERATIONS ---")

    run_test("cat", "cut", 1, "Substitution")
    run_test("cat", "cart", 1, "Insertion")
    run_test("cart", "cat", 1, "Deletion")

    print("\n--- ADDITIONAL CASES ---")

    run_test("Cat", "cat", 1, "Case-sensitive comparison")
    run_test("book", "back", 2, "Multiple substitutions")
    run_test("algorithm", "algorithm", 0, "Identical strings")
    run_test("ab", "ba", 2, "Two substitutions")
    run_test("form", "from", 2, "Transposition is two edits")

    print("\n--- EDGE CASES ---")

    run_test("", "", 0, "Both empty")
    run_test("", "abc", 3, "First string empty")
    run_test("abc", "", 3, "Second string empty")


if __name__ == "__main__":
    main()
