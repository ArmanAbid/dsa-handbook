# Debugging and Testing

**Debugging** means finding and fixing the cause of incorrect behavior.

**Testing** the process of determining if your code gives the correct output for specific inputs.

## A Practical Debugging Process

1. **Reproduce the bug.** Determine an input that causes the problem.
2. **Compare expected and actual results.**  Determine what is actually wrong.
3. **Trace the code.** Trace important variables and conditions..
4. **Find the first incorrect step.** The last incorrect response could be a result of the previous mistake.
5. **Fix the cause.** Avoid making random changes just to pass one example.
6. **Test again.** Verify fix is working.

## Test Different Types of Input

- **Normal case:** A normal input.
- **Boundary case:** The smallest or largest allowable input.
- **Unusual case:** duplicates, negative values or no valid answer (if applicable).

## Example: An Incorrect Loop

Now suppose that you want to traverse all the elements in an array except the last one.

Test an input for which the output is based on that last element. Next, follow the loop condition and determine the end of the loop.

This is typically more successful than random loop changes.

## Keep Failing Test Cases

If you discover and resolve a bug, save the input that caused the bug to appear.

Repeat that test following any changes. This is known as a **regression test**: it is used to ensure that a previously corrected bug is not reoccurring.

## Before Submitting

- Does the code meet the requirements of the problem?
- Does it handle all valid inputs?
- Are the loop bounds correct?
- Could any value overflow?
- Is the time complexity suitable for the constraints?
- Does the code use a reasonable amount of memory?