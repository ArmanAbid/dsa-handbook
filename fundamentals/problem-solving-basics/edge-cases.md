# Edge Cases

An edge case is an input at the boundary of a problem's constraints or an unusual valid input that can reveal a bug.

The solution that works for the example input might not work for different inputs.
## Common Edge Cases

| Case            |       Example          |       What to check                          |
|-----------------|------------------------|----------------------------------------------|
| Empty input     | `[]`                   | Does the code handle no elements?            |
| One element     | `[7]`                  | Is the bound of the loop correct?            |
| Duplicate values| `[3, 3, 1]`            | Are repeated values handled correctly?       |
| Negative values | `[-4, 2, -1]`          | Does the solution assume values are positive?|
| All values equal| `[5, 5, 5]`            | Does the code handle identical values?       |
| Already sorted  | `[1, 2, 3]`            | Does the algorithm behave correctly?         |
| Reverse sorted  | `[3, 2, 1]`            | Are ordering assumptions correct?            |
| Maximum values  | Largest allowed numbers| Could overflow occur?                        |
| No valid answer | Depends on the problem | Is failure handled correctly?                |

Not all problems have all cases. Always follow its stated constraints.

## Example: Finding the Maximum

Suppose you have an array of numbers and you want to find the maximum element in the array.

Ask the questions before writing the solution:
- What happens if the array has only one element?
- What happens if all the numbers are negative?
- What if the array is empty?

If empty input is not allowed, you can initialize the maximum using the first element. If there is a possibility of empty input, you must deal with it as per the problem requirements.

Initializing the maximum to `0` would be incorrect for an array such as `[-5, -2, -8]`, because the actual maximum is `-2`.

## Quick Checklist

Ask the following questions before submitting a solution:

- What is the smallest valid input?
- What is the largest valid input?
- Can values repeat?
- Are there values that can be zero or negative?
- Is an answer always guaranteed?
- Does the first and last element get treated properly?

Edge cases are part of checking correctness, not an optional final step.
