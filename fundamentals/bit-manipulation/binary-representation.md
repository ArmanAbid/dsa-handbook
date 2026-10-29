# Binary Representation

## What Is Binary?

Binary is a number system that uses only two digits: `0` and `1`.

Digital hardware has two states and this is why computers use binary.

Decimal is based on the powers of 10. In binary, powers of 2 are used.

For example:

```text
Binary:  1101
Powers:  8 4 2 1
Values:  1 1 0 1

Decimal = 8 + 4 + 0 + 1 = 13
```

So, binary `1101` is decimal `13`.

## Bits and Positions

A binary digit is known as a bit.

The bit positions start at `0` from the right.

For binary `10110`:

| Bit position | Bit value | Decimal value |
|--------------|-----------|---------------|
| 0            | 0         | 0             |
| 1            | 1         | 2             |
| 2            | 1         | 4             |
| 3            | 0         | 0             |
| 4            | 1         | 16            |

The number is `16 + 4 + 2 = 22`.

## Converting Decimal to Binary

Keep dividing the number by 2 and write down the remainders. Read the remainder from bottom to top.

Example: decimal `13`

```text
13 / 2 = 6 remainder 1
 6 / 2 = 3 remainder 0
 3 / 2 = 1 remainder 1
 1 / 2 = 0 remainder 1
```

Read upward: `1101`.

## Set Bits

A bit whose value is `1` is called a set bit.

For instance, the number `10110` has three set bits.

The number of set bits is also known as the population count or Hamming weight.

## Signed and Unsigned Integers

Unsigned integers are used to store non-negative numbers. Signed integer types also have a negative value, typically two's complement.

The range of values that can be represented depends on the number of bits and the integer type of the language.

Care should be taken with negative values, shifts and bitwise NOT, as they are language and integer representation dependent.

## Practice

- Convert decimal `10` to binary.
- Convert binary `11101` to decimal.
- Count the set bits in `101101`.
- Write the binary representation of several small integers.
