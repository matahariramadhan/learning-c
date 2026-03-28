# ex08_functions

## Goal

Create a function that doubles a number and returns the result.

## Initial Problems

### 1. Missing parameter type

Initial form:

```c
int doubler(i) {
```

Problem:
- parameter types were not declared explicitly
- this old-style form should be treated as wrong in modern C

Fix:

```c
int doubler(int i) {
```

### 2. Missing semicolon after `return`

Problem:
- `return i` is not a complete C statement

Fix:

```c
return i;
```

## Final Code

```c
#include <stdio.h>

int doubler(int i) {
        return i * 2;
}

int main(void) {
        int x = 5;
        printf("%d\n", doubler(x));
        return 0;
}
```

## Output

```text
10
```

## Lessons Learned

- functions must declare parameter types explicitly
- functions return values with `return`
- semicolons still apply to `return` statements
- functions help separate input, processing, and output into reusable parts
