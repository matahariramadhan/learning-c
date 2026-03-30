# Phase 1 Notes

## 2026-03-06 - `stdio.h` basics

`#include <stdio.h>` is used when a program needs input/output.

Common functions:
- `printf()` prints formatted output
- `scanf()` reads input
- `puts()` prints a string and appends a newline
- `fopen()` opens a file
- `fclose()` closes a file

Standard streams:
- `stdin` for input
- `stdout` for normal output
- `stderr` for error output

Key idea:
- `stdio.h` declares input/output functions such as `printf()` and `scanf()`
- without it, the compiler does not know those function declarations

## 2026-03-06 - `ex02_output`

Goal:
- practice basic C output using `printf()` and variables

Key concepts:
- `main()` is the program entry point
- `return 0;` means the program finished successfully
- `int` stores integer values
- `char[]` can store a C string
- `printf()` needs the correct format specifier for each argument

Format specifiers used:
- `%d` for `int`
- `%s` for C strings
- `%c` for a single character

Important corrections:
- C does not have a built-in `string` type like Python
- `char name[] = "Matahari Ramadhan";` declares a character array initialized with a string literal
- wrong `printf()` format specifiers can cause undefined behavior

## 2026-03-06 - `ex03_input`

Goal:
- practice reading user input with `scanf()`

Key concepts:
- `scanf()` reads according to its format string
- `%d` reads an `int`
- `&number` passes the address of `number`
- prompts should be printed with `printf()`, not embedded in `scanf()`

Important corrections:
- `scanf("Input number: %d", &number);` is wrong for normal terminal input because it expects literal text
- `scanf("%d", &number);` is the correct basic form for reading one integer
- `scanf()` return values must be checked before using the destination variable

Safety note:
- if `scanf("%d", &number)` does not return `1`, then input failed
- using `number` after failed input can lead to undefined behavior because it may be uninitialized

## 2026-03-06 - `ex04_types`

Goal:
- learn basic C data types and match them with the correct `printf()` format specifiers

Types practiced:
- `int` for whole numbers
- `char` for a single character
- `float` for decimal numbers
- `char[]` for a C string

Correct format specifiers:
- `%d` for `int`
- `%c` for `char`
- `%f` for `float`
- `%s` for `char[]` used as a C string

Important corrections:
- `'a'` is a character literal, but `"a"` is a string literal
- C does not have a built-in `string` type
- using `%c` for a C string is a type mismatch
- `float phi = 3.14f;` is clearer than `float phi = 3.14;` because `3.14f` is a `float` literal

Useful note:
- in `printf()`, `%f` is correct for printing both `float` and `double` values

## 2026-03-07 - safer `scanf()` usage

Key idea:
- `scanf()` returns the number of successful conversions

For this pattern:

```c
scanf("%d", &number);
```

Return values:
- `1` means one integer was read successfully
- `0` means the input did not match `%d`
- `EOF` means the input stream ended or an input error occurred

Safe pattern:

```c
if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
}
```

Why it matters:
- failed input should not be treated as valid input
- if conversion fails, using `number` anyway can lead to undefined behavior because it may be uninitialized

Rule to remember:
- never trust user input
- validate it before using the result

## 2026-03-07 - `ex05_if_else`

Goal:
- practice conditional logic with `if`, `else if`, and `else`

Key concepts:
- compare values with `<`, `>`, and `==`
- use `number`, not `&number`, in comparisons
- `scanf()` format strings need quotes
- validated input should happen before branching on the value

Common mistakes found:
- `scanf(%d, &number);` missing quotes around `%d`
- comparing `&number` instead of `number`
- missing closing parenthesis in `if (...)`
- stray semicolon after the closing brace of the conditional block

## 2026-03-11 - `ex06_loops`

Goal:
- learn how to repeat actions using a `for` loop

`for` loop structure:

```c
for (initialization; condition; update) {
        /* repeated code */
}
```

Execution model:
- initialize
- check condition
- run loop body
- apply update
- repeat

Important loop boundaries:
- `i < 10` stops before `10`
- `i <= 10` includes `10`

Important correction:
- incrementing the loop variable both in the loop body and in the update expression can skip values

Practical rule:
- let the `for` loop manage the iteration variable unless there is a clear reason not to

## 2026-03-11 - `ex07_while_loop`

Goal:
- learn how to repeat actions using a `while` loop

`while` loop structure:

