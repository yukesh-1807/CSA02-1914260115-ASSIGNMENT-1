# CSA02-1914260115-ASSIGNMENT-1
C Programming – Assignment 1 (CO1)

## Student Details
- Name: Yukesh Babu V
- Register Number: 1914260115
- Department: Mechanical Engineering
- College: SIMATS

## Development Environment
- IDE used: Dev-C++
- Compiler: The C compiler configured in Dev-C++ (the exact compiler/version depends on the installation)
- Compile and run: Open the required `.c` file in Dev-C++ and use **Compile & Run**.
- Alternative: If GCC is installed, compile with `gcc filename.c -o output` and run `./output` (or `output.exe` on Windows).

## Assignment Details
- Assignment: 1
- Subject: C Programming
- Course Outcome: CO1
- Total Marks: 50
- Total Tasks: 12

## Repository Structure
- `Task01` – Program, input and output
- `Task02` – Program, input and output
- `Task03` – Program, input and output
- `Task04` – Program, input and output
- `Task05` – Header files and conditional compilation; billing program
- `Task06` – Program, input and output
- `Task07` – Program, input and output
- `Task08` – Program, input and output
- `Task09` – Program, input and output
- `Task10` – Program, input and output
- `Task11` – Design recommendations for the electricity billing program
- `task 12` – Smart Meter Design Challenge, including readings and design analysis

## Task 5 – Build and Run
The Task 5 program is split into `main.c`, `billing.c`, and `billing.h`. In Dev-C++, add both `main.c` and `billing.c` to the same project and keep `billing.h` in the same folder. Build the project together; compiling only `main.c` will not link the billing functions.

For GCC, run these commands from the Task 5 folder:

Normal build:
```sh
gcc -std=c11 -Wall -Wextra -Werror main.c billing.c -o billing
```

Debug build:
```sh
gcc -std=c11 -Wall -Wextra -Werror -DDEBUG main.c billing.c -o billing-debug
```

## Execution Steps
1. Open the required task folder.
2. Open the source file or project in Dev-C++.
3. Include all required source files in the project before compiling.
4. Use **Compile & Run**.
5. For programs that read input files, keep those files in the program's working directory.
6. Compare the program output with the task's expected result and keep a genuine screenshot of the run.

## Task Descriptions and Results
See each task folder for its program and task-specific notes. Task 5 documents the normal build, debug build, and validation test cases in `Task05/README.md`. Task 11's design recommendations are documented in `Task11/README.md`. The Smart Meter Design Challenge analysis is in `task 12/README.md`.

## Submission Checklist
- Confirm each of the 12 tasks has the required source files and any required input files.
- Compile and run each program in Dev-C++ and capture genuine output screenshots.
- Check that each screenshot matches the actual program output.
- Keep README instructions consistent with the files and compiler used.

This repository is for C Programming Assignment 1 (CO1). Verify the files and runtime screenshots for every task before submission.
