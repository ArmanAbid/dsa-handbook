# Space Complexity

Space Complexity is a measure of the amount of memory required as the input increases.

A useful distinction:

- **Input space:** Memory required to store the input.
- **Auxiliary space:** extra memory the algorithm uses while working.

In DSA, O(1) extra space means auxiliary space, excluding the space required for the input.

## Example: constant extra space

```python
total = 0
for value in numbers:
    total += value
```

The algorithm requires a fixed number of additional variables (total and value). The number of variables does not increase as the array length increases, thus auxiliary space is **O(1)**.

## Example: space grows with input

```python
squares = []
for value in numbers:
    squares.append(value * value)
```

The new list contains one result for each input element. It has an extra space of O(n) when there are n elements.

## Recursion also uses memory

The call stack is used in recursive calls. A recursive function that calls itself n times will require O(n) space in the stack. This depends on the recursion structure and the information stored in each call.

## Quick guide

- O(1) additional variables: typically
- An additional list, set, or map that can expand as `n` increases; typically O(n).
- A two-dimensional `n × n` table: O(n²).
- Recursive depth `n`: frequently O(n) stack space.

Count memory that can be expanded with the input; don't just count the obvious variables.