```c
while (condition) {
        /* repeated code */
}
```

Execution model:
- initialize
- check condition
- run loop body
- update state manually
- repeat

Important correction:
- forgetting to update the loop variable inside a `while` loop can cause an infinite loop

Useful comparison:
- `for` loops often read more clearly for counting
- `while` loops often read more clearly for condition-driven repetition

## 2026-03-11 - `ex08_functions`

Goal:
- learn how to define and call functions in C

Function structure:

```c
return_type function_name(parameters) {
        /* code */
        return value;
}
```

Key concepts:
- a function can receive input through parameters
- a function can return a value to the caller
- `main()` can call other functions and use their return values
- parameter types must be declared explicitly in modern C

Important corrections:
- old-style forms like `int doubler(i)` should be treated as wrong for modern C learning
- every `return` statement still needs a semicolon

Practical note:
- if a function only computes and returns a value, return the expression directly when that is clearer

## 2026-03-11 - `ex09_arrays`

Goal:
- learn how to declare arrays, access elements by index, and iterate through them with loops

Key concepts:
- array declaration uses `type name[size]`
- array initialization uses curly braces `{}` 
- array indexing starts at `0`
- loops are the standard way to process array elements one by one

Important corrections:
- C arrays do not have a `.length` property
- initialization uses `{1, 2, 3}`, not `[1, 2, 3]`

Useful pattern:

```c
size_t size = sizeof(numbers) / sizeof(numbers[0]);
```

Important limit:
- this `sizeof(array) / sizeof(array[0])` pattern only works while the variable is still an actual array in the current scope
- after passing it to a function, it usually decays to a pointer and this pattern no longer gives the element count

## 2026-03-11 - `ex10_strings`

Goal:
- learn how strings work in C

Key concepts:
- a C string is typically stored in a `char[]`
- C strings end with a null terminator `'\0'`
- `%s` prints characters until it reaches `'\0'`
- individual characters can be accessed with array indexes

Important warning:
- hardcoding a loop bound like `for (int i = 0; i < 13; i++)` is brittle
- if the string changes length, that loop can become wrong and may read past the array

Safer mental model:
- `%s` depends on the null terminator
- manual character-by-character loops should usually stop based on `'\0'` or a correctly computed size

## 2026-03-13 - `ex11_string_input`

Goal:
- read a full line of text safely into a fixed-size character buffer

Key concepts:
- `fgets()` reads a line into a buffer
- `fgets()` needs three arguments: destination buffer, buffer size, and input stream
- `fgets()` does not use format strings
- the return value of `fgets()` must be checked before using the buffer
- newline trimming can be done by scanning the buffer and replacing `'\n'` with `'\0'`

Important corrections:
- `fgets("%s", *name);` is wrong because `fgets()` does not take a format string and `*name` is a single `char`
- `sizeof name` is better than repeating the literal buffer size like `100`

Behavior note:
- `fgets()` usually keeps the trailing newline if there is room in the buffer
- trimming that newline produces cleaner output for later string handling

## 2026-03-13 - `ex12_structs`

Goal:
- group related values together using a `struct`

Key concepts:
- a `struct` defines a custom data type with named fields
- the struct definition must end with a semicolon
- a struct variable can be initialized with values in field order
- fields are accessed with the `.` operator

Important corrections:
- `struct person;` alone is only an incomplete declaration, not a full definition with fields
- fields like `name` and `age` belong inside the struct definition, not as ad hoc declarations in `main`
- a struct initializer contains values, not new declarations such as `char person.name[] = ...`

Practical note:
- adding a trailing newline to `printf()` keeps shell output readable

## 2026-03-13 - `ex13_functions_with_struct`

Goal:
- pass a struct to a function and use its fields inside that function

Key concepts:
- struct types can be used as function parameter types
- the struct definition must appear before functions that use that type
- field access inside the function still uses the `.` operator
- a function should return `void` when it performs an action but does not produce a value

Important corrections:
- a struct field declaration like `char[] name;` is invalid because array fields need a fixed size
- if a struct definition is wrong, later field accesses and initializers will fail in confusing ways
- function names should match what the function actually does, so `print_person` is clearer than `print_name`

## 2026-03-13 - `ex14_pointers_intro`

Goal:
- understand the basic relationship between a value, its address, and a pointer

Key concepts:
- a pointer stores an address
- `&value` means the address of `value`
- `*ptr` means the value stored at the address held by `ptr`
- `%p` is the correct `printf()` format specifier for addresses

