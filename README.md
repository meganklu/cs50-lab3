# Lab 3 - Megan Lu
COSC050, 26S

## Book Library
- [books.c](books.c): C program with a Book struct and Library struct, along with functions `displayBooks`, `addCopies`, and `findByAuthor` that use the structures. `main` tests the implemented functions. 

Note: [books.c](books.c) can be compiled with the flag `-DDEBUG` to print additional information (e.g., memory addresses) to stdout:
```bash
mygcc -DDEBUG books.c -o books
```

## String Functions
- [string.c](string.c): C program that implements the functions `mystrcat`, `mystrcpy`, and `mystrlen` that match the prototypes described in `string.h` standard library for `strcat`, `strcpy`, and `strlen`.
- [test.c](test.c): C program that tests the [string.c](string.c). The file imports the file with `#include "string.c"`. Compile and run this file to check test cases for the code:

```bash
mygcc test.c -o test
```

### Test Cases
- `mystrcat`
    - Basic append of "Hello " and "world!"
    - Append to empty string
    - Append empty string
- `mystrcpy`
    - Basic copy of "Batman" into buffer
    - Overwriting buffer multiple times
    - Copying the empty string
- `mystrlen`
    - Basic string with spaces for "Hello world!"
    - Empty string
    - String with special characters
    - String with null terminating character "Hello\0world!"
