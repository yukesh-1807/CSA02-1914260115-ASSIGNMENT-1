# Task 12 – Day-4 Design Challenge
## A. Impact Analysis (2 Marks)

### 1. What has changed from the original problem?

The smart meter now sends one watt-hour reading every 15 minutes, giving 35,040 readings per house in a non-leap year. Electricity consumed between 6 PM and 10 PM costs 20% more than the normal tariff. The tariff values must also be changeable without recompiling the program.

The design must therefore process frequent readings, identify peak-hour consumption, calculate yearly energy totals, and load the tariff from an external configuration file.

### 2. Which data types are no longer sufficient?

- **Watt-hour readings and yearly totals:** Use `long long` for large accumulated integer values.
- **Tariff rates and bill amounts:** Use `double` for tariff rates and monetary calculations.
- **Reading count:** Use an integer type capable of storing 35,040 readings.

### 3. Which constants can no longer be fixed with `#define`?

Tariff prices should not be fixed using `#define` because the board requires tariff changes without recompilation. Store the normal tariff in an external file named `tariff.txt` and read it when the program starts.

Calculate the peak tariff as:

`peak tariff = normal tariff × 1.20`

The peak period is 6 PM to 10 PM. The program can use time-based logic to identify these readings and apply the appropriate rate.

### Proposed Design Changes

1. Read the normal tariff from `tariff.txt`.
2. Read smart-meter readings from `readings.txt`.
3. Treat readings as consecutive 15-minute intervals starting at midnight.
4. Apply a 20% higher tariff to readings between 6 PM and 10 PM.
5. Use `long long` for accumulated watt-hour totals.
6. Use `double` for tariff and bill calculations.
7. Change the tariff by editing `tariff.txt`, without recompiling the program.

### Conclusion

The design must be modified to support frequent readings, peak-hour billing, large yearly totals, and configurable tariffs. These changes improve flexibility, accuracy, and maintainability.