Important corrections:
- `*value` is invalid when `value` is an `int`, because dereference only works on pointer values
- `int *ptr = &value;` is the correct pattern for making a pointer point to `value`
- printing an address with `%p` should use a `void *`, such as `(void *)ptr`

Mental model:
- `value` is the direct value
- `ptr` is the address
- `*ptr` is the indirect value read through that address

## 2026-03-13 - `ex15_pointer_modify_value`

Goal:
- modify a variable through a pointer and observe that the address stays the same while the value changes

Key concepts:
- writing to `*ptr` changes the value stored at the pointed location
- if `ptr` points to `value`, then changing `*ptr` changes `value`
- the pointer value itself can remain unchanged while the underlying data changes

Important corrections:
- `./` means the current directory, not the program file, so the executable must be run as `./main`
- compile flags should stay consistent, including `-Werror`

Mental model:
- `ptr` tells you where the value lives
- `*ptr = 45;` changes what lives there

## 2026-03-13 - `ex16_swap_with_pointers`

Goal:
- swap two integers by passing their addresses into a function

Key concepts:
- C uses pointers, not reference parameters, for this pattern
- the function receives addresses, but the swap must operate on the pointed values
- `a` and `b` are pointers, while `*a` and `*b` are integers
- a temporary integer is needed so the first value is not lost during the swap

Important corrections:
- `int &a, int &b` is C++ syntax, not C
- swapping `a` and `b` would swap addresses, not the caller's integer values
- storing pointer addresses in `int` temporaries is the wrong layer of abstraction

Mental model:
- `a` points to `x`
- `b` points to `y`
- `*a` is the current value of `x`
- `*b` is the current value of `y`
- swapping means exchanging `*a` and `*b`

## 2026-03-13 - `ex17_set_value_with_pointer`

Goal:
- modify a caller variable through a pointer parameter in a simpler pattern than swapping

Key concepts:
- passing `&value` gives the function access to the caller's variable
- the function writes through `*p` to update that variable
- this pattern is structurally similar to a setter, but it is plain C pointer-based mutation, not object-oriented encapsulation

Mental model:
- `p` is the address of the caller variable
- `*p = new_value;` updates what lives at that address

## 2026-03-13 - `ex18_pointer_to_array_first_element`

Goal:
- connect arrays and pointers by showing that a pointer to the first element can access array values

Key concepts:
- in many expressions, an array name acts like a pointer to its first element
- if `int *ptr = numbers;`, then `ptr` points to `numbers[0]`
- `numbers[0]` and `*ptr` refer to the same value
- `numbers[1]` and `*(ptr + 1)` refer to the same value

Important corrections:
- `*ptr + 1` means value arithmetic after dereference
- `*(ptr + 1)` means pointer arithmetic first, then dereference
- pointer arithmetic moves by element size, not by a hardcoded byte count in source code

Mental model:
- `ptr + 1` means “next `int` element”
- `*(ptr + 1)` means “value of the next `int` element”

## 2026-03-13 - `ex19_array_interaction_with_pointer`

Goal:
- iterate through an array and prove that `numbers[i]` matches `*(ptr + i)`

Key concepts:
- pointer arithmetic can be combined with a loop index
- `*(ptr + i)` means move `i` elements forward, then dereference
- array indexing and pointer arithmetic can refer to the same array element

Important corrections:
- `sizeof numbers` gives total bytes, not the number of elements
- using `i < sizeof numbers` as the loop bound causes out-of-bounds access
- the correct element count is `sizeof numbers / sizeof numbers[0]`

Tooling lesson:
- AddressSanitizer correctly caught the out-of-bounds access when the loop bound was wrong

## 2026-03-13 - `ex20_sum_array_with_pointer`

Goal:
- use a pointer and an element count inside a function to process an array and return a result

Key concepts:
- once an array is passed into a function, the function receives a pointer, not the full array object
- the element count should be computed in the caller while the variable is still an actual array
- `*(ptr + i)` can be used inside a loop to access each element through the pointer

Important note:
- a size/count parameter is better represented as `size_t` than `int`

Mental model:
- the pointer says where the first element is
- the count says how many valid elements may be read

## 2026-03-13 - `ex21_malloc_intro`

Goal:
- allocate memory on the heap for one integer, use it safely, and free it

