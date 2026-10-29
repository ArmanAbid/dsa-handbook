
# Modular Arithmetic

Modular arithmetic deals with remainders. In competitive programming, it is often used when the numbers are too big or when a problem asks for an answer modulo a given number.

## 1. The Modulo Operation

The remainder of `a` divided by `m` is returned by `a % m,`, subject to the language's rules for negative values.

For example:

- `17 % 5 = 2`
- `20 % 5 = 0`
- `23 % 5 = 3`

The modulus `m` is normally a positive integer.

## 2. Why Use Modulo?

Some problems ask you to return the answer modulo a number such as:

`1,000,000,007`

This ensures that the result stays within a reasonable size and does not build up large numbers.

## 3. Addition and Multiplication

For a positive modulus `m`:

`(a + b) % m = ((a % m) + (b % m)) % m`

`(a × b) % m = ((a % m) × (b % m)) % m`

In programming, multiplying can cause an overflow before the modulo operation. Use a sufficiently wide type or a safe modular multiplication method when necessary.

## 4. Modular Subtraction

In languages like C++, subtraction may result in a negative remainder.

A typical normalization is:

```cpp
int result = ((a - b) % mod + mod) % mod;
```

This is based on the assumption that `mod > 0` and that the intermediate arithmetic doesn't overflow.

## 5. Modular Exponentiation

When computing `aⁿ % mod`, do not calculate the full power first if it becomes enormous.

Use exponentiation by squaring and take the remainder after each multiplication.

```cpp
long long modPow(long long a, long long n, long long mod) {
    long long result = 1;
    a %= mod;

    while (n > 0) {
        if (n % 2 == 1) {
            result = result * a % mod;
        }

        a = a * a % mod;
        n /= 2;
    }

    return result;
}
```

This takes `O(log n)` multiplications. It is written with the assumption of mod > 0 (a nonnegative exponent) and intermediate products that fit in long long.

## Practice

- Compute the remainder of a big integer.
- Calculate `(a + b) % mod`.
- Calculate `(a × b) % mod` safely.
- Implement modular exponentiation.