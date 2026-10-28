# Common Complexity Classes

These are typical growth rates and are listed in approximate order of slowest to fastest growth.

| Complexity |    Name     | Example |
|------------|-------------|---------------------------------------------------------|
| O(1)       | Constant    | Access an array element by index                        |
| O(log n)   | Logarithmic | Binary search in a sorted array                         |
| O(n)       | Linear      | Scan every element once                                 |
| O(n log n) | Linearithmic| Typical efficient comparison sorting, such as merge sort|
| O(n²)      | Quadratic   | Compare every pair using two full nested loops          |
| O(2ⁿ)      | Exponential | Try every subset of `n` items                           |
| O(n!)      | Factorial   | Generate all orderings of n distinct items              |

## Why the difference matters

Now suppose that n is very large:

- O(1) stays about the same.
- O(log n) grows very slowly.
- O(n) grows in proportion to the input.
- O(n²) can get really costly.
- O(2ⁿ) and O(n!) are typically not feasible for moderate values of n.

For instance, if we double the number of rows in the table, we approximately double the work of O(n), but approximately quadruple the work of O(n²).

These classes are estimates and not guarantees of actual runtime. The details of implementation and the shape of the input still count.
