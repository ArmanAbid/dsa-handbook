# Floating-Point Numbers

Floating-point types are used to store approximate real numbers in a finite amount of bits.

They are helpful for fractions and measurements but not all decimal numbers can be written exactly.

## 1. Floating-Point Types

Common C++ types are:
- `float`
- `double`
- `long double`

A typical default for floating point calculations is `double`.

## 2. Why Some Values Are Inexact

Consider:

```python
print(0.1 + 0.2)
```

The output is typically:

```text
0.30000000000000004
```

Standard binary floating-point formats do not have exact finite binary representations for the decimal fractions 0.1 and 0.2.

Rounding errors may occur when performing calculations.

## 3. Floating-Point Range and Precision

The floating-point types can store values that are much larger or smaller than those of many integer types, but they have limited significant precision.

A number can be within the representable magnitude range but not exactly representable.

## 4. When to Use Floating Point

When approximations are sufficient, use floating-point numbers, for example:
- Geometric calculations.
- Scientific calculations.
- Measurements and rates.

If the money or exact decimal arithmetic type is used, then use an integer unit, e.g., cents.

## 5. Avoid Assuming Exact Equality

This comparison may not hold true:

```cpp
double a = 0.1 + 0.2;
double b = 0.3;

cout << (a == b);
```

There may be a small rounding error in the values.

Apply an appropriate tolerance if the problem requires a comparison to be approximate.
