# Base Cases and Recursive Cases

All recursive solutions must have a clear stopping point and a mechanism to move towards that stopping point.

## 1. Base Case

The base case handles the simplest input directly, without making another recursive call.

For factorial:

```python
if n == 0:
    return 1
```

The answer is known, since `0! = 1`.

## 2. Recursive Case

The recursive case reduces the problem to a smaller version of itself.

```python
return n * factorial(n - 1)
```

The function requires the value of `factorial(4)` to compute the value of `factorial(5)`. This call requires `factorial(3)`, and so on, until the base case is reached.

## 3. Make Progress Toward the Base Case

A recursive call should progress the input towards a condition that will terminate the recursion.

Incorrect:

```python
def count(n):
    if n == 0:
        return

    count(n)  # The input never changes.
```

Correct:

```python
def count(n):
    if n == 0:
        return

    count(n - 1)
```

## 4. Choose the Right Base Case

Consider summing an array recursively.

```python
def array_sum(numbers, index):
    if index == len(numbers):
        return 0

    return numbers[index] + array_sum(numbers, index + 1)
```

The base case is reached when `index` reaches the array's length. The return value of 0 is ok because adding 0 does not change the sum.

This also works for an empty array, the first element is already at the same index as the length of the array, so the result is `0`.

## Checklist

Ask Before using recursion:

- What is the simplest input?
- What should the answer be for that input?
- How does each call reduce the problem?
- Will the calls ever get to the base case?
- Does every recursive call return the correct result?