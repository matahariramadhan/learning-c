# ex19_array_interaction_with_pointer

## Goal

Iterate through an array and prove that `numbers[i]` matches `*(ptr + i)` for each valid index.

## Initial Problem

The first loop used:

```c
for (size_t i = 0; i < sizeof numbers; i++) {
```

Problem:
- `sizeof numbers` is the total array size in bytes, not the number of elements
- for a 5-element `int` array, that can be `20` bytes instead of `5` elements
- the loop ran past the valid indexes and triggered a stack buffer overflow

AddressSanitizer correctly reported the out-of-bounds access.

## Working Version

```c
#include <stdio.h>

int main(void) {
        int numbers[] = {10, 20, 30, 40, 50};
        int *ptr = numbers;
        size_t count = sizeof numbers / sizeof numbers[0];
        for (size_t i = 0; i < count; i++) {
                printf("%d | %d\n", numbers[i], *(ptr + i));
        }
        return 0;
}
```

## Output

```text
10 | 10
20 | 20
30 | 30
40 | 40
50 | 50
```

## Lessons Learned

- `numbers[i]` and `*(ptr + i)` can refer to the same value
- `sizeof array` is bytes, not element count
- `sizeof array / sizeof array[0]` gives the element count while the variable is still an actual array in scope
- sanitizers are useful because they catch out-of-bounds errors immediately
