# ex22_malloc_array

## Goal

Allocate an array of integers on the heap, fill it in a loop, print the elements, and free the memory safely.

## Initial Problems

The first incorrect attempt tried to treat heap memory like a brace-initialized array:

```c
*numbers = {10, 20, 30, 40, 50};
```

Problem:
- `*numbers` is one `int`
- brace initialization in that form does not apply to an already allocated heap block

Another incorrect cleanup attempt was:

```c
*numbers = NULL;
```

Problem:
- `*numbers` is an `int`
- the pointer variable is `numbers`, so the defensive cleanup form is `numbers = NULL;`

There was also a precedence mistake:

```c
*numbers[i] = ...
```

Problem:
- `numbers[i]` is already an `int`
- `*numbers[i]` tries to dereference that `int` as if it were a pointer

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
        size_t count = 5;
        int *numbers = malloc(count * sizeof *numbers);
        if (numbers == NULL) {
                return 1;
        }
        for (size_t i = 0; i < count; i++) {
                numbers[i] = (int)(i + 1) * 10;
        }
        for (size_t i = 0; i < count; i++) {
                printf("%d\n", numbers[i]);
        }
        free(numbers);
        numbers = NULL;
        return 0;
}
```

## Output

```text
10
20
30
40
50
```

## Lessons Learned

- heap arrays must be allocated with the total byte count needed
- after allocation, elements are assigned individually or with a loop
- `numbers[i]` is the cleanest way to access each heap array element here
- after `free(numbers);`, the pointer may be set to `NULL`, but the freed memory must not be used
