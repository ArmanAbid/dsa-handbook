# Value vs Reference

A value is the data itself. A reference or alias is an indirect access to existing data. Depending on the language, the meaning varies.

## 1. C++: Pass by Value

When an integer is passed by value, it is copied into the function parameter.

```cpp
void change(int x) {
    x = 100;
}

int main() {
    int a = 5;
    change(a);
    // a is still 5
}
```

The function modifies its local copy, not `a`.

## 2. C++: Pass by Reference

A reference parameter refers to the original variable.

```cpp
void change(int& x) {
    x = 100;
}

int main() {
    int a = 5;
    change(a);
    // a is now 100
}
```

The function can modify the original variable through `x`.

## 3. Python: Objects and Names

Python variables are names bound to objects. When you pass an argument, the function gets another reference to the same object.

```python
def change(items):
    items.append(4)

numbers = [1, 2, 3]
change(numbers)

print(numbers)  # [1, 2, 3, 4]
```

The list is modified, so the caller sees the change.

But if you rebind the parameter, the caller's variable isn't rebound:

```python
def replace(items):
    items = [9, 9]

numbers = [1, 2, 3]
replace(numbers)

print(numbers)  # [1, 2, 3]
```

## 4. TypeScript: Objects and Primitives

TypeScript is JavaScript at runtime.

Primitive values like numbers are copied when assigned:

```typescript
let a = 5;
let b = a;

b = 10;
// a is still 5
```

Objects may be passed via more than one variable:

```typescript
const first = { score: 10 };
const second = first;

second.score = 20;
// first.score is now 20
```

Both variables refer to the same object.

## Key Takeaway

There are two questions to ask:

1. Does this operation return a new value or get access to an existing object?
2. Am I changing the object itself or merely rebinding a variable?
