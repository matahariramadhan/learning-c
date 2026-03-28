# ex15_pointer_modify_value

## Goal

Modify a variable through a pointer and confirm that the address stays the same while the stored value changes.

## Working Version

```c
#include <stdio.h>

int main(void) {
        int value = 43;
        int *ptr = &value;
        printf("Before: Direct value is %d and the address is %p\n", value, (void *)ptr);

        *ptr = 45;
        printf("After: Direct value is %d and the address is %p\n", value, (void *)ptr);
        return 0;
}
```

## Output

```text
Before: Direct value is 43 and the address is 0x...
After: Direct value is 45 and the address is 0x...
```

The important observation is that the address remains the same, but the value changes after writing through `*ptr`.

## Small Mistakes Along the Way

- `./` was used instead of `./main`
- the `Makefile` temporarily lost `-Werror` and repeated `-Wall`

## Lessons Learned

- `*ptr = 45;` writes to the memory location pointed to by `ptr`
- changing the pointee changes the original variable when the pointer refers to that variable
- the pointer address can stay the same while the pointed value changes
