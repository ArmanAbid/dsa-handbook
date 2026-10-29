# Common Recursion Mistakes

It is easier to debug recursive solutions by examining the base case, the progress, and the return value individually.

## 1. Missing a Base Case

Incorrect:

```python
def count(n):
    return count(n - 1)
```

There is no stopping condition, so calls continue until the runtime stops the program.

**Fix:** Set up a base case that recursive calls can get to.

## 2. Not Making Progress

Incorrect:

```python
def count(n):
    if n == 0:
        return

    count(n)
```

The base case is never reached for any value of `n>0`, since the input does not change.

**Fix:** move closer to the base case, e.g., call `count(n - 1)` if `n > 0`

## 3. Incorrect Return Values

Incorrect:

```python
def factorial(n):
    if n == 0:
        return 1

    factorial(n - 1)
    return n
```

The result of the recursive call is thrown away. This function returns `n` instead of calculating the factorial.

Correct:

```python
def factorial(n):
    if n == 0:
        return 1

    return n * factorial(n - 1)
```

## 4. Repeated Work

The naive Fibonacci implementation repeatedly solves the same subproblems.

**Fix:** Try memoization, tabulation or a better mathematical recurrence.

## 5. Excessive Recursion Depth

A recursive function that calls itself thousands of times can go beyond the depth of the run time.

**Fix:** Consider an iterative approach or an explicit stack when appropriate.

## 6. Incorrect Base-Case Boundaries

A function may stop one step too early or too late.

**Fix:** Test smallest valid input, base case, and a value just above base case.

## Debugging Checklist

- Is the base case correct?
- Can it be reached from all valid inputs?
- Does each call make progress?
- Is the recursive result used correctly?
- Do you have slow execution because of repeated calculations?
- Is the maximum recursion depth safe?
