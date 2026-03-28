# ex16_swap_with_pointers

## Goal

Swap two integers by passing their addresses into a function.

## Initial Problems

The first attempt used C++ reference syntax:

```c
void swap_int(int &a, int &b) {
```

Problem:
- C does not support reference parameters
- the correct C approach uses pointer parameters

Later attempts still mixed up pointer values and pointed values.

Examples of wrong directions:

```c
*ptr_a = b;
*ptr_b = a;
```

and

```c
int temp_a = (void *)a;
int temp_b = (void *)b;
```

Problems:
- `a` and `b` are pointers, not integers
- the swap must exchange `*a` and `*b`, not the addresses themselves
- pointer addresses should not be stored in `int` temporaries for this task

## Working Version

```c
#include <stdio.h>

void swap_int(int *a, int *b) {
        int temp_a = *a;
        int temp_b = *b;

        *a = temp_b;
        *b = temp_a;
}

int main(void) {
        int x = 11;
        int y = 99;
        printf("Before swap; x: %d, y: %d\n", x, y);
        swap_int(&x, &y);
        printf("After swap; x:%d, y: %d\n", x, y);
        return 0;
}
```

## Output

```text
Before swap; x: 11, y: 99
After swap; x:99, y: 11
```

## Lessons Learned

- C uses pointer parameters to let a function modify caller variables
- `a` and `b` are addresses, while `*a` and `*b` are the integer values to swap
- the swap needs a temporary variable so one value is not overwritten and lost
- the important operation is value swap through pointers, not address swap
