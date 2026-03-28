# ex27_manual_reallocation

## Goal

Manually grow a heap-allocated integer array by allocating a larger block, copying the old values, freeing the old block, and continuing with the new block.

## High-Value Mistakes

The first important mistake was losing track of the original allocation.

Problem pattern:
- allocate `numbers`
- allocate `temp`
- copy values into `temp`
- assign `numbers = temp;`
- forget to free the original `numbers` block first

Why that is wrong:
- once `numbers` is overwritten, the old allocation becomes unreachable
- that creates a memory leak

The second important mistake was an off-by-one initialization bug.

Buggy loop:

```c
for (size_t i = count; i < new_count - 1; i++) {
    temp[i] = i + 1;
}
```

Why that is wrong:
- with `count = 3` and `new_count = 5`, only index `3` is initialized
- index `4` remains uninitialized
- printing that element produced garbage output

There was also a failure-path leak at first:
- if `temp == NULL`, the original `numbers` block must still be freed before returning

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
	int *temp = malloc(new_count * sizeof *temp);
	if (temp == NULL) {
		free(numbers);
		return 1;
	}

	for (size_t i = 0; i < count; i++) {
		temp[i] = numbers[i];
	}

	for (size_t i = count; i < new_count; i++) {
		temp[i] = (int)(i + 1);
	}

	free(numbers);
	numbers = temp;
	temp = NULL;

	for (size_t i = 0; i < new_count; i++) {
		printf("%d", numbers[i]);
	}
	printf("\n");

	free(numbers);
	numbers = NULL;
	return 0;
}
```

## Program Output

```text
12345
```

## Lessons Learned

- manual reallocation requires two valid blocks during the copy step
- the old block must not be freed before copying finishes
- the old block must be freed before its pointer is overwritten
- allocation-failure paths must clean up already-owned memory
- new elements in the larger block must be initialized before printing or using them
