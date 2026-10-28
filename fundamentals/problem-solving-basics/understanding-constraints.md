# Understanding Constraints

Constraints indicate what values are permitted for the variables in a problem and what size they can be. They can help you determine if your strategy will be efficient enough.

## 1. Check the Input Size

For a problem with an array of up to `n` elements, the input size is `n`.

Always consider the maximum allowed input, not just the small examples.

## 2. Estimate the Required Complexity

hese are only general guidelines and not rules.

| Input size       | Approaches worth considering             |
|------------------|------------------------------------------|
| `n <= 10`        | Some exponential or factorial approaches |
| `n <= 20`        | Some `O(2^n)` approaches                 |
| `n <= 1,000`     | `O(n²)` may be practical                 |
| `n <= 100,000`   | Usually aim for `O(n log n)` or `O(n)`   |
| `n <= 1,000,000` | Often aim for `O(n)` or `O(n log n)`     |

The actual limits vary based on the time limit, language, memory usage, and work done by each operation.

## 3. Example

Assume that there are up to 100,000 elements in an array.

Comparing every pair requires approximately:

`n × n = 100,000 × 100,000 = 10,000,000,000`

That's about 10 billion comparisons, typically too slow for a typical coding challenge.

An alternative solution that is more efficient is to sort or use a hash map.

## 4. Check Value Limits Too

Size of input is not the only constraint.

For example:
- In languages that have fixed-width integer types, large numbers may overflow the integer type
- If the value of an element is very large, creating an array from it can take up too much space.
- Comparing all pairs of elements in two arrays of size `n` and `m` can take `O(n × m)` time.

## Remember

Constraints are there to help you decide on an approach, but not to ensure it passes. Analyze the actual time and memory requirements.
