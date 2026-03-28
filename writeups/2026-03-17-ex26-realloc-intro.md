# ex26_realloc_intro

## Goal

Resize a heap-allocated integer array safely with `realloc()`, preserve the old values, initialize the new slots, and free the final allocation correctly.

## High-Value Mistake To Avoid

The main risk in this exercise is overwriting the original pointer too early.

Unsafe pattern:

```c
numbers = realloc(numbers, new_count * sizeof *numbers);
```

Why that is dangerous:
- if `realloc()` fails, it returns `NULL`
- if that `NULL` is assigned directly to `numbers`, the original allocation address is lost
- that means the original block cannot be freed anymore

The safer pattern is:

```c
int *temp = realloc(numbers, new_count * sizeof *temp);
if (temp == NULL) {
    free(numbers);
    return 1;
}
numbers = temp;
```

That preserves the original pointer until success is confirmed.

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	size_t count = 3;
	int *numbers = malloc(count * sizeof *numbers);
	if (numbers == NULL) {
		return 1;
	}

	for (size_t i = 0; i < count; i++) {
		numbers[i] = (int)(i + 1);
	}

	size_t new_count = 5;
	int *temp = realloc(numbers, new_count * sizeof *temp);
	if (temp == NULL) {
		free(numbers);
		return 1;
	}

	numbers = temp;

	for (size_t i = count; i < new_count; i++) {
		numbers[i] = (int)(i + 1);
	}

	for (size_t i = 0; i < new_count; i++) {
		printf("%d\n", numbers[i]);
	}

	free(numbers);
	numbers = NULL;
	return 0;
}
```

## Program Output

```text
1
2
3
4
5
```

## Lessons Learned

- `realloc()` may resize in place or move the data to a new block
- direct assignment from `realloc()` can lose the original allocation on failure
- a temporary pointer makes the resize logic safe
- new elements in the grown block must still be initialized before use
- the final block must be freed exactly once
