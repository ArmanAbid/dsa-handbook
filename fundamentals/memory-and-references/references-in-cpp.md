# References in C++

A reference is an alias of an object in C++. A normal reference is not like a pointer, it must be assigned at the time of declaration and cannot be reassigned to another object.

## 1. Creating a Reference

```cpp
int value = 10;
int& ref = value;

ref = 20;

// value is now 20
```

Both `ref` and `value` refer to the same object, so any change to one will affect the other.

## 2. Passing by Reference

```cpp
void increment(int& n) {
    n++;
}

int main() {
    int value = 5;
    increment(value);

    // value is now 6
}
```

This prevents the integer from being copied and enables the function to change the original.

## 3. Passing by Const Reference

When you want to avoid copying a potentially large object but you don't want to allow modification through the reference, use a const reference.

```cpp
void printValues(const vector<int>& values) {
    for (int value : values) {
        cout << value << ' ';
    }
}
```

The function is able to read the vector but not change its elements using `values`.

## 4. Reference vs Pointer

| Feature           | Reference                       | Pointer                                     |
|-------------------|---------------------------------|---------------------------------------------|
| Declaration       | `int& ref = value;`             | `int* ptr = &value;`                        |
| Can be null?      | A valid reference cannot be null| Yes                                         |
| Can be redirected?| No                              | Yes                                         |
| Access value      | Use the reference name          | Dereference with `*`                        |
| Common use        | Aliases and function parameters | Optional access and pointer-based structures|

## 5. References and Lifetime

The reference should not outlive the object it refers to. Returning a reference to a local variable is a common error.

```cpp
int& badFunction() {
    int local = 5;
    return local; // Invalid: reference dangles after return
}
```

Return by value or refer to an object whose lifetime is guaranteed to continue when appropriate.

## Practice

- Use reference parameters to swap two integers.
- Pass a vector by const reference.
- Explain why returning a reference to a local variable is unsafe.
