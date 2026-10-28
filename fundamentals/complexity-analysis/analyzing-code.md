# How to Analyze Code

Estimate the time and auxiliary space complexity using this short process.

## 1. Identify the input size

Select a variable to use for the number of elements in an array, like n. For two independent inputs, use two variables, e.g. `n` and `m`.

## 2. Count how often the main work happens

Consider loops, nested loops, recursion and operations that could have costs that increase with the input.

```python
for value in numbers:
    print(value)
```

The loop runs `n` times: **O(n)** time.

```python
for i in numbers:
    for j in numbers:
        print(i, j)
```

The inner work is executed `n` times for each of the `n` outer iterations: O(n²) time.

## 3. Simplify the result

Simplify the fastest growing term and remove constant terms::

- `O(3n + 10)` becomes O(n).
- `O(n² + n)` becomes O(n²).
- `O(5)` becomes O(1).

## 4. Count extra memory separately

Ask: Is the algorithm producing data that increases as the input increases?

- O(1) auxiliary space – a few variables.
- O(n) auxiliary space - Up to `n` elements in a list.

Take recursive call stack memory into account.

## 5. Check assumptions

Not all operations are constant time. For instance, if you're searching a list, it's typically O(n), but if you're accessing an array element by index, it's O(1). A loop that divides the number `n` by 2 at each iteration is typically O(log n), not O(n).

## Practice

Try to determine time complexity and auxiliary space complexity for each snippet.

### A
```python
for x in numbers:
    print(x)
```

### B
```python
result = []
for x in numbers:
    result.append(x * 2)
```

### C
```python
for i in numbers:
    for j in numbers:
        print(i, j)
```

<details>
<summary>Answers</summary>

- **A:** O(n) time, O(1) auxiliary space.
- **B:** O(n) time, O(n) auxiliary space because `result` grows with `n`.
- **C:** O(n²) time, O(1) auxiliary space, assuming that the loop variables and the print operation require constant extra space.

</details>
