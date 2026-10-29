# Counting Set Bits

Counting set bits means finding the number of `1` bits in a binary representation.

For example:

```text
n = 13 = 1101
```

The answer is 3 as there are three set bits.

## 1. Check Every Bit

For a nonnegative integer:

```cpp
int countBits(unsigned int n) {
    int count = 0;

    while (n > 0) {
        count += n & 1u;
        n >>= 1;
    }

    return count;
}
```

In each iteration, it tests the least significant bit and rotates the number right.

Time complexity: `O(log n)` for positive `n`, where the number of bits is proportional to the log of `n`.

## 2. Brian Kernighan's Algorithm

Remove the lowest set bit, rather than checking each bit.

```cpp
int countBits(unsigned int n) {
    int count = 0;

    while (n != 0) {
        n &= n - 1;
        count++;
    }

    return count;
}
```

One set bit is removed in each iteration.

Time complexity: `O(k)`, where `k` is the number of set bits. In the worst case for a fixed-width integer, it is bounded by the number of bits in the type.

## 3. Built-in Functions

Built-in operations exist in modern languages for counting the population.

C++20:

```cpp
#include <bit>

unsigned int n = 13;
int count = std::popcount(n);
```

Python:

```python
n = 13
count = n.bit_count()
```

Use the appropriate function for the language and integer type.

## Comparison

| Method                     | Work performed |
|----------------------------|--------------------------------------------|
| Check each bit             | One iteration per bit position             |
| Brian Kernighan's algorithm| One iteration per set bit                  |
| Built-in population count  | Often optimized by the compiler or runtime |

## Practice

- Count set bits in `7`, `8`, and `15`.
- Compare the two manual algorithms on numbers with few set bits.
- Solve the classic problem of counting set bits for every number from `0` to `n`.