Key concepts:
- `malloc()` allocates raw memory and returns a pointer
- the allocation result must be checked against `NULL`
- `sizeof *ptr` is based on the pointer's pointed type, not the pointer's runtime value
- heap memory allocated with `malloc()` should be released with `free()`

Important corrections:
- `printf()` still requires `<stdio.h>`
- `free(ptr);` is a function call and needs parentheses
- after `free(ptr);`, setting `ptr = NULL;` can be a useful defensive cleanup in longer-lived code

Mental model:
- `malloc()` gives you heap storage
- `*ptr` accesses the integer stored in that allocated memory

## 2026-03-17 - `ex22_malloc_array`

Goal:
- allocate a dynamic array on the heap, fill it, print it, and free it safely

Key concepts:
- dynamic arrays allocated with `malloc()` must be sized with `count * sizeof *ptr`
- heap arrays cannot be initialized with brace syntax after allocation
- once memory is allocated, elements must be assigned one by one or in a loop
- after `free(numbers);`, the pointer variable itself may be set to `NULL`, but the freed memory must not be accessed

Important corrections:
- `*numbers = {10, 20, 30, 40, 50};` is invalid because `*numbers` is one `int`, not an array initializer target
- `*numbers = NULL;` is wrong after `free()` because `*numbers` is an `int`; the pointer variable is `numbers`
- `*numbers[i]` is a precedence mistake because `numbers[i]` is already an `int`

Mental model:
- `numbers` points to the first heap-allocated element
- `numbers[i]` accesses the `i`th element in that allocated block

## 2026-03-17 - `ex24_malloc_string_buffer`

Goal:
- allocate a string buffer on the heap and use it as a real C string

Key concepts:
- heap strings should use `char *`, not `int *`
- a C string still needs a null terminator when stored on the heap
- `%s` requires a `char *` that points to a valid null-terminated string

Important corrections:
- using `int *` appeared to work with `%c` because character constants are small integer values
- the wrong type model was exposed when `%s` failed, because `%s` expects `char *`, not `int *`
- “it compiled and ran once” is not enough; the underlying data model still has to be correct

Mental model:
- a heap string is just a dynamically allocated `char` buffer ending in `'\0'`

## 2026-03-17 - `ex25_use_after_free_demo`

Goal:
- deliberately trigger and then correct a use-after-free mistake in a tiny heap program

Key concepts:
- after `free(ptr);`, the memory is no longer valid to dereference
- the pointer variable may still hold an old address value, but that does not make the pointee valid
- `ptr = NULL;` is a defensive cleanup to avoid accidental reuse of a stale address

Important corrections:
- `*ptr = 100;` after `free(ptr);` is a use-after-free bug
- with strict warnings, the compiler may catch the bug before runtime

Mental model:
- `free(ptr);` ends your right to use the pointed memory
- `ptr = NULL;` does not restore the memory; it only makes the stale pointer obvious

## 2026-03-17 - `ex26_realloc_intro`

Goal:
- grow a heap-allocated integer array safely with `realloc()`

Key concepts:
- `realloc()` may grow the existing block in place or move the data to a new block
- if `realloc()` fails, it returns `NULL` and the original pointer remains valid
- the safe pattern is to store the `realloc()` result in a temporary pointer first
- newly added elements after growth still need explicit initialization

Important corrections:
- assigning the result of `realloc()` directly to `numbers` is risky because a failure would lose the original pointer
- the old values are preserved only if `realloc()` succeeds; failure must still clean up the original allocation explicitly
- growing the block does not initialize the new slots automatically

Mental model:
- `realloc()` is a resize request, not always a brand-new allocation
- use `temp` to hold the resize result, then replace `numbers` only after success


## 2026-03-17 - `ex27_manual_reallocation`

Goal:
- manually grow a heap-allocated integer array without using `realloc()`

Key concepts:
- manual reallocation means allocate a new larger block, copy old values, free the old block, then reassign the pointer
- the old block must remain valid until copying is finished
- both success paths and failure paths must free the correct allocations
- newly added elements must be initialized before use

Important corrections:
- overwriting `numbers` with `temp` before freeing the original block would lose the only pointer to the old allocation and leak memory
- returning on `temp == NULL` without freeing `numbers` leaks the original allocation
- filling only up to `i < new_count - 1` left the last element uninitialized, which produced garbage output

Mental model:
- `numbers` owns the original heap block
- `temp` is a separate larger block used as the replacement
- copy old elements first, initialize the new ones, free the old block, then transfer ownership to `numbers`

