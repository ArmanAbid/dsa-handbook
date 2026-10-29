# The Call Stack

The call stack keeps track of active function calls. Every call has its own local variables, parameters and execution position.

If one function calls another function, the first function will wait until the second function returns.

## Example

```python
def greet(n):
    if n == 0:
        return

    print("Entering", n)
    greet(n - 1)
    print("Leaving", n)

greet(3)
```

Output:

```text
Entering 3
Entering 2
Entering 1
Leaving 1
Leaving 2
Leaving 3
```

## Why Does This Happen?

The calls are entered in the following order:

```text
greet(3)
greet(2)
greet(1)
greet(0)
```

Once `greet(0)` returns, the waiting calls will resume in reverse order:

```text
greet(1)
greet(2)
greet(3)
```

This is the LIFO (last in first out) property of a stack.

## Call Stack and Memory

Recursive calls require stack space.

The auxiliary space can be `O(n)` when the recursion goes to the depth of `n`.

Depending on the language and runtime, the stack may overflow or a recursion depth error may occur.

## Important Distinction

The information about active calls is kept in the call stack. Unlike the heap, where dynamically allocated objects are typically stored, it is different.

## Practice

Trace the output of the example when `greet(3)` runs. Then change the function to print the second `print` statement before the recursive call and see how the output changes.
