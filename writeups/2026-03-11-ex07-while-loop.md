# ex07_while_loop

## Goal

Learn how to repeat actions using a `while` loop and understand how it differs from a `for` loop.

## Implementation

```c
#include <stdio.h>

int main(void) {
        int i = 1;

        while (i <= 10) {
                printf("%d\n", i);
                i++;
        }

        return 0;
}
```

## Output

```text
1
2
3
4
5
6
7
8
9
10
```

## Lessons Learned

- a `while` loop keeps running while its condition is true
- the loop variable must be updated manually inside the loop when needed
- forgetting that update can create an infinite loop
- `for` and `while` can express similar logic, but `for` is often clearer for counting and `while` is often clearer for condition-driven repetition
