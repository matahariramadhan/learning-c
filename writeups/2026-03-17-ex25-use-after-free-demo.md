# ex25_use_after_free_demo

## Goal

Deliberately create a use-after-free bug in a tiny program, observe the toolchain catching it, and then correct the code.

## High-Value Mistake

The buggy version did this:

```c
*ptr = 50;
free(ptr);
*ptr = 100;
```

Problem:
- after `free(ptr);`, the memory pointed to by `ptr` is no longer valid to use
- dereferencing `ptr` after that is a use-after-free bug

Important outcome:
- the compiler caught this under `-Werror=use-after-free`
- the bug was detected before runtime

That is a strong lesson:
- strict warnings can catch real memory bugs early

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
        int *ptr = malloc(sizeof *ptr);
        if (ptr == NULL) {
                return 1;
        }
        *ptr = 50;
        free(ptr);
        ptr = NULL;
        return 0;
}
```

## Lessons Learned

- once memory has been freed, it must not be dereferenced
- the pointer variable may still exist, but the pointee is no longer valid
- setting the pointer to `NULL` after `free()` is a defensive cleanup habit
- strict compiler warnings can detect some use-after-free cases before execution
