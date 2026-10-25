# Task 5 – Organise the Program with Header Files and Conditional Compilation

## Objective
Organise billing constants and function prototypes in a custom header file, implement the functions in a separate C file, and use conditional compilation to print intermediate values only in debug builds.

## Files
- `main.c` — reads input, calls the billing functions, and prints the bill.
- `billing.h` — defines `TAX_RATE` and `MAX_ITEMS`, declares the functions, and uses include guards.
- `billing.c` — implements subtotal, tax, and total calculations.

## Program structure and header details
The program separates declarations from implementations: `main.c` contains `main()`, `billing.h` contains shared macros and function prototypes, and `billing.c` contains function definitions. The `BILLING_H` guard prevents the header from being processed more than once in a translation unit.

Use `#include "billing.h"` for this project header. Quoted includes search the source file's directory first; angle-bracket includes such as `#include <stdio.h>` are conventionally used for system headers.

The `#ifdef DEBUG` block is compiled only when `DEBUG` is defined. It prints intermediate values in debug builds and adds no debug-print statements to a normal build.

## Compile commands (GCC)
Run these commands from inside the `Task05` folder.

Normal build:
```sh
gcc -std=c11 -Wall -Wextra -Werror main.c billing.c -o billing
```

Debug build:
```sh
gcc -std=c11 -Wall -Wextra -Werror -DDEBUG main.c billing.c -o billing-debug
```

## Execution
Linux/macOS/GCC terminal:
```sh
./billing
./billing-debug
```

In Dev-C++, add both `main.c` and `billing.c` to the project and keep `billing.h` in the same folder. To enable debug output, add `-DDEBUG` to the compiler options; otherwise build normally. If using the command line, run the exact GCC commands above in the folder.

## Test cases and verified results
Tests were run with GCC using `-std=c11 -Wall -Wextra -Werror`.

| Test | Input | Expected/observed result |
|---|---|---|
| Normal build, ordinary bill | Quantity `3`, unit price `100` | Subtotal `300.00`, tax `15.00`, total `315.00`; no debug lines |
| Debug build, ordinary bill | Quantity `3`, unit price `100` | Same totals, plus debug lines for quantity, unit price, subtotal, and tax |
| Invalid quantity | Quantity `101` | Prints invalid quantity message and exits without calculating a bill |

The ordinary and debug builds compiled successfully with warnings treated as errors. Both executed successfully for the ordinary bill test. The invalid-quantity test produced the expected validation message.

## Runtime-variable alternative (complexity note)
A runtime check such as `if (debug) printf(...)` executes a condition check whenever control reaches it, and the debug code remains in the executable. With `#ifdef DEBUG`, the preprocessor removes the debug statements from a normal build, so there is no runtime condition or debug-print code in that executable. A runtime flag is more flexible when debug mode must be switched on without recompiling.
