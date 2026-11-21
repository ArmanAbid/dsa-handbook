from typing import List, Tuple

def odd_radii(text: str) -> List[int]:
    """Calculate odd-length palindrome radii."""

    n = len(text)
    odd = [0] * n

    left = 0
    right = -1

    for i in range(n):

        # Reuse information from the current palindrome.
        if i > right:
            radius = 1
        else:
            mirror = left + right - i
            remaining = right - i + 1

            radius = min(odd[mirror], remaining)

        # Expand around the current character.
        while (
            i - radius >= 0
            and i + radius < n
            and text[i - radius] == text[i + radius]
        ):
            radius += 1

        odd[i] = radius

        # Update the rightmost palindrome.
        if i + radius - 1 > right:
            left = i - radius + 1
            right = i + radius - 1

    return odd


def even_radii(text: str) -> List[int]:
    """Calculate even-length palindrome radii."""

    n = len(text)
    even = [0] * n

    left = 0
    right = -1

    for i in range(n):

        # Reuse information from the current palindrome.
        if i > right:
            radius = 0
        else:
            mirror = left + right - i + 1
            remaining = right - i + 1

            radius = min(even[mirror], remaining)

        # Expand around the gap before the current character.
        while (
            i - radius - 1 >= 0
            and i + radius < n
            and text[i - radius - 1] == text[i + radius]
        ):
            radius += 1

        even[i] = radius

        # Update the rightmost palindrome.
        if i + radius - 1 > right:
            left = i - radius
            right = i + radius - 1

    return even


def manacher(
    text: str
) -> Tuple[List[int], List[int], int, int, str]:
    """
    Calculate both radius arrays and find the longest palindrome.

    Returns:
        odd radii,
        even radii,
        starting index,
        palindrome length,
        longest palindrome.
    """

    odd = odd_radii(text)
    even = even_radii(text)

    best_start = 0
    best_length = 0

    # Check odd-length palindromes.
    for i in range(len(text)):
        length = 2 * odd[i] - 1
        start = i - odd[i] + 1

        if (
            length > best_length
            or (length == best_length and start < best_start)
        ):
            best_start = start
            best_length = length

    # Check even-length palindromes.
    for i in range(len(text)):
        length = 2 * even[i]
        start = i - even[i]

        if (
            length > best_length
            or (length == best_length and start < best_start)
        ):
            best_start = start
            best_length = length

    longest = text[best_start:best_start + best_length]

    return odd, even, best_start, best_length, longest


def run_radius_test(
    text: str,
    expected_odd: List[int],
    expected_even: List[int],
    test_name: str
) -> None:
    odd = odd_radii(text)
    even = even_radii(text)

    passed = odd == expected_odd and even == expected_even

    print(
        f"{test_name}: "
        f"Odd = {odd}, Even = {even} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )


def run_test(
    text: str,
    expected_longest: str,
    expected_start: int,
    expected_length: int,
    test_name: str
) -> None:
    _, _, start, length, longest = manacher(text)

    passed = (
        longest == expected_longest
        and start == expected_start
        and length == expected_length
    )

    print(
        f'{test_name}: Longest = "{longest}", '
        f"Start = {start}, Length = {length} "
        f"[{'PASSED' if passed else 'FAILED'}]"
    )

    if not passed:
        print(f'  Expected: "{expected_longest}" at {expected_start}')


def main() -> None:
    print("==== MANACHER'S ALGORITHM ====")

    print("\n--- RADIUS ARRAYS ---")

    run_radius_test(
        "abacaba",
        [1, 2, 1, 4, 1, 2, 1],
        [0, 0, 0, 0, 0, 0, 0],
        "Odd palindrome radii"
    )

    run_radius_test(
        "abba",
        [1, 1, 1, 1],
        [0, 0, 2, 0],
        "Even palindrome radii"
    )

    print("\n--- LONGEST PALINDROMES ---")

    run_test("babad", "bab", 0, 3, "Odd-length palindrome")
    run_test("cbbd", "bb", 1, 2, "Even-length palindrome")
    run_test("abba", "abba", 0, 4, "Entire string is a palindrome")
    run_test("aaaaa", "aaaaa", 0, 5, "Repeated characters")
    run_test("racecar", "racecar", 0, 7, "Classic palindrome")
    run_test("abc", "a", 0, 1, "No palindrome longer than one")

    run_test(
        "abacdfgdcaba",
        "aba",
        0,
        3,
        "Multiple longest palindromes"
    )

    print("\n--- EDGE CASES ---")

    run_test("", "", 0, 0, "Empty string")
    run_test("x", "x", 0, 1, "Single character")
    run_test("aabbaa", "aabbaa", 0, 6, "Long even palindrome")


if __name__ == "__main__":
    main()
