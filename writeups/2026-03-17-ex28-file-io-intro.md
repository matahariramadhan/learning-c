# ex28_file_io_intro

## Goal

Open a text file, write a few lines into it, close it safely, and verify the output on disk.

## High-Value Mistake To Avoid

The main failure point in this exercise is assuming file opening always works.

Risk pattern:

```c
FILE *file = fopen("output.txt", "w");
fprintf(file, "Hello file\n");
```

Why that is dangerous:
- `fopen()` can fail and return `NULL`
- using `fprintf()` on a `NULL` file pointer is invalid

The correct pattern is:

```c
FILE *file = fopen("output.txt", "w");
if (file == NULL) {
    return 1;
}
```

Another practical correction:
- this exercise generates `output.txt`, so the `clean` target should remove it too

## Working Version

```c
#include <stdio.h>

int main(void) {
	FILE *file = fopen("output.txt", "w");
	if (file == NULL) {
		return 1;
	}

	fprintf(file, "Hello file\n");
	fprintf(file, "Number: %d\n", 42);

	fclose(file);
	return 0;
}
```

## File Output

```text
Hello file
Number: 42
```

## Lessons Learned

- `fopen()` returns a `FILE *` used for file operations
- `"w"` opens a file for writing and overwrites existing contents
- `fprintf()` works like `printf()`, but writes to the file stream
- successful file opens must be matched with `fclose()`
- generated files belong in the `clean` target when they are part of the exercise output
