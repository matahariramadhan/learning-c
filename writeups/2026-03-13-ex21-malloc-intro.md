# ex21_malloc_intro

## Goal

Allocate space for one integer on the heap, store a value in it, print it, and free the memory safely.

## Initial Problems

Initial issues:
- `printf()` was used without including `<stdio.h>`
- `free ptr;` was written as if `free` were a keyword instead of a function call

Those were corrected to:
- include `<stdio.h>`
- call `free(ptr);`

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
        int *ptr = malloc(sizeof *ptr);
        if (ptr == NULL) {
                return 1;
        }
        *ptr = 42;
        printf("%d\n", *ptr);
        free(ptr);
        ptr = NULL;
        return 0;
}
```

## Output

```text
42
```

## Lessons Learned

- `malloc(sizeof *ptr)` allocates enough space for the type pointed to by `ptr`
- `malloc()` results must be checked for `NULL`
- heap memory should be released with `free()`
- setting a pointer to `NULL` after `free()` can be a useful habit in longer programs to avoid accidental reuse
