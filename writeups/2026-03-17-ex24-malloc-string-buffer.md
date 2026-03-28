# ex24_malloc_string_buffer

## Goal

Allocate a string buffer on the heap, store a short string in it, print it, and free the memory safely.

## High-Value Mistake

The first version used:

```c
int *string = malloc(count * sizeof *string);
```

and then stored:

```c
'H', 'e', 'l', 'l', 'o', '\0'
```

Why it seemed to work:
- character constants are small integer values
- printing one element at a time with `%c` accepts integer character codes

Why it was still wrong:
- the buffer was modeling a string as `int *` instead of `char *`
- the mistake became obvious when `%s` was used, because `%s` expects a `char *`

That was the important lesson:
- code can appear to work while still teaching the wrong memory model

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
        size_t count = 6;
        char *string = malloc(count * sizeof *string);
        if (string == NULL) {
                return 1;
        }
        string[0] = 'H';
        string[1] = 'e';
        string[2] = 'l';
        string[3] = 'l';
        string[4] = 'o';
        string[5] = '\0';
        printf("%s\n", string);
        free(string);
        string = NULL;
        return 0;
}
```

## Output

```text
Hello
```

## Lessons Learned

- a heap string should be stored in `char *`
- `%s` requires a null-terminated `char` buffer
- the null terminator matters on heap strings just as much as stack strings
- a program that seems to work with the wrong type can still be conceptually wrong
