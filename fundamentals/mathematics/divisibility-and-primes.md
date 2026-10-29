# Divisibility and Prime Numbers

## 1. Divisibility

A nonzero integer `a` is divisible by a nonzero integer `b` if the remainder of dividing a by b is 0.

For example:
- `12` is divisible by `3`.
- `15` is divisible by `5`.
- `14` is not divisible by `4`.

## 2. Factors

A positive factor of `n` is a positive integer that is evenly divisible by `n`.

The positive factors of `12` are:

`1, 2, 3, 4, 6, 12`

Factors come in pairs. For example, `3 × 4 = 12`.

## 3. Prime Numbers

A prime number is an integer `n > 1` that has exactly two positive factors: `1 and n`.

Examples: `2`, `3`, `5`, `7`, `11`.

Important:
- `2` is the only even prime number.
- `1` is not prime.
- Numbers less than `2` are not prime.

## 4. Checking Whether a Number Is Prime

If n is composite, it has a factor ≤ its square root. Hence it is enough to test the factors up to `sqrt(n)`

```cpp
bool isPrime(int n) {
    if (n < 2) return false;

    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }

    return true;
}
```

Time complexity: `O(√n)`.

If d is very large, be careful of potential overflow in d * d; use d <= n / d or an appropriate wider integer type

## 5. Counting Divisors Efficiently

Factors occur in pairs: If `d` is a factor of `n`, then `n / d` is also a factor of `n`.

This allows you to list the divisors up to `√n` instead of testing all the integers up to `n`.

When `n` is a perfect square, be sure not to count the square root twice.

## Practice

- Determine if a number is prime.
- Print all divisors of a positive integer.
- Count the divisors of a number.
- Print all prime numbers up to a given limit.
