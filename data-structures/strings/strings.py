from typing import Optional


# READ

def get_at(text: str, index: int) -> Optional[str]:
    if not isinstance(index, int) or index < 0 or index >= len(text):
        return None

    return text[index]


def get_first(text: str) -> Optional[str]:
    if not text:
        return None

    return text[0]


def get_last(text: str) -> Optional[str]:
    if not text:
        return None

    return text[-1]


def print_string(text: str) -> None:
    print(text)


# UPDATE

def set_at(
    text: str,
    index: int,
    new_char: str
) -> Optional[str]:
    """
    Return a new string with one character replaced.
    Return None for an invalid index or replacement.
    """
    if (
        not isinstance(index, int)
        or index < 0
        or index >= len(text)
        or len(new_char) != 1
    ):
        return None

    return text[:index] + new_char + text[index + 1:]


# INSERT

def append_text(text: str, value: str) -> str:
    return text + value


def prepend_text(text: str, value: str) -> str:
    return value + text


# index == len(text) inserts at the end.
def insert_at(
    text: str,
    index: int,
    value: str
) -> Optional[str]:
    if (
        not isinstance(index, int)
        or index < 0
        or index > len(text)
    ):
        return None

    return text[:index] + value + text[index:]


# DELETE

def remove_at(text: str, index: int) -> Optional[str]:
    """Return a new string without the character at index."""
    if (
        not isinstance(index, int)
        or index < 0
        or index >= len(text)
    ):
        return None

    return text[:index] + text[index + 1:]


def remove_first(text: str) -> Optional[str]:
    if not text:
        return None

    return text[1:]


def remove_last(text: str) -> Optional[str]:
    if not text:
        return None

    return text[:-1]


def clear_string(text: str) -> str:
    return ""


# SIZE AND BASIC PROPERTIES

def size_of(text: str) -> int:
    return len(text)


def is_empty(text: str) -> bool:
    return len(text) == 0


# OTHER BASIC STRING OPERATIONS

# Extract the range [start, end).
# Start is included; end is excluded.
def substring_range(
    text: str,
    start: int,
    end: int
) -> Optional[str]:
    if (
        not isinstance(start, int)
        or not isinstance(end, int)
        or start < 0
        or end < start
        or end > len(text)
    ):
        return None

    return text[start:end]


def concatenate(first: str, second: str) -> str:
    return first + second


def strings_equal(first: str, second: str) -> bool:
    return first == second


# DEMONSTRATION

def main() -> None:

    # Initialize a string using native Python syntax.
    text = "Hello"

    print("==== PYTHON STRING ====")

    print("Original:", text)

    # READ
    print("Character at index 1:", get_at(text, 1))
    print("First character:", get_first(text))
    print("Last character:", get_last(text))

    # UPDATE
    updated = set_at(text, 0, "Y")

    if updated is not None:
        text = updated

    print("After updating:", text)

    # INSERT
    updated = insert_at(text, 5, "!")

    if updated is not None:
        text = updated

    text = append_text(text, " World")
    text = prepend_text(text, "Hi, ")

    print("After inserting:", text)

    # DELETE
    updated = remove_at(text, 2)

    if updated is not None:
        text = updated

    updated = remove_first(text)

    if updated is not None:
        text = updated

    updated = remove_last(text)

    if updated is not None:
        text = updated

    print("After deleting:", text)

    # SIZE AND PROPERTIES
    print("Length:", size_of(text))
    print("Empty:", is_empty(text))

    # SUBSTRING
    print("Substring [0, 2):", substring_range(text, 0, 2))

    # CONCATENATION
    combined = concatenate(text, "!!!")

    print("Concatenated:", combined)

    # COMPARISON
    print("Strings equal:", strings_equal(text, combined))

    # CLEAR
    text = clear_string(text)

    print('After clearing:', f'"{text}"')
    print("Empty after clearing:", is_empty(text))


if __name__ == "__main__":
    main()
