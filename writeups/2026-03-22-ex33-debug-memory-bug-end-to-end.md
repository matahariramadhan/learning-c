# ex33_debug_memory_bug_end_to_end

## Goal

Trigger a real memory bug, inspect the runtime report, identify the exact cause, fix the code, and confirm the corrected version runs cleanly.

## High-Value Mistake

The bug was an off-by-one heap write.

Buggy loop:

```c
for (size_t i = 0; i <= count; i++) {
    numbers[i] = (int)i * 10;
}
```

Why it was wrong:
- `count` was `5`
- the allocation held exactly `5` integers
- valid indexes were `0, 1, 2, 3, 4`
- the last loop iteration used `i == 5`
- `numbers[5]` writes one element past the allocated block

This was not a read bug. It was a write bug:

```c
numbers[i] = ...
```

That assignment writes into memory, and the final iteration wrote outside the heap allocation.

## ASan Report

Key information from the runtime error:

```text
ERROR: AddressSanitizer: heap-buffer-overflow
WRITE of size 4
main.c:12
0 bytes after 20-byte region
allocated by thread T0 here:
main.c:6
```

What that means:
- the program wrote 4 bytes outside the heap block
- the bad write happened at line 12
- the heap block was allocated at line 6
- the invalid address was exactly one element beyond the 5-int allocation

## Important Tooling Correction

`valgrind` was also tried, but it was run on an ASan build.

That result was not valid for leak or memory-check purposes because:
- AddressSanitizer and `valgrind` both instrument memory behavior
- they should not be used together in the same build/run

So the meaningful debugger for this exercise was the ASan report.

## Fixed Version

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
		numbers[i] = (int)i * 10;
	}

	for (size_t i = 0; i < count; i++) {
		printf("%d\n", numbers[i]);
	}

	free(numbers);
	return 0;
}
```

## Program Output After Fix

```text
0
10
20
30
40
```

## Lessons Learned

- valid array indexes stop at `count - 1`
- `i <= count` is a classic off-by-one bug when filling a `count`-element array
- ASan can point directly to both the invalid access and the allocation site
- end-to-end debugging means reproducing the bug, understanding it, fixing it, and rerunning to confirm the fix
