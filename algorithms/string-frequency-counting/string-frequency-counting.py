from typing import List, Optional

def character_frequency(text: str) -> Optional[List[int]]:
    """
    Counts lowercase English letters.

    Returns a list of 26 frequency counters.
    Returns None if the input contains unsupported characters.
    """

    frequency = [0] * 26

    for character in text:
        if character < "a" or character > "z":
            return None

        index = ord(character) - ord("a")
        frequency[index] += 1

    return frequency


def print_frequency(frequency: List[int]) -> None:
    for index, count in enumerate(frequency):
        if count > 0:
            character = chr(ord("a") + index)
            print(f"{character} -> {count}")


def test_frequency(
    text: str,
    expected: List[int],
    label: str
) -> None:
    result = character_frequency(text)

    passed = result == expected

    print(
        f"{label}: "
        f"{'[PASSED]' if passed else '[FAILED]'}"
    )


def main() -> None:
    print("==== CHARACTER FREQUENCY COUNTING ====")

    print("\n--- BASIC EXAMPLE ---")

    text = "banana"

    print(f"Input: {text}")

    frequency = character_frequency(text)

    if frequency is not None:
        print("Character frequencies:")
        print_frequency(frequency)

    print("\n--- TEST CASES ---")

    banana_expected = [0] * 26
    banana_expected[0] = 3
    banana_expected[1] = 1
    banana_expected[13] = 2

    test_frequency(
        "banana",
        banana_expected,
        "Repeated characters"
    )

    test_frequency(
        "abcdefghijklmnopqrstuvwxyz",
        [1] * 26,
        "All lowercase letters"
    )

    single_expected = [0] * 26
    single_expected[25] = 1

    test_frequency(
        "z",
        single_expected,
        "Single character"
    )

    test_frequency(
        "",
        [0] * 26,
        "Empty string"
    )

    repeated_expected = [0] * 26
    repeated_expected[2] = 5

    test_frequency(
        "ccccc",
        repeated_expected,
        "All characters identical"
    )

    print("\n--- INVALID INPUT ---")

    invalid_uppercase = character_frequency("Banana")

    print(
        f"Uppercase character: "
        f"{'Rejected [PASSED]' if invalid_uppercase is None else 'Accepted [FAILED]'}"
    )

    invalid_numeric = character_frequency("hello123")

    print(
        f"Numeric characters: "
        f"{'Rejected [PASSED]' if invalid_numeric is None else 'Accepted [FAILED]'}"
    )


if __name__ == "__main__":
    main()