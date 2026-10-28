# Dry-Running Code

A dry run is a step by step execution of the code with a particular input and observing the changes in the variables.

It will guide you to understand the code and locate logical errors.

## Example

```python
numbers = [2, 5, 3]
total = 0

for number in numbers:
    total += number

print(total)
```

Let's trace the loop:

| Step            | `number` | `total` |
|-----------------|----------|---------|
| Before loop     |    —     |    0    |
| First iteration |    2     |    2    |
| Second iteration|    5     |    7    |
| Third iteration |    3     |    10   |

The output is `10`.

## How to Dry-Run Code

1. Select a small input.
2. Write the initial values of the variables.
3. Follow each statement in execution order.
4. After each operation, update the variables.
5. Check the final result.

## When Is It Useful?

Dry runs are particularly helpful for:
- Nested loops
- Index/pointer change
- Conditions inside loops
- Recursive functions
- Problems where the order of operations matters

## Common Mistake

Do not skip steps just because they seem obvious. It is easy to get a wrong answer if the condition or variable in a loop is not correct.

## Practice

Dry-run the example again with:

`numbers = [1, 4, 6]`

What will `total` be after each iteration?
