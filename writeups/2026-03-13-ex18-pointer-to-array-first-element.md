# ex18_pointer_to_array_first_element

## Goal

Connect arrays and pointers by showing that a pointer to the first element can be used to access later array elements.

## Initial Confusion

An intermediate attempt used:

```c
*ptr + 1
```

and produced:

```text
10, 10, 20, 11
```

Why:
- `*ptr + 1` means “take the value pointed to by `ptr`, then add 1”
- if `*ptr` is `10`, the result is `11`

That is different from:

```c
*(ptr + 1)
```

which means:
- move the pointer to the next array element
- then dereference it

## Working Version

```c
#include <stdio.h>

int main(void) {
        int numbers[] = {10, 20, 30};
        int *ptr = numbers;
        printf("%d is equal to %d,\n%d is equal to %d\n",
               numbers[0], *ptr, numbers[1], *(ptr + 1));
        return 0;
}
```

## Output

```text
10 is equal to 10,
20 is equal to 20
```

## Lessons Learned

- `numbers` can act like a pointer to `numbers[0]` in expressions
- `numbers[0]` and `*ptr` can refer to the same value
- `numbers[1]` and `*(ptr + 1)` can refer to the same value
- `*ptr + 1` and `*(ptr + 1)` are different expressions with different meanings
- pointer arithmetic moves in units of the pointed type