## 2026-03-17 - `ex28_file_io_intro`

Goal:
- open a file, write text into it, and close it safely

Key concepts:
- `fopen()` returns a `FILE *`
- opening with `"w"` creates or overwrites a text file for writing
- `fprintf()` writes formatted output to a file stream
- `fclose()` must be called after a successful open

Important corrections:
- file opening can fail, so `fopen()` must be checked against `NULL`
- this exercise generates `output.txt`, so `clean` should remove it along with `main`
- file output formatting still matters; `Number: %d` is clearer than `Number:%d`

Mental model:
- a `FILE *` is a handle to an opened file stream
- `fprintf(file, ...)` is `printf()` directed into that stream instead of the terminal

## 2026-03-17 - `ex29_gdb_intro`

Goal:
- learn the basic `gdb` workflow: breakpoints, stepping, and variable inspection

Key concepts:
- `break main` sets a breakpoint at `main()`
- `run` starts the program under the debugger
- `next` executes the current source line without entering called functions
- `step` enters a called function
- `finish` runs until the current function returns to its caller
- `print name` shows the current debugger-visible value of a variable

Important corrections:
- when `gdb` stops on a line like `int y = 32;`, that line has not executed yet
- printing `y` before the assignment line runs does not mean `y` is meaningfully initialized
- debugger output for not-yet-assigned variables must not be treated as trustworthy program state

Mental model:
- the highlighted line in `gdb` is the next line to execute
- variable assignments only take effect after their assignment line runs

## 2026-03-17 - `ex30_gdb_assignment_timing`

Goal:
- understand exactly when a variable changes while stepping through code in `gdb`

Key concepts:
- `gdb` stops before the highlighted line executes
- `next` runs the current line and stops at the following line
- a variable only reflects an assignment after that assignment line has run
- `gdb` result labels like `$1`, `$2` are debugger history values, not program variables

Important corrections:
- seeing `0` for `x` at `int x = 1;` did not mean uninitialized variables are reliably zero
- it only showed that the assignment had not executed yet
- debugger-visible values before assignment must not be treated as trustworthy program state

Mental model:
- stop on a line: the line has not run yet
- `next`: now the line has run, and the variable state can change

## 2026-03-17 - `ex31_valgrind_demo`

Goal:
- use `valgrind` to detect a memory leak, then fix the program and verify the leak is gone

Key concepts:
- `valgrind --leak-check=full ./main` runs Memcheck on the program
- `definitely lost` means leaked memory with no remaining live pointer to it
- `valgrind` should be used with a plain debug build, not with AddressSanitizer enabled
- after adding the missing `free()`, the heap summary should show matching allocs and frees

Important corrections:
- running `valgrind` on an ASan build produced invalid results and a runtime warning
- `valgrind --leak-check=full` without a program path is incomplete and does nothing useful
- the first correct run showed `4 bytes definitely lost in 1 blocks`
- after `free(ptr);`, the follow-up run showed `All heap blocks were freed`

Mental model:
- `valgrind` inspects how your program uses memory at runtime
- leak reports compare allocations against frees and tell you what was never released

## 2026-03-17 - `ex32_file_read_intro`

Goal:
- open a text file for reading, read it line by line, print each line, and close the file safely

Key concepts:
- `fopen("input.txt", "r")` opens a file for reading
- `fgets(buffer, sizeof buffer, file)` reads one line at a time from a file stream
- a `while` loop with `fgets(...) != NULL` is the standard beginner pattern for line-by-line reading
- file-open failure should be reported and return a non-zero status

Important corrections:
- testing with `echo "...\n..."` wrote literal `\n` text instead of real newlines in this shell
- `printf` or `cat > input.txt` is more reliable when creating test files with exact line breaks
- `main` is not found by the shell without `./`; executables in the current directory must be run as `./main`

Mental model:
- `fgets()` keeps reading until it reaches end-of-file or failure
- each successful `fgets()` call fills the buffer with one line from the file

## 2026-03-22 - `ex33_debug_memory_bug_end_to_end`

Goal:
- reproduce a real memory bug, inspect the failure signal, identify the root cause, fix it, and verify the corrected program

Key concepts:
- AddressSanitizer can identify heap buffer overflows precisely, including the failing line and the allocation site
- valid indexes for a `count`-element allocation are `0` through `count - 1`
- an off-by-one loop bound like `i <= count` can write one element past the heap block
- `valgrind` must be run on a non-ASan build to be meaningful

Important corrections:
- the bug was a heap-buffer-overflow caused by writing `numbers[count]`
- the failing statement was a write, not a read
- the ASan report showed the write happened exactly at the byte right after the 20-byte allocation
- running `valgrind` on the ASan build produced invalid results and did not count as useful verification
- changing the loop bound from `i <= count` to `i < count` fixed the bug

Mental model:
- allocation size defines the legal index range
- debugging end-to-end means: reproduce, inspect, explain, fix, and rerun cleanly

## 2026-03-23 - `project01_password_generator` v1

Goal:
- build the first Phase 1 project: a CLI password generator that validates length input, generates a password from a fixed charset, and prints it as a valid C string

Key concepts:
- input validation must first check whether `scanf()` successfully parsed an integer
- user-controlled lengths need both lower and upper bounds before using them for array sizing
- a generated password printed with `%s` must have room for a null terminator and must place `'\0'` at the correct final index
- array-index ranges must be derived from the real charset length, not from a stale hardcoded count
- random-output programs are best tested by checking properties like exit status, output length, and allowed characters
- once manual testing becomes repetitive, a small shell test script is a practical upgrade
- editor/formatting friction can become a real productivity constraint even when the program logic is small
- `gdb` can inspect a partially built character buffer byte-by-byte with `display` and `x/9cb password`
- raw array bytes and valid C string interpretation are different things
- debugger expressions that call functions like `rand()` are not neutral observations; they can change program state
- shell behavior matters during testing, especially for `echo`, `printf`, `cat > file`, and `./main`

Important corrections:
- comparing `password_length` to `NULL` was a type error because `password_length` is an `int`, not a pointer
- checking `password_length == 0` was not enough to validate input; the real first check was the return value of `scanf()`
- the password initially printed extra garbage characters because the array was not null-terminated before `%s` printing
- placing `'\0'` at `password[password_length - 1]` truncated the password by overwriting the last generated character
- a hardcoded charset length created an out-of-bounds read risk when the actual charset contents changed
- the first test script failed to extract the password because the program prompt and result shared one output line when input was piped
- manual testing became tedious enough that adding `test.sh` was justified, not premature
- formatting code in `nano` became painful enough to motivate adding `clang-format` and a short alias
- byte-level `gdb` inspection showed the password buffer contents before it was a valid string
- extra trailing characters appeared because `%s` kept reading past the intended password until it found `'\0'`
- `print rand() % total_charset` was identified as a bad inspection pattern because it would consume another random value
- `echo "...\n..."` wrote literal `\n` text in this shell, while `printf` or `cat > file` created real line breaks
- `main` failed but `./main` worked because the shell does not search the current directory by default
- `nano` was kept for now, while `vim` was postponed rather than forced early

Mental model:
- generated characters occupy indexes `0` through `password_length - 1`
- the null terminator belongs at `password[password_length]`
- tests for random programs should verify shape and constraints, not exact values
- when workflow pain becomes repetitive, small tooling upgrades are part of disciplined engineering, not a distraction
- `print password` asks `gdb` to interpret the buffer as a string, while `x/9cb password` shows the raw bytes directly

## 2026-03-23 - `ex34_xor_intro`

Goal:
- understand the reversible property of XOR before starting the XOR file tool project

Key concepts:
- XOR uses the `^` operator in C
- XOR compares bits position by position
- applying the same XOR key twice restores the original value
- this makes XOR useful as a simple reversible byte transformation

Important correction:
- calling the result “encrypted” is acceptable for learning, but this toy example is not secure encryption by itself

Mental model:
- if `encrypted = value ^ key`, then `encrypted ^ key` returns the original value

## 2026-03-25 - `project02_xor_file_tool` checkpoint 1

Goal:
- start the second Phase 1 project: read an input file, apply XOR with a key, and write the transformed output to another file

Key concepts:
- line-based user input was moved toward safer handling with `fgets`, newline trimming, and leftover-input flushing
- `scanf` and `fgets` interact differently with `stdin`, especially around leftover newlines
- path expansion with `~` is not handled by `fopen` automatically and must be done in program logic if desired
- binary-oriented file processing should eventually use `fread` and `fwrite`, not just `fgets`
- raw-byte file buffers should prefer `unsigned char`
- embedded `'\0'` bytes inside file data must be treated as ordinary bytes, not as string terminators
- file-size comparison tools like `wc -c` and bytewise comparison tools like `cmp` are useful break tests for file tools

