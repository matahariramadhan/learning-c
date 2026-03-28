# ex14_pointers_intro

## Goal

Understand the relationship between a variable, its address, and a pointer that refers to it.

## Initial Problems

Early attempts mixed up the address-of operator `&` and the dereference operator `*`.

Examples of wrong ideas:

```c
int ptr = *value;
```

and

```c
int *ptr = *value;
```

Problems:
- `value` was an `int`, not a pointer
- `*value` tried to dereference a non-pointer value
- later attempts also tried to print `*ptr` with `%p`, which is wrong because `%p` expects an address, not an integer value

## Working Version

```c
#include <stdio.h>

int main(void) {
        int value = 42;
        int *ptr = &value;
        printf("Direct value %d, indirect value %d and the address is %p\n",
               value, *ptr, (void *)ptr);
        return 0;
}
```

## Lessons Learned

- `&value` produces the address of `value`
- `ptr` stores that address
- `*ptr` reads the value through the pointer
- `%p` is for addresses, not ordinary integer values
- direct and indirect access can refer to the same underlying value
