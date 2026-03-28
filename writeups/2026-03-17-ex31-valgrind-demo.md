# ex31_valgrind_demo

## Goal

Run a small program under `valgrind`, observe a real leak report, fix the leak, and confirm the program is clean afterward.

## High-Value Mistakes

The first mistake was tool setup.

Initial build:
- compiled with `-fsanitize=address,undefined`

Why that was wrong for this exercise:
- AddressSanitizer and `valgrind` both instrument memory behavior
- running `valgrind` on an ASan build produced a warning and invalid leak-check conditions

That setup had to be corrected first by removing:

```make
-fsanitize=address,undefined
```

The second mistake was command usage.

This command was incomplete:

```bash
valgrind --leak-check=full
```

Why:
- `valgrind` needs a target program, for example `./main`

The real memory bug was the missing `free()`:

```c
int *ptr = malloc(sizeof *ptr);
if (ptr == NULL) {
	return 1;
}
*ptr = 42;
return 0;
```

That leaked the allocated integer because the program exited without freeing it.

## Leak Report Before Fix

Key lines:

```text
in use at exit: 4 bytes in 1 blocks
total heap usage: 1 allocs, 0 frees, 4 bytes allocated
4 bytes in 1 blocks are definitely lost
```

Meaning:
- one allocation happened
- no free happened
- `valgrind` confirmed the block was truly leaked

## Working Version

```c
#include <stdlib.h>

int main(void) {
	int *ptr = malloc(sizeof *ptr);
	if (ptr == NULL) {
		return 1;
	}
	*ptr = 42;
	free(ptr);
	ptr = NULL;
	return 0;
}
```

## `valgrind` Result After Fix

Key lines:

```text
in use at exit: 0 bytes in 0 blocks
total heap usage: 1 allocs, 1 frees, 4 bytes allocated
All heap blocks were freed -- no leaks are possible
```

## Lessons Learned

- `valgrind` should be run on a plain `-g` build, not an ASan build
- `valgrind` needs the program path as part of the command
- `definitely lost` means the leak is real and unrecoverable inside the running process
- fixing the leak means making allocations and frees match correctly
