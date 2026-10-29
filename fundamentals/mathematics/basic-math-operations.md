# Basic Math Operations

Many DSA problems involve basic arithmetic. To prevent common errors, it is important to understand integer division, remainders and number properties

## 1. Integer Division

In languages like C++, if the two operands are integers, the fractional part is discarded.

For example, in C++:

```cpp
int result = 7 / 2; // 3
```

In Python, the / operator will return a floating point value, and the // operator will return the result of floor division:

```python
print(7 / 2)  # 3.5
print(7 // 2) # 3
```

Beware of negative numbers as Python will round down on integer division, but C++ will truncate towards zero.

## 2. Modulo and Remainders

The modulo operator `%` gives the remainder of a division.

```cpp
cout << 10 % 3; // 1
cout << 12 % 4; // 0
```

Common uses:
- Check whether a number is even: `n % 2 == 0`
- Check divisibility: `n % d == 0`
- Get the last decimal digit of a nonnegative integer: `n % 10`
- Remove the last decimal digit of a nonnegative integer: `n / 10`

## 3. Even and Odd Numbers

An integer is even if it is divisible by 2. Otherwise, it is odd.

```cpp
if (n % 2 == 0) {
    cout << "Even";
} else {
    cout << "Odd";
}
```

## 4. Digit Extraction

You can work with the digits of a non-negative integer from right to left::

```cpp
while (n > 0) {
    int digit = n % 10;
    cout << digit << '\n';
    n /= 10;
}
```

For `n = 472`, the digits are processed in this order: `2`, `7`, `4`.

Note: This loop will not process any digits if `n = 0`. If necessary, treat zero separately.

## 5. Absolute Value

The absolute value represents a number's nonnegative magnitude.

`abs(-8) = 8`

When using the minimum representable signed integer with fixed-width integer types, be careful cause the positive value of that integer might not fit in the same type.

## Practice

- Determine even or odd numbers..
- Count the digits of a nonnegative integer.
- Calculate the sum of an integer's digits.
- Reverse the digits of an integer.