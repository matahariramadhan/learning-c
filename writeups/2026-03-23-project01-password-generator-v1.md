# project01_password_generator v1

## Goal

Build the first Phase 1 project: a small password generator that reads a desired length, validates the input, generates random characters from a fixed charset, and prints the result as a valid C string.

## High-Value Mistakes

This project exposed several real beginner bugs in sequence.

### 1. Wrong validation target

The first version tried to do this:

```c
if (password_length == NULL) {
```

Why that was wrong:
- `password_length` is an `int`
- `NULL` is a null pointer constant
- the real thing to validate first was whether `scanf()` successfully parsed an integer

That was corrected by checking the return value of `scanf()`.

### 2. Missing null terminator

An early version generated characters into the array and printed with:

```c
printf("Your password: %s\n", password);
```

But the array was not properly null-terminated.

Symptom:
- `gdb` showed the password bytes were followed by unrelated memory
- runtime output included extra characters after the intended password

Root cause:
- `%s` prints until it reaches `'\0'`
- without a terminator, it keeps reading past the intended password bytes

This was made visible with `gdb` by inspecting the buffer byte-by-byte:
- `display i`
- `display password[i]`
- `x/9cb password`

That inspection made the difference explicit between:
- raw bytes inside the array
- a valid C string interpretation

At that stage, the buffer had allocated space, but it was not yet a proper null-terminated string.

### 3. Null terminator placed at the wrong index

Another revision used:

```c
password[password_length - 1] = '\0';
```

Why that was wrong:
- it overwrote the final generated character
- the printed password became one character shorter than requested

Correct model:
- generated characters go in indexes `0` through `password_length - 1`
- the terminator belongs at `password[password_length]`

### 4. Charset length mismatch

At one point the code used a hardcoded charset length while the actual array contents had changed.

Why that was dangerous:
- random indexes could go past the real end of the charset array
- that creates an out-of-bounds read risk

That was corrected by deriving the usable charset length from the actual array.

### 5. Test extraction bug

The first shell test expected `Your password:` to begin a line.

That failed because:
- the prompt did not end with a newline
- when input was piped, the password output continued on the same line as the prompt

The test script was then adjusted to extract the password more robustly.

### 5a. A debugger inspection trap

At one point, the natural idea was to inspect:

```gdb
print rand() % total_charset
```

That is a bad debugging pattern here.

Why:
- `rand()` has side effects
- evaluating it in `gdb` consumes another pseudo-random value
- that means the debugger changes the program state instead of only observing it

The safer inspection pattern was:
- step over the assignment
- inspect `password[i]` after the value had already been written

### 6. Manual testing stopped scaling

At first the program was tested by repeatedly typing values into the terminal.

That became painful for two reasons:
- the same input cases had to be retyped over and over
- random output made visual checking slower and less trustworthy

That pain was a useful signal:
- automation was justified
- a small shell test script was the right level of tooling

The project then gained a `test.sh` that checked:
- invalid input cases
- exit behavior
- generated password length
- allowed character set

### 7. Formatting friction was real

Coding the project in `nano` exposed a workflow problem:
- no syntax highlighting
- no built-in formatting
- repeated manual cleanup was annoying

That did not block the project, but it was still a real engineering lesson:
- tooling friction affects momentum
- adding `clang-format` and a short alias was a reasonable response
- not every improvement has to wait until “later”

Another workflow choice was made deliberately:
- `nano` was kept for now
- `vim` was postponed instead of forcing an editor migration in the middle of the project

That was a reasonable tradeoff for momentum.

### 8. Shell behavior mattered

This project also surfaced useful shell-side lessons:

- `echo "...\n..."` did not create real newlines in this shell invocation
- `printf` was the more reliable way to generate exact newline-separated test input
- `cat > file` worked because `cat` copies from standard input to standard output, and shell redirection changed the output destination
- `main` failed while `./main` worked because the shell does not search the current directory by default

## Working Version

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int password_length;
	int max_password_length = 30;

	printf("===Password Generator===\npassword lenght: ");
	if (scanf("%d", &password_length) != 1) {
		printf("invalid input\n");
		return 1;
	}

	if (password_length < 1) {
		printf("Minimum password length is 1\n");
		return 1;
	}

	if (password_length > max_password_length) {
		printf("Max password length is %d\n", max_password_length);
		return 1;
	}

	srand((unsigned int)time(NULL));

	char password[password_length + 1];
	char charset[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'k', 'l', 'm',
	                  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
	                  'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	                  'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
	                  'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1',
	                  '2', '3', '4', '5', '6', '7', '8', '9', '0'};

	for (int i = 0; i < password_length; i++) {
		password[i] = charset[rand() % (sizeof charset / sizeof charset[0])];
	}

	password[password_length] = '\0';

	printf("Your password: %s\n", password);
	return 0;
}
```

## Test Script Outcome

The shell test script verified:
- non-numeric input fails
- zero fails
- negative length fails
- too-large length fails
- valid input succeeds
- generated password has the requested length
- generated password contains only allowed characters

Observed result:

```text
PASS: non-numeric input
PASS: zero length
PASS: negative length
PASS: too-large length
PASS: valid password generation
All tests passed
```

## Lessons Learned

- validate parsing before validating numeric range
- `%s` output requires a real null-terminated C string
- for random generation, array bounds must match the actual array contents
- debugging with `gdb` can reveal when an array is not yet a valid string
- `gdb` byte-level inspection is useful when string printing is misleading
- do not inspect side-effecting expressions like `rand()` by calling them again inside the debugger
- shell tests are a practical first testing layer for CLI programs
- random-output programs should be tested by constraints, not exact output
- when manual testing becomes repetitive, automation is the disciplined next step
- tooling pain is worth recording because it affects code quality and iteration speed
