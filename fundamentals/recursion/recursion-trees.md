# Recursion Trees

A recursion tree visualizes the recursive calls made while solving a problem.

Useful when multiple smaller calls are generated for each call.

## Example: Fibonacci Numbers

The Fibonacci sequence is defined as:

- `F(0) = 0`
- `F(1) = 1`
- `F(n) = F(n - 1) + F(n - 2)` for `n >= 2`

A recursive implementation is:

```python
def fib(n):
    if n <= 1:
        return n

    return fib(n - 1) + fib(n - 2)
```

## Visualizing fib(4)

```text
fib(4)
├── fib(3)
│   ├── fib(2)
│   │   ├── fib(1)
│   │   └── fib(0)
│   └── fib(1)
└── fib(2)
    ├── fib(1)
    └── fib(0)
```

Notice that the value of `fib(2)` is computed more than once. The naive implementation is inefficient due to this repeated work.

## Complexity

The naive recursive Fibonacci implementation has exponential time complexity, commonly expressed as `O(2^n)` as an upper bound.

It has a maximum recursion depth of `O(n)` and an auxiliary call-stack space of `O(n)`.

## How to Use a Recursion Tree

1. Draw the first function call.
2. Add a child for each recursive call.
3. Repeat until the base cases.
4. Identify repeated subproblems.
5. Estimate the total work and the maximum depth.

Repeated subproblems can often be optimized using memoization or dynamic programming.

## Practice

Draw the recursion tree for `fib(5)`. Determine which calls are repeated and why it is unnecessary to calculate them again.