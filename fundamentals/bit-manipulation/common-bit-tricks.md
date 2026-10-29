# Common Bit Tricks

These patterns appear frequently in coding interviews and competitive programming.

## 1. Determine if a number is odd

```cpp
bool isOdd = (n & 1) != 0;
```

The bottom bit is `1` if the integer is odd and nonnegative, and `0` if the integer is even.

## 2. Check Whether a Number Is a Power of Two

There is exactly one set bit in a positive power of 2.

Examples:

```text
1  = 0001
2  = 0010
4  = 0100
8  = 1000
```

For a positive integer `n`:

```cpp
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

When subtracting `1`, the lowest set bit is cleared and the bits below it are changed. There are no other bits set in a power of two after the operation.

## 3. Remove the lowest set bit

```cpp
n = n & (n - 1);
```

Example:

```text
n     = 101100
n - 1 = 101011
AND   = 101000
```

The lowest set bit is removed.

## 4. Isolate the Lowest Set Bit

For an unsigned integer:

```cpp
unsigned int lowest = n & -n;
```

This isolates the lowest set bit under the usual unsigned integer arithmetic rules.

For example, if `n = 12` (`1100`), the result is `4` (`0100`).

## 5. Multiply or divide by powers of two

A left shift of `k` for nonnegative integers is equivalent to multiplying by `2^k`, if it is valid and representable.

A right shift by `k` can divide by `2^k`, discarding lower bits.

Do not use shifts blindly when overflow or signed values are involved.

## Practice

- Check whether a number is a power of two.
- Remove the lowest set bit repeatedly until the number becomes zero.
- Find the lowest set bit of a positive integer.
- Count how many iterations are needed to clear all set bits.
