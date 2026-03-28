# ex13_functions_with_struct

## Goal

Pass a struct into a function and print its fields from inside that function.

## Initial Problems

Initial attempt:

```c
#include <stdio.h>

struct Person {
        char[] name;
        int age;
};

int print_name(struct Person orang) {
        printf("The person's name is: %s, he/she is %d years old\n", orang.name, orang.age);
        return 0;
};

int main(void) {
        struct Person person = {"Matahari Ramadhan", 26};
        print_name(person)
        return 0;
};
```

Problems:
- `char[] name;` is invalid because an array field needs a size
- the broken struct definition caused later field and initializer errors
- the function call was missing a semicolon
- the function name did not match its behavior because it printed both name and age
- the function returned `int` even though the return value was never used

## Working Version

```c
#include <stdio.h>

struct Person {
        char name[30];
        int age;
};

void print_person(struct Person orang) {
        printf("The person's name is: %s, he/she is %d years old\n", orang.name, orang.age);
}

int main(void) {
        struct Person person = {"Matahari Ramadhan", 26};
        print_person(person);
        return 0;
}
```

## Lessons Learned

- struct fields must be declared with complete types
- struct types can be passed directly into functions
- fields are accessed with the `.` operator inside and outside functions
- `void` is the right return type for functions that do not return a value
- function names should describe the real behavior
