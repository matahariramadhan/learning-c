# ex32_file_read_intro

## Goal

Open a text file for reading, process it line by line with `fgets()`, print each line, and handle file-open failure cleanly.

## High-Value Mistakes

The main code path was correct, but two practical mistakes during testing were useful:

1. The file-open failure path was real and intentional.

The code handled it like this:

```c
FILE *file = fopen("input.txt", "r");
if (file == NULL) {
	fprintf(stderr, "failed to open input.txt\n");
	return 1;
}
```

That is the right minimal pattern for this stage:
- detect failure
- print a clear error
- return non-zero

2. The first attempt to create the input file used:

```bash
echo "Hello there\nHow are you\nNice to meet you" > input.txt
```

Why that was misleading:
- in this shell, `echo` did not interpret `\n` as real newlines
- it wrote the backslash characters literally
- the program then correctly read and printed those literal characters

The fix was to create the file with real line breaks, using a more reliable tool such as:

```bash
printf "Hello there\nHow are you\nNice to meet you\n" > input.txt
```

Another useful shell lesson:
- `main` failed with `command not found`
- `./main` is required because the shell does not search the current directory by default

## Working Version

```c
#include <stdio.h>

int main(void) {
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "failed to open input.txt\n");
		return 1;
	}

	char buffer[100];
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		printf("%s", buffer);
	}

	fclose(file);
	return 0;
}
```

## Program Output

With a real multi-line `input.txt`:

```text
Hello there
How are you
Nice to meet you
```

## Lessons Learned

- `fopen(..., "r")` opens a file for reading
- `fgets()` can read from files, not just `stdin`
- a `while (fgets(...) != NULL)` loop is the basic line-reading pattern
- `stderr` is the right stream for simple error messages
- shell-side test setup matters; bad test input can make correct code look suspicious
