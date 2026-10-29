# XOR Properties

XOR (`^`) is particularly useful in problems with duplicate values, missing numbers and bitwise comparisons.

## 1. XOR Truth Table

| A | B | A XOR B |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 1       |
| 1 | 0 | 1       |
| 1 | 1 | 0       |

XOR returns `1` when the bits differ.

## 2. Important Properties

### A Number XOR Itself Is Zero

```text
a ^ a = 0
```

Each bit is equal to itself, so each output bit is `0`.

### XOR with Zero Changes Nothing

```text
a ^ 0 = a
```

### XOR Is Commutative

```text
a ^ b = b ^ a
```

The order of operands does not affect the result.

### XOR Is Associative

```text
(a ^ b) ^ c = a ^ (b ^ c)
```

XOR operations can be regrouped without affecting the result.

## 3. Find the Single Number

Suppose every number in an array appears twice except one number. Find the number that appears once.

```cpp
int singleNumber(vector<int>& nums) {
    int result = 0;

    for (int n : nums) {
        result ^= n;
    }

    return result;
}
```

Example:

```text
nums = [4, 1, 2, 1, 2]

4 ^ 1 ^ 2 ^ 1 ^ 2 = 4
```

The duplicate values cancel out since a ^ a = 0. The remaining value is `4`.

- Time complexity: `O(n)`
- Extra space complexity: `O(1)`

This is assuming that exactly one value appears once and the other values appear twice.

## 4. Find a Missing Number

Assume that there is an array with all numbers from 0 to n, but one number is missing.

XOR all the expected values with all the array values. Each value in the two sets is cancelled out, leaving the missing value.

```cpp
int missingNumber(vector<int>& nums) {
    int result = nums.size();

    for (int i = 0; i < nums.size(); i++) {
        result ^= i;
        result ^= nums[i];
    }

    return result;
}
```

This solution has a time complexity of O(n) and space complexity of O(1).

## Important Limitation

XOR does not count frequencies. The single-number trick works only when the problem's frequency conditions allow pairs to cancel.

If values occur three times, or multiple values have different frequencies, a different method may be required.

## Practice

- Find the single number when every other value appears twice.
- Find the missing number from `0` through `n`.
- Predict the result of `a ^ b ^ a`.
- Explain why XOR can cancel duplicate pairs.
