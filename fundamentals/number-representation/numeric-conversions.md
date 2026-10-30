# Numeric Conversions

Numeric conversion is the process of changing the representation or interpretation of a number by a type. There are some conversions that lose information.

## 1. Integer to Floating Point

If the integer is too large, converting it to a floating-point type may result in a loss of precision.

For instance, in JavaScript, the type `number` can't store every integer exactly after the safe integ


## 2. Floating Point to Integer

In C++, the fractional part is dropped off of a finite floating-point number when converting to an integer, and the number is rounded down toward zero if it is representable.

```cpp
int a = 3.9;   // 3
int b = -3.9;  // -3
```

This is not the same as rounding to the nearest whole number.

## 3. Implicit Conversion

Type conversion may be done automatically by the compiler when performing arithmetic or assignments.

```cpp
int x = 5;
double y = x; // y becomes 5.0
```

It is sometimes convenient to allow implicit conversions, but it can lead to bugs if mixed signedness or narrowing conversions are performed.

## 4. Explicit Conversion

When you know you want a conversion, use a cast in C++:

```cpp
double value = 7.8;
int whole = static_cast<int>(value); // 7
```

The cast does not make an unsafe conversion safe. Look at the range of the destination type and its conversion behavior.

## 5. TypeScript Conversions

JavaScript and TypeScript have a difference between number and bigint.

```typescript
const a = 10;
const b = 10n;

// a + b; // Type error: cannot mix number and bigint
```

Convert explicitly when appropriate:

```typescript
const total = BigInt(a) + b;
```

Only use `bigint` when the number is already the exact integer value that it represents.


## 6. Conversion Checklist

- Does the destination type have a value?
- Is there any chance of losing precision in the conversion?
- Does the operation use truncation or rounding?
- Are signed and unsigned values being mixed?
- Does the language allow the operation directly?

## Practice

- Convert `7.9` and `-7.9` to integers in C++.
- Explain the difference between `number` and `bigint` in TypeScript.
- Identify a narrowing conversion that could lose information.
