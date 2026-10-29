# Bitwise Operators

Bitwise operators perform operations on individual bits.

Consider:

```text
a = 12 = 1100
b = 10 = 1010
```

## 1. AND (`&`)

If both bits are `1`, then the bit is `1`; otherwise, the bit is `0`.

```text
  1100
& 1010
------
  1000
```

Result: `8`.

Common use: checking whether a particular bit is set.

## 2. OR (`|`)

If one or more of the bits is `1`, the bit is `1`.

```text
  1100
| 1010
------
  1110
```

Result: `14`.

Common use: setting bits.

## 3. XOR (`^`)

A bit is `1` when the corresponding bits differ.

```text
  1100
^ 1010
------
  0110
```

Result: `6`.

Common use: toggling bits and solving problems involving pairs of equal values.

## 4. NOT (`~`)

NOT flips every bit in the integer type's representation.

In C++, the ~ operator is used with the promoted integer representation, which can be negative.

```cpp
int x = 5;
cout << ~x;
```

On a normal system with 32-bit `int`, it will output -6.

Avoid assuming NOT simply produces a positive binary number with the visible bits flipped.

## 5. Left Shift (`<<`)

A left shift moves bits toward higher positions.

```cpp
int x = 1 << 3; // 8
```

For appropriate nonnegative values and safe shift counts, shifting left by `k` positions corresponds to multiplying by `2^k`.

## 6. Right Shift (`>>`)

A right shift moves bits toward lower positions.

```cpp
int x = 16 >> 2; // 4
```

Shifting to the right by `k` is the same as integer division by `2^k` for nonnegative integers.

## Operator Summary

| Operator | Meaning     |
|----------|-------------|
| `&`      | Bitwise AND |
| `|`      | Bitwise OR  |
| `^`      | Bitwise XOR |
| `~`      | Bitwise NOT |
| `<<`     | Left shift  |
| `>>`     | Right shift |

In C++, check that the number of shifts is valid and can be represented. The shifting to or past an invalid signed-bit position may result in undefined behavior.

## Practice

- Calculate `6 & 3`.
- Calculate `6 | 3`.
- Calculate `6 ^ 3`.
- Calculate `1 << 4`.
- Calculate `32 >> 3`.
