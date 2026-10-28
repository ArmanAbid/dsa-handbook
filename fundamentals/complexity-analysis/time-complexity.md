# Time Complexity

Time complexity is a measure of how much work an algorithm does as its input increases.

Typically the input size is denoted as n. For an array, n is the number of elements in the array.

## Example: one loop

```python
for value in numbers:
    print(value)
```

The loop will execute 5 times if numbers contains 5 elements. If it has 1,000 elements, it runs 1,000 times. The complexity of the work is O(n) because the work grows with the size of `n`.

## Example: two separate loops

```python
for value in numbers:
    print(value)

for value in numbers:
    print(value)
```

Each loop executes `n` iterations and there are two of them, meaning that they execute approximately `2n` iterations. We ignore the constant term, so the complexity is O(n) not O(2n).

## Example: nested loops

```python
for a in numbers:
    for b in numbers:
        print(a, b)
```

For every one of the `n` values in the outer loop, the inner loop runs `n` times. That means you have n×n = n² iterations, and the complexity is **O(n²)**.

## What is meant by Big-O?

Big-O is an upper bound on the growth of the work an algorithm does, excluding constant factors and smaller terms. In common parlance, it is used to refer to the growth rate of an algorithm in DSA discussions.

For example, `3n² + 5n + 10` is **O(n²)** because the `n²` term dominates when `n` becomes large.

Big-O does not provide you with the exact runtime in seconds. Two O(n) algorithms can be of different speeds.

## Best, average, and worst case

These describe different inputs or outcomes for the same algorithm.

In an array, for a linear search:

- **Best case:** the target is first — one check, O(1).
- **Worst case:** the target is last or not present — up to `n` checks, O(n).
- **Average case:** on average, how many checks are needed for the inputs being considered; for a typical successful search with the target equally likely to be anywhere, this is O(n).

Always say which case you mean when it matters.

## Quick rules

- One loop over n items: typically O(n).
- Two nested loops, each running up to `n`: typically O(n²).
- Repeatedly halve the search space: usually O(log n).
- Separate sections add: O(n) + O(n) = O(n).
- Nested work multiplies: O(n) × O(n) = O(n²).

These are starting rules, not substitutes for checking what the code actually does.
