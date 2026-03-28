# ex17_set_value_with_pointer

## Goal

Modify a caller variable through a pointer parameter using a simpler pattern than swapping two values.

## Working Version

```c
#include <stdio.h>

void set_value(int *p, int new_value) {
        *p = new_value;
}

int main(void) {
        int value = 0;
        printf("Initial value is %d\n", value);
        set_value(&value, 10);
        printf("Current value is %d\n", value);
        return 0;
}
```

## Output

```text
Initial value is 0
Current value is 10
```

## Lessons Learned

- passing `&value` allows a function to modify the caller's variable
- `*p = new_value;` writes to the memory location pointed to by `p`
- this resembles a setter pattern in spirit, but in C it is just a plain function operating on an address
