# Logarithms

Logarithms are useful in understanding the complexity of algorithms, particularly binary search, tree operations, and divide and conquer algorithms.

## 1. What Is a Logarithm?

A logarithm answers this question:

**What power must a base be raised to in order to produce a number?**

For example:

`log₂(8) = 3`

Because:

`2³ = 8`

Similarly:

- `log₂(16) = 4`
- `log₁₀(100) = 2`
- `log₂(32) = 5`

## 2. Why Logarithms Appear in DSA

Suppose a process repeatedly divides a problem's size by two.

Starting with `n = 16`:

`16 → 8 → 4 → 2 → 1`

It requires 4 divisions to get to `1`.

The number of divisions is about `log₂(n)` and the process takes `O(log n)` steps.

This principle is used in binary search to cut the search space in half each time.

## 3. Common Logarithm Rules

For valid positive values:

- `log(a × b) = log(a) + log(b)`
- `log(a / b) = log(a) - log(b)`
- `log(a^k) = k × log(a)`

The change of base formula is:

`log_b(n) = log_a(n) / log_a(b)`

## 4. Logarithm Bases in Complexity

In Big-O notation, logarithms with different constant bases are equivalent:

`O(log₂ n) = O(log₁₀ n) = O(log n)`

This is because changing the base only multiplies the logarithm by a constant.

## Practice

- Calculate `log₂(64)`.
- Explain why binary search takes `O(log n)` time.
- Estimate the number of times you can divide 1,024 by 2 until you get to 1.
