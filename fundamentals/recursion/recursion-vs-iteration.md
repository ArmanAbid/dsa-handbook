# Recursion vs Iteration

Recursion solves a problem using function calls. Iteration repeats operations using loops.

Both techniques can be used to solve many of the same problems.

## Example: Sum from 1 to n

### Recursive Version

```python
def sum_recursive(n):
    if n == 0:
        return 0

    return n + sum_recursive(n - 1)
```

### Iterative Version

```python
def sum_iterative(n):
    total = 0

    for value in range(1, n + 1):
        total += value

    return total
```

Both return `15` for `n = 5`.

## Comparison

| Feature           | Recursion                               | Iteration |
|-------------------|-----------------------------------------|---------------------------------------------|
| Main mechanism    | Function calls                          | Loops                                       |
| Stopping condition| Base case                               | Loop condition                              |
| Call-stack usage  | Often grows with depth                  | Usually constant for simple loops           |
| Readability       | Natural for self-similar problems       | Natural for repeated steps                  |
| Common uses       | Trees, backtracking, divide-and-conquer | Array processing, counting, repeated updates|

## Complexity

For the examples given above:
- Time: `O(n)` for both.
- Recursive auxiliary space: `O(n)` because of the number of calls in use.
- Iterative auxiliary space: `O(1)`.

## Which should you use?

Recursion should be used when the problem can be naturally broken down into smaller versions of itself, such as traversing a tree.

Iterate when a loop is simpler to express the solution, or when recursive depth might be too great.

Neither approach is always better. Choose based on clarity, constraints, and the language's runtime behavior.
