# ex20_sum_array_with_pointer

## Goal

Write a function that sums an array by receiving a pointer to the first element and an element count.

## Working Version

```c
#include <stdio.h>

int sum_array(int *ptr, size_t array_length) {
        int sum = 0;
        for (size_t i = 0; i < array_length; i++) {
                sum = sum + *(ptr + i);
        }
        return sum;
}

int main(void) {
        int numbers[] = {10, 20, 30, 40, 50};
        size_t count = sizeof numbers / sizeof numbers[0];
        printf("%d\n", sum_array(numbers, count));
        return 0;
}
```

## Output

```text
150
```

## Lessons Learned

- when an array is passed to a function, the function receives a pointer to the first element
- the caller should compute the element count while the variable is still an array in that scope
- `*(ptr + i)` can be used inside a loop to access each element through pointer arithmetic
- `size_t` is a better type for array lengths and counts than `int`
