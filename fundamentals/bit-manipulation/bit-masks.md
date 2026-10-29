# Bit Masks

A bit mask is an integer whose binary value is used to indicate specific bit positions.

Using bit masks you can store several yes/no values in a single integer.

## Create a Mask

To create a mask with only bit `k` set:

```cpp
int mask = 1 << k;
```

For example, `1 << 3` produces binary `1000`.

When using higher bit positions, use an unsigned integer type that is appropriate for the size of the bit position.

## 1. Check a Bit

Use AND to determine whether bit `k` is set:

```cpp
bool isSet = (n & (1u << k)) != 0;
```

If the result is not zero, then the bit is set.

## 2. Set a Bit

Use OR:

```cpp
n |= (1u << k);
```

Sets bit `k` to 1 without affecting the other bits.

## 3. Clear a Bit

Apply AND to the inverted mask:

```cpp
n &= ~(1u << k);
```

This sets bit `k` to `0`.

## 4. Toggle a Bit

Use XOR:

```cpp
n ^= (1u << k);
```

If the bit is `0`, it becomes `1`. If it is `1`, it becomes `0`.

## Example

Start with:

```text
n = 10 = 1010
```

Set bit `0`:

```text
  1010
| 0001
------
  1011 = 11
```

Clear bit `3`:

```text
  1011
& 0111
------
  0011 = 3
```

## Representing Sets

Assume that there are 4 items. Four bits can be used to indicate which items are selected.

```text
0000 = no items selected
0001 = item 0 selected
0101 = items 0 and 2 selected
1111 = all four items selected
```

This is helpful for subset enumeration, state compression and dynamic programming.

## Practice

- Check whether bit `2` is set in `n = 12`.
- Set bit `1` in `n = 8`.
- Clear bit `3` in `n = 15`.
- Toggle bit `0` twice and observe the result.
