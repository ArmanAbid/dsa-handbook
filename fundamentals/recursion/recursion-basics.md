# Recursion Basics

## What Is Recursion?

Recursion is a function that calls itself to solve a smaller version of the same problem.

For instance, one can recursively count down from a number.

```python
def countdown(n):
    if n == 0:
        print("Done!")
        return

    print(n)
    countdown(n - 1)

countdown(3)
```

Output:

```text
3
2
1
Done!
```

Every call processes the current number, and then calls the function with a smaller number.

## The Two Essential Parts

A recursive function usually contains:

1. **Base case:** The condition that stops recursion.
2. **Recursive case:** The part that calls the function recursively with a smaller or simpler input.

If there is no base case to stop the recursion, it can continue until the program runs out of call-stack space.

## Example: Factorial

The factorial of a nonnegative integer `n` is the product of all positive integers from `1` through `n`.

For example:

`4! = 4 × 3 × 2 × 1 = 24`

The factorial of n can be defined recursively as:

- `0! = 1`
- `n! = n × (n - 1)!` for `n > 0`

```python
def factorial(n):
    if n == 0:
        return 1

    return n * factorial(n - 1)

print(factorial(4))  # 24
```

## Trace the Calls

```text
factorial(4)
└── 4 * factorial(3)
    └── 3 * factorial(2)
        └── 2 * factorial(1)
            └── 1 * factorial(0)
                └── 1
```

The base case is `1`. The waiting calls then calculate:

- `factorial(1) = 1 × 1 = 1`
- `factorial(2) = 2 × 1 = 2`
- `factorial(3) = 3 × 2 = 6`
- `factorial(4) = 4 × 6 = 24`

## Complexity

For this factorial implementation:
- Time complexity: `O(n)`
- Auxiliary space complexity: `O(n)` since there are `n + 1` calls to the functions at the deepest level.

## Practice

- Print numbers from `n` down to `1`.
- Print numbers from `1` up to `n`.
- Sum the integers from 1 to n.
- Compute the factorial of `n`.
