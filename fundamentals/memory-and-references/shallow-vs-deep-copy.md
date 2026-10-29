# Shallow Copy vs Deep Copy

Copying an object does not necessarily copy everything inside it. Knowing the difference can help avoid unwanted data changes.

## 1. Shallow Copy

A shallow copy will make a new outer object but may refer to the same inner objects.

Python example:

```python
import copy

original = [[1, 2], [3, 4]]
shallow = copy.copy(original)

shallow[0][0] = 99

print(original)  # [[99, 2], [3, 4]]
```

The outer list is copied, the inner lists are shared.

## 2. Deep Copy

A deep copy copies nested objects recursively, based on the "copy behavior" of the language.

```python
import copy

original = [[1, 2], [3, 4]]
deep = copy.deepcopy(original)

deep[0][0] = 99

print(original)  # [[1, 2], [3, 4]]
print(deep)      # [[99, 2], [3, 4]]
```

Modifying the nested list in the deep copy does not modify the nested list in the original.

## 3. Assignment Is Not Always Copying

In Python:

```python
a = [[1, 2]]
b = a
```

There is no new list created. Both names refer to the same outer list.

In TypeScript:

```typescript
const a = { items: [1, 2] };
const b = a;
```

Both variables refer to the same object.

## 4. Copying in C++

The copy behavior of C++ is defined by the type and the definition of its copy operations. Normally, containers like `std::vector` copy their elements when copied, but a raw pointer copy only copies the address.

```cpp
int value = 10;
int* a = &value;
int* b = a;
```

In this case, the values of `a` and `b` refer to the same integer.

## Why It Matters in DSA

Unexpected sharing can result in:
- An original array or object to change unexpectedly.
- Bugs when modifying nested collections.
- Incorrect assumptions about whether a function modifies its input.

## Practice

- In Python, compare b = a to a shallow copy.
- Modify a nested list after making a shallow copy.
- Describe the reasons why a copy of a raw pointer does not copy the pointed-to object.