Important corrections:
- after `scanf("%d", &key)`, the leftover newline remained in `stdin`, which caused the next `fgets` call to read an empty line
- using `gdb` to call `getchar()` changed the input stream state, so debugger inspection itself affected the bug
- trying to apply `trim_newline` to an `int` key was conceptually wrong because the newline was still in `stdin`, not inside the integer variable
- using `fgets` with a single `char` key buffer was invalid because there was no room for both input and the null terminator
- `convert_to_home` originally used `sizeof home` even though `home` was a pointer, not an array
- `convert_to_home` also originally truncated the path by expanding `~` but losing the remaining suffix
- successful `fopen` calls must be paired with `fclose` before returning on later failures
- `fgets` on the opened file only reads one text line, not the whole file
- the encrypted output showed unstable trailing garbage because the encrypted buffer was not a proper null-terminated C string for `%s` printing
- the first XOR loop wrongly stopped at `'\0'`, which caused files containing embedded null bytes to be truncated during processing
- the current implementation still reads only one chunk, so a 300-byte file produced 256-byte encrypted and decrypted outputs

Mental model:
- string buffers need both size-aware handling and `'\0'`-aware handling
- input helpers should first work correctly, then be wrapped into cleaner higher-level functions
- this checkpoint is a working step in the project, not the final binary-safe XOR tool yet
- for binary file processing, the number of bytes read (`nread`) is the boundary that matters, not string terminators

## 2026-03-29 - `project02_xor_file_tool` checkpoint 2

Goal:
- move the XOR tool from string-oriented key handling toward a cleaner numeric key model and confirm whole-file chunked processing works

Key concepts:
- `strtol` is the right standard-library tool for parsing a numeric key from text input
- `strtol` does not report failure with just return value `0`; parsing validity must be checked with `endptr`
- a byte-oriented XOR tool should use a numeric key type such as `unsigned char`, not an ASCII character from a short string buffer
- repeated `fread`/`fwrite` in a loop is the right whole-file pattern; one `fread` is only one chunk
- retry loops should distinguish retryable input-too-long cases from hard input-read failures

Important corrections:
- treating `key[0]` from a tiny string buffer as the XOR key was the wrong model because it encoded an ASCII character, not a validated numeric byte value
- checking `read_input(...) != 0` without branching by status caused bad retry-loop logic; only the too-long case should retry
- the helper contract for `read_input` became clearer after returning distinct statuses for read failure, too-long input, and zero-capacity misuse
- moving from a single-read design to a chunk loop fixed the earlier 300-byte test truncation; `big.txt`, `big.enc`, and `big.dec` all reached 300 bytes and `cmp big.txt big.dec` succeeded

Mental model:
- input acquisition and semantic validation are separate layers: `read_input` gets a clean line, `strtol` interprets it as a number
- one `fread` call reads one chunk, not the whole file
- the chunk boundary is `nread`, and the program should process and write exactly those bytes each iteration

## 2026-03-30 - `project02_xor_file_tool` v1

Goal:
- finish a usable v1 of the XOR file tool with safer interactive input handling, early input-file validation, numeric key parsing, and whole-file chunked processing

Key concepts:
- the input file should be opened immediately after the path is entered so bad paths fail fast before asking for later inputs
- `switch` works well for handling explicit `read_input` status codes because the retryable and fatal cases are different
- `strtol` is the right parser for turning text input into a numeric key
- chunked `fread`/`fwrite` is the correct whole-file pattern for a byte-oriented tool
- `fwrite` must be checked against `nread`, and `ferror(file)` must be checked after the read loop

Important corrections:
- a giant `while (...)` condition that combined reading, `~` conversion, and `fopen` was rejected because it was hard to reason about and broke under normal control-flow analysis
- the input-file flow was reordered so the program opens the input file before asking for the key and output filename
- the key path was changed from an ASCII-character-style model to `strtol` parsing with explicit validation
- the whole-file loop now writes exactly the number of bytes read each iteration and checks for write failures and stream read errors

Mental model:
- `read_input` acquires a clean line; later code decides what that line means
- retry only the retryable case; fail fast on hard input/read errors
- a finished v1 does not need every cosmetic cleanup solved, but it does need the core behavior to be coherent and testable
