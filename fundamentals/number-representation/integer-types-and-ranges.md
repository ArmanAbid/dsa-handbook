# Integer Types and Ranges

Whole numbers are stored in integer types. Their size determines which values they can represent.

## 1. Common C++ Integer Types

Common examples on modern systems:

| Type      | Typical size | Approximate range                           |
|-----------|--------------|---------------------------------------------|
| `int32_t` | 32 bits      | -2,147,483,648 to 2,147,483,647             |
| `uint32_t`| 32 bits      | 0 to 4,294,967,295                          |
| `int64_t` | 64 bits      | Approximately -9.22 × 10^18 to 9.22 × 10^18 |
| `uint64_t`| 64 bits      | 0 to approximately 1.84 × 10^19             |

The size of primitive types like `int` and `long` is implementation dependent. The fixed-width types in `<cstdint>` can be useful if a specific width is needed, and supported.

## 2. Choosing a Type

Think about the highest value possible first when selecting a type.

```cpp
int count = 100000;
long long product = 100000LL * 100000;
```

The product is 10,000,000,000, which is too large to be stored in a typical 32-bit `int`.

The `LL` suffix guarantees that the multiplication will be done with `long long` operands.

## 3. Check Limits in C++

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << numeric_limits<int>::max() << '\n';
    cout << numeric_limits<long long>::max() << '\n';
}
```

This allows you to check the range of the types your compiler supports.

## 4. Python Integers

The built-in type int in Python can be larger than 64 bits, depending on the amount of memory available.

```python
x = 10**100
print(x)
```

Python does not suffer from the ordinary fixed-width integer overflows, but very large integers take up more memory and more computation.

## 5. TypeScript Numbers

The number type in JavaScript is IEEE 754 double precision floating point.

The safe integer range is the range where integers are exactly representable:

`-(2^53 - 1)` through `2^53 - 1`

JavaScript supports `bigint` for larger integers:

```typescript
const value = 9007199254740993n;
```

Integer literals for a `bigint` should be preceded by an `n`. A `bigint` cannot be mixed directly with `number` arithmetic.

## Practice

- Find the maximum value of `int` in your C++ environment.
- Describe why it is dangerous to multiply two large ints.
- Make a comparison between Python's `int` and TypeScript's `number`.
