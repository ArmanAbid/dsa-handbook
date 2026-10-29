# Powers and Exponents

## 1. What Is an Exponent?

An exponent indicates the number of times the base is used as a factor.

For example:

`2⁴ = 2 × 2 × 2 × 2 = 16`

Here, `2` is the base and `4` is the exponent.

## 2. Useful Rules

For suitable nonzero bases:

- `aᵐ × aⁿ = aᵐ⁺ⁿ`
- `aᵐ / aⁿ = aᵐ⁻ⁿ`
- `(aᵐ)ⁿ = aᵐⁿ`
- `a⁰ = 1`
- `a⁻ⁿ = 1 / aⁿ`

The rules are helpful in simplifying mathematical expressions and in studying algorithms.

## 3. Repeated Multiplication

A simple way to calculate `aⁿ` is to multiply `a` by itself `n` times.

```cpp
long long power(long long a, int n) {
    long long result = 1;

    for (int i = 0; i < n; i++) {
        result *= a;
    }

    return result;
}
```

This takes `O(n)` multiplications. It can overflow even with the use of `long long`.

## 4. Fast Exponentiation

You can calculate powers more efficiently using exponentiation by squaring.

If the exponent is even:

`aⁿ = (a²)ⁿ⁄²`

If the exponent is odd:

`aⁿ = a × aⁿ⁻¹`

This decreases the number of multiplications to `O(log n)`.

```cpp
long long power(long long a, long long n) {
    long long result = 1;

    while (n > 0) {
        if (n % 2 == 1) {
            result *= a;
        }

        a *= a;
        n /= 2;
    }

    return result;
}
```

This example assumes that the exponent is nonnegative and that intermediate results can be stored in a `long long`. Use modular exponentiation or other suitable representation for large powers.

## Practice

- Calculate a power using a loop.
- Implement exponentiation by squaring.
- Compare the number of multiplications in both approaches.
