# GCD and LCM

## 1. Greatest Common Divisor (GCD)

The GCD of two integers is the greatest positive integer divisible by both positive integers.

Example:

`gcd(12, 18) = 6`

Both numbers are divisible by `6`, and there is no larger positive integer that is a common factor of both.

## 2. Euclidean Algorithm

The Euclidean algorithm uses this property:

`gcd(a, b) = gcd(b, a % b)`

Repeat until the second number becomes zero. The other first number is the GCD.

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
```

Time complexity: `O(log(min(a, b)))` for nonnegative inputs, with the usual convention that `gcd(0, 0)` is handled separately if needed.

## 3. Least Common Multiple (LCM)

The LCM is the smallest positive integer divisible by both positive integers.


Example:

`lcm(4, 6) = 12`

The relationship between GCD and LCM is:

`lcm(a, b) = (a / gcd(a, b)) * b`

To prevent integer overflow, divide first and then multiply.

```cpp
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}
```

In real code, ensure `gcd` supports the chosen integer type and account for overflow if the result may exceed its range.

## Practice

- Find the GCD of two numbers.
- Find the LCM of two numbers.
- Reduce a fraction to its simplest form.
- Determine whether two numbers are coprime (their GCD is `1`).
