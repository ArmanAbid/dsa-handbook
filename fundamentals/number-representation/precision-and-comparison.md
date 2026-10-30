# Precision and Comparison

Small errors can occur in floating-point calculations. Comparisons should be as precise as the problem requires.

## 1. Compare Using a Tolerance

You can compare if two floating point numbers are close enough rather than if they're equal.

```cpp
#include <cmath>

bool approximatelyEqual(double a, double b) {
    const double epsilon = 1e-9;
    return std::abs(a - b) < epsilon;
}
```

The value `1e-9` is only an example. The tolerance value used is dependent on the scale of the values and the needs of the problem.

## 2. Absolute and Relative Tolerance

When the values are close to a known scale, an absolute tolerance is helpful.

For values with very different magnitudes, a relative tolerance can be more appropriate.

A combined comparison is:

```cpp
#include <algorithm>
#include <cmath>

bool approximatelyEqual(double a, double b) {
    const double absTolerance = 1e-9;
    const double relTolerance = 1e-9;

    return std::abs(a - b) <=
        std::max(absTolerance,
                 relTolerance * std::max(std::abs(a), std::abs(b)));
}
```

Choose tolerances according to the expected error and required accuracy.

## 3. Formatting Is Not Precision

The number of decimal places printed affects the way the number is represented, but not the precision of the number that is stored.

```cpp
#include <iomanip>
#include <iostream>

double value = 1.0 / 3.0;
std::cout << std::fixed << std::setprecision(4) << value;
```

Output:

```text
0.3333
```

## 4. Integer vs Floating-Point Division

In C++:

```cpp
cout << 5 / 2;    // 2
cout << 5.0 / 2;  // 2.5
```

When both operands are integers, integer division is done.

## 5. LeetCode Considerations

Always follow the problem's output requirements:
- If it's expecting an integer, don't do any needless floating-point arithmetic.
- If it requires a decimal, use its required precision.
- If it involves geometric calculations, consider numerical error.
- If exact arithmetic is required, use an appropriate exact representation.

## Practice

- Compare `0.1 + 0.2` with `0.3`.
- Give a reason why more decimal places will not cure rounding error.
- Choose an appropriate tolerance for a geometric problem.
