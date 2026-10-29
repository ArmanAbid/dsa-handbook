# Stack and Heap

There are two general approaches that programs use to manage memory: stack and heap. The exact details depend on the language and runtime.

## 1. Stack Memory

The call stack is a record of the functions that are currently being called. Function parameters and local variables may be stored in stack frames, depending on the compiler and runtime.

```cpp
void example() {
    int x = 10;
}
```

Once `example()` returns, its stack frame is no longer in use. Local variables can not be accessed after they are out of scope.

## 2. Heap Memory

The heap is the memory area used for dynamically allocated memory and many run-time managed objects.

```cpp
int* ptr = new int(10);
delete ptr;
```

In this case, `new` dynamically allocates an integer and `delete` frees up the space.

Use automatic objects and smart pointers instead of using new and delete where possible in modern C++.

## 3. Stack vs Heap

| Feature       | Stack                                 | Heap                               |
|---------------|---------------------------------------|------------------------------------|
| Common purpose| Function-call state and local storage | Dynamic memory and objects         |
| Lifetime      | Often tied to a function call         | Depends on allocation and ownership|
| Management    | Usually automatic                     | Manual or runtime-managed          |
| Common risk   | Excessive call depth                  | Leaks and invalid memory access    |

These are conceptual differences, not universal rules about where every variable or object must live.

## 4. Why This Matters in DSA

A recursive function that is too deeply recursive can cause the call stack to overflow.

Each node of a dynamically allocated linked list can be stored in the heap.

Knowing about lifetime and ownership can prevent invalid accesses and memory leaks.
