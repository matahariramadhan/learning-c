# ex11_string_input

## Goal

Read a full line of text safely into a fixed-size buffer and print it back.

## Initial Problems

Initial code:

```c
#include <stdio.h>

int main(void) {
        char name[100];
        printf("Input your name: ");
        fgets("%s", *name);
        printf("\n Your name is %s", name);
        return 0;
}
```

Problems:
- `fgets()` was called with the wrong arguments
- `fgets()` does not use format strings like `"%s"`
- `*name` is a single `char`, not the destination buffer
- the return value of `fgets()` was not checked

## Safer Final Version

```c
#include <stdio.h>

int main(void) {
        char name[100];
        printf("Input your name: ");
        if (fgets(name, sizeof name, stdin) == NULL) {
                return 1;
        }
        for (size_t i = 0; i < sizeof name; i++) {
                if (name[i] == '\0') {
                        break;
                }
                if (name[i] == '\n') {
                        name[i] = '\0';
                        break;
                }
        }
        printf("Your name is %s", name);
        return 0;
}
```

## Lessons Learned

- `fgets()` needs the buffer, the buffer size, and the input stream
- `fgets()` is safer than `scanf("%s", ...)` for reading a full line
- input function return values should be checked before using the result
- `sizeof name` is better than repeating a literal size like `100`
- `fgets()` usually keeps the trailing newline if there is room in the buffer
- newline trimming can be done by replacing `'\n'` with `'\0'`
