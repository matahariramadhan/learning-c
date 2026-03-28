# ex30_gdb_assignment_timing

## Goal

Use `gdb` on a tiny program to understand exactly when assignments take effect.

## High-Value Mistake

The important confusion was this:
- `gdb` stopped at `int x = 1;`
- `print x` showed `0`
- that looked like `x` already had a meaningful value

That interpretation is wrong.

What actually happened:
- `gdb` had stopped before the line executed
- the assignment `x = 1` had not happened yet
- the displayed `0` was not the lesson
- the lesson was that the highlighted line is the next line to run, not a line that has already run

This became clearer through the session:

- at `int x = 1;`, `x` had not been assigned yet
- after `next`, execution moved to `x = 5;`, and then `x` showed `1`
- after the next `next`, execution moved to `x = x + 2;`, and then `x` showed `5`
- after the next `next`, execution moved to `printf("%d\n", x);`, and then `x` showed `7`

That proves the rule:
- assignments take effect only after their line has executed

## Program Used

```c
#include <stdio.h>

int main(void) {
	int x = 1;
	x = 5;
	x = x + 2;
	printf("%d\n", x);
	return 0;
}
```

## `gdb` Commands Used

```gdb
break main
run
print x
next
print x
next
print x
next
print x
```

## Observed Values

- before `int x = 1;` executed: `x` showed `0` in this run
- after `int x = 1;` executed: `x` showed `1`
- after `x = 5;` executed: `x` showed `5`
- after `x = x + 2;` executed: `x` showed `7`

## Lessons Learned

- `gdb` stops before the highlighted line runs
- variable values should be interpreted relative to the current execution point
- a value shown before assignment is not proof of meaningful initialization
- `next` is the right command for watching state changes line by line
- `$1`, `$2`, and similar labels are `gdb` history values, not C variables
