# Memory Allocation

Memory allocation is the process of obtaining storage for data. How allocation and cleanup work depends on the programming language.

## 1. Automatic Storage in C++

```cpp
int number = 10;
```

This local integer is automatically destroyed when its lifetime ends.

## 2. Dynamic Allocation in C++

```cpp
int* ptr = new int(10);
delete ptr;
```

The program explicitly frees up the allocation. If the allocation is not released and there is no other ownership mechanism controlling it, the program can leak memory.

Use `delete[]` for arrays allocated with `new[]` It is unsafe to mismatch allocation and deallocation forms.

## 3. Prefer RAII and Smart Pointers

There are tools in modern C++ that can take care of resources.

```cpp
#include <memory>

auto ptr = std::make_unique<int>(10);
```

The allocated integer is automatically released when its owning `unique_ptr` is destroyed.

Use standard containers like `std::vector` for normal collections, rather than dynamically allocating arrays.

## 4. Python Memory Management

Object memory is automatically managed in Python. Objects are still alive as long as they can be accessed through a reference, and there are implementation-specific details regarding the cleanup.

```python
numbers = [1, 2, 3]
```

You normally do not manually allocate or free the list's memory.

## 5. TypeScript and JavaScript

Garbage collection is used for JavaScript objects.

```typescript
let user = { name: "Alex" };
user = { name: "Sam" };
```

Once the first object can no longer be reached, it can be garbage collected. Cleanup does not necessarily happen immediately.

## 6. Common Memory Problems

- **Memory leak:** Memory is allocated or objects are still reachable after they are no longer used.
- **Dangling pointer:** A pointer refers to an object whose lifetime has ended.
- **Use-after-free:** Accessing memory that has been released.
- **Out-of-bounds access:** Reading or writing outside an object's valid range.

## Remember

Automatic memory management does not solve all memory issues. In any language, retaining unnecessary objects can waste memory and unsafe access can still occur in languages that permit it.
