# Pointers

A pointer is a variable that contains a memory address. Pointers are basic concepts in C and C++ and they can be used to understand linked lists, trees and dynamic memory.

## 1. Declaring a Pointer

```cpp
int x = 10;
int* ptr = &x;
```

- `x` stores the integer `10`.
- `&x` obtains the address of `x`.
- That address is stored in the variable `ptr`.
- The expression `*ptr` returns the value of the object pointed to by `ptr`.

```cpp
cout << *ptr; // 10
```

## 2. Modifying a Value Through a Pointer

```cpp
int x = 10;
int* ptr = &x;

*ptr = 25;

// x is now 25
```

The pointer is used to access the original variable.

## 3. Null Pointers

A null pointer is not a pointer to a valid object.

```cpp
int* ptr = nullptr;
```

Don't dereference a null pointer:

```cpp
// *ptr = 10; // Invalid: undefined behavior
```

Test a pointer for validity before using it, but be aware that a non-null pointer may be invalid.

## 4. Pointers and Dynamic Memory

```cpp
int* ptr = new int(42);

cout << *ptr;

delete ptr;
ptr = nullptr;
```

After `delete`, the allocated object no longer exists. It is a good idea to set the pointer to `nullptr` to prevent the accidental re-use of that pointer, but it does not change other aliases.

## 5. Dangling Pointers

A dangling pointer is a pointer that does not point to an object anymore or whose memory has been released.

It is not safe to dereference and may cause undefined behavior.

## 6. Pointers in Linked Lists

Each node in a linked-list has a value and a pointer to the next node:

```cpp
struct Node {
    int value;
    Node* next;
};
```

The `next` pointer is used to link nodes together.

## Best Practice

Prefer smart pointers such as `std::unique_ptr` when you need dynamic ownership in modern C++. When using non-owning access or when learning about pointer-based structures, use raw pointers.
