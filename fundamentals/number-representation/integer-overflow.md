# Integer Overflow

An integer overflow is when an arithmetic operation produces a value too large to fit into an integer type.

## 1. Example

A typical 32-bit signed `int` has a maximum value of `2,147,483,647`.

```cpp
int x = 2000000000;
int y = x + 1000000000;
```

The result of the mathematical operation is too large to store in the `int` type. Signed overflow is undefined in C++.

Don't assume it will wrap around.

## 2. Overflow Can Happen Before Assignment

This is not safe:

```cpp
int a = 100000;
int b = 100000;

long long product = a * b;
```

The multiplication happens as `int` arithmetic before the result is assigned to `product`.

Use a wider operand first:

```cpp
long long product = 1LL * a * b;
```

## 3. Common Places Overflow Appears

- Multiplying large values.
- Summing up large arrays.
- Calculating factorials or powers.
- Using `mid = (left + right) / 2` when the sum may overflow.
- Squaring values while checking numeric conditions.

A safer midpoint formula for nonnegative ordered bounds is:

```cpp
int mid = left + (right - left) / 2;
```

## 4. Python and TypeScript

Python integers can be made larger as needed, depending on resources.

The `number` type in TypeScript can be used to store large numbers, but numbers outside of its safe integer range may lose precision. Use `bigint` when exact large integer arithmetic is required.

## 5. Preventing Overflow

1. Read the maximum input constraints.
2. Estimate the largest intermediate result.
3. Select an appropriate type.
4. Promote operands for arithmetic as necessary.
5. Do not assume that overflow will wrap around.

## Practice

- Find the maximum possible sum of an array with some restriction.
- Identify whether a multiplication can overflow a 32-bit integer.
- Rewrite unsafe multiplication using `long long`.
