# Task 11 – Recommend and Defend the Final Design

## 1. Recommended Data Types

The following data types are recommended for the electricity billing system:

| Data | Recommended Type | Reason |
|---|---|---|
| Household number | `int` | Stores household identification numbers. |
| Meter readings | `unsigned short` | Stores non-negative readings up to 65,535 on a typical 16-bit type. |
| Units consumed | `unsigned int` | Stores non-negative electricity consumption. |
| Tariff rates and bill amounts | `long` or `long long` | Stores larger billing values; integer paise avoids floating-point rounding errors. |

The program should validate inputs and handle meter rollover correctly. The exact ranges of integer types should be checked on the target compiler.

## 2. Tariff Revision

If tariff rates are defined using `#define`, changing a rate requires editing the source code, recompiling the program, and distributing the new executable.

A better approach is to store tariff values in a configuration file such as `tariff.txt`. The program reads the values when it starts. A tariff revision then requires changing the configuration file instead of recompiling the program.

The program must validate the file to ensure that the values are numeric, positive, and within acceptable limits.

## 3. Limitations of the Design

- Incorrect or missing input can produce errors unless it is validated.
- Meter rollover and meter replacement must be handled correctly.
- Integer calculations can overflow if the selected type is too small.
- Floating-point arithmetic can cause rounding differences in financial calculations.
- Tariff changes must be validated before they are used.

For financial accuracy, storing monetary amounts as integer paise is preferable.

## 4. Correctness at District Scale

The co-operative serves approximately 4,000 households. The program should process each household's readings and calculate its bill independently.

For one household, the calculation requires a fixed number of operations, so its time complexity is O(1). For 4,000 households, the total time complexity is O(n), where n is the number of households. The memory requirement can remain O(1) per household when records are processed one at a time.

The design is suitable for this scale in principle, provided that input validation, correct tariff calculations, and overflow checks are implemented. Actual performance should be confirmed by running tests with representative data for all 4,000 households.

## 5. Alternative Concept and Complexity Analysis

An alternative is to read tariff values from a configuration file at program startup instead of compiling them into the program.

| Factor | Compile-Time Constants | Configuration File |
|---|---|---|
| Tariff revision | Requires recompilation | Edit the file |
| Startup time | No file-reading overhead | Reads and validates tariff values |
| Time complexity | O(1) to access constants | O(k) to read k tariff values |
| Extra memory | O(1) | O(k) to store k tariff values |
| Distribution | New executable may be needed | Updated configuration file can be distributed |

For a small number of tariff values, the startup time and memory overhead of reading a configuration file are negligible. This makes configuration files more convenient when tariffs change frequently.

## 6. Experimental Evidence and Testing

The following tests should be conducted and their actual results recorded before submission:

| Test | Input or Setup | Expected Result |
|---|---|---|
| Normal billing | Valid previous and current readings | Correct units and bill |
| Boundary testing | Readings around tariff slab limits | Correct slab charges |
| Meter rollover | Previous reading 65,400; current reading 120 | 256 units consumed |
| Invalid input | Negative or non-numeric reading | Error message |
| District-scale test | Process 4,000 household records | All valid records processed correctly |
| Tariff revision | Change tariff in the configuration file | New tariff used without recompilation |

**Note:** Expected results are not proof that the tests have been executed. Record actual outputs and measured timings after running the tests.

## 7. Conclusion

The recommended design uses suitable integer types, validates inputs, handles meter rollover, and stores monetary values carefully. Configuration files make tariff revisions easier because recompilation is unnecessary for tariff changes. The design can support approximately 4,000 households when implemented with proper validation, overflow protection, and verified testing.
