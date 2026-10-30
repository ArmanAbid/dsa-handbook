# Signed vs Unsigned Integers

Negative integers and nonnegative integers are represented by signed integers. Unsigned integers are used to store values that are not negative.

## 1. Signed Integers

The range of a typical signed 32-bit integer is:

`-2^31` to `2^31 - 1`

That is:

`-2,147,483,648` to `2,147,483,647`

## 2. Unsigned Integers

The range of an unsigned 32-bit integer is:

`0` to `2^32 - 1`

Using the same number of bits, unsigned integers can represent larger positive values, but they cannot represent negative values.

## 3. A Common C++ Bug

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = -1;
    unsigned int b = 1;

    cout << (a < b);
}
```

On common C++ implementations, the comparison converts `a` to an unsigned value, so the comparison is false.

Signed and unsigned types can result in unexpected comparisons.

## 4. Unsigned Underflow

```cpp
unsigned int x = 0;
x--;
```

Unsigned arithmetic wraps around modulo one more than the type's maximum value. For a 32-bit unsigned integer, decrementing zero produces `4,294,967,295`.

Signed overflow, in contrast, is undefined behavior in C++.

## 5. Looping Backward

This loop is dangerous:

```cpp
for (size_t i = values.size() - 1; i >= 0; i--) {
    // ...
}
```

`size_t` is unsigned, so `i >= 0` is always true. Decrementing zero wraps around.

A safer way to write a nonempty vector is:

```cpp
for (size_t i = values.size(); i > 0; i--) {
    size_t index = i - 1;
    // Use values[index].
}
```

This also works for an empty vector, since the loop body is never executed.

## Best Practice

- Use signed types when negative values are meaningful.
- Use unsigned types when their semantics are appropriate, not merely because values are nonnegative.
- Be careful when comparing signed and unsigned values.
- Be sure to pay attention to container sizes and loop boundaries.
