from typing import List, Optional

# READ

def get_at(arr: List[int], index: int) -> Optional[int]:
    if not isinstance(index, int) or index < 0 or index >= len(arr):
        return None

    return arr[index]


def get_first(arr: List[int]) -> Optional[int]:
    if not arr:
        return None

    return arr[0]


def get_last(arr: List[int]) -> Optional[int]:
    if not arr:
        return None

    return arr[-1]


def print_array(arr: List[int]) -> None:
    for value in arr:
        print(value, end=" ")

    print()



# UPDATE

def set_at(arr: List[int], index: int, value: int) -> bool:
    if not isinstance(index, int) or index < 0 or index >= len(arr):
        return False

    arr[index] = value
    return True



# INSERT

def append(arr: List[int], value: int) -> None:
    arr.append(value)


def prepend(arr: List[int], value: int) -> None:
    arr.insert(0, value)


# index == len(arr) inserts at the end.
def insert_at(arr: List[int], index: int, value: int) -> bool:
    if not isinstance(index, int) or index < 0 or index > len(arr):
        return False

    arr.insert(index, value)
    return True



# DELETE

def remove_at(arr: List[int], index: int) -> Optional[int]:
    if not isinstance(index, int) or index < 0 or index >= len(arr):
        return None

    return arr.pop(index)


def pop_front(arr: List[int]) -> Optional[int]:
    if not arr:
        return None

    return arr.pop(0)


def pop_back(arr: List[int]) -> Optional[int]:
    if not arr:
        return None

    return arr.pop()


def clear_array(arr: List[int]) -> None:
    arr.clear()



# SIZE AND RESIZING

def size_of(arr: List[int]) -> int:
    return len(arr)


def is_empty(arr: List[int]) -> bool:
    return len(arr) == 0


def resize_array(
    arr: List[int],
    new_size: int,
    fill_value: int = 0
) -> bool:
    if not isinstance(new_size, int) or new_size < 0:
        return False

    if new_size < len(arr):
        del arr[new_size:]
    else:
        arr.extend([fill_value] * (new_size - len(arr)))

    return True



# DEMONSTRATION

def main() -> None:

    # Create an array using native Python syntax.
    arr = [10, 20, 30, 40, 50]

    print("Initial array:", end=" ")
    print_array(arr)

    # READ
    print("Element at index 2:", get_at(arr, 2))
    print("First element:", get_first(arr))
    print("Last element:", get_last(arr))

    # UPDATE
    set_at(arr, 2, 35)

    # INSERT
    insert_at(arr, 2, 25)
    append(arr, 60)
    prepend(arr, 5)

    print("After updates and insertions:", end=" ")
    print_array(arr)

    # DELETE
    print("Removed at index 1:", remove_at(arr, 1))
    print("Removed first element:", pop_front(arr))
    print("Removed last element:", pop_back(arr))

    print("Current array:", end=" ")
    print_array(arr)

    # SIZE AND RESIZING
    print("Size:", size_of(arr))
    print("Empty:", is_empty(arr))

    resize_array(arr, 6, -1)

    print("After resizing:", end=" ")
    print_array(arr)

    # CLEAR
    clear_array(arr)

    print("Size after clearing:", size_of(arr))
    print("Empty after clearing:", is_empty(arr))


if __name__ == "__main__":
    main()
