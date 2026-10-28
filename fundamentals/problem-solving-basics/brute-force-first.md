# Start with Brute Force

Brute force is a simple method that systematically tests every possibility until a solution is discovered.

It's not necessarily the quickest solution, but it's usually the easiest way to get a handle on a problem.

## Example: Two Sum

Given:

`numbers = [4, 1, 7, 3]`

`target = 8`

Look for two other elements that add up to the target.

A brute-force solution would test all pairs:

```python
numbers = [4, 1, 7, 3]
target = 8

for i in range(len(numbers)):
    for j in range(i + 1, len(numbers)):
        if numbers[i] + numbers[j] == target:
            print(i, j)
```

The solution is to return the indices of the elements that are `1` and `7`: `1, 2`.

## Complexity

- **Time:** `O(n²)` since pairs are checked using nested loops.
- **Extra space:** `O(1)` since we are using a fixed number of variables.

## How to Improve It

Ask yourself:

- Am I going over the same information over and over?
- Can I recall values I have previously encountered?
- Can sorting or another data structure help?

In this problem, a hash map can be used to store previously seen values and the expected time complexity is reduced to `O(n)` with `O(n)` extra space.

## A Good Approach

1. Understand what makes an answer valid.
2. Write the simplest solution you can explain.
3. Test it on a small example.
4. Analyze its time and space complexity.
5. Optimize if the solution is too slow.

## Remember

A brute force solution is a good way to start, but may not be efficient for large inputs.