# Task 12 – Smart Meter Design Challenge

## A. Impact analysis

A 15-minute interval gives 4 readings/hour × 24 hours/day × 365 days = **35,040 readings** in a non-leap year. The program streams values one at a time, so it does not need an array holding all readings.

Tariffs and bills use `double`; integer watt-hour readings and yearly accumulators use `long long`. A 32-bit signed `int` tops out at 2,147,483,647. Under the stated assumption of at most 100,000 Wh per interval, the yearly upper bound is 35,040 × 100,000 = **3,504,000,000 Wh**, which exceeds that limit. C guarantees minimum type ranges, so production builds should check target type widths.

Tariffs should not be hard-coded with `#define`: the normal rate is loaded from `tariff.txt`; peak rate is calculated at runtime as normal rate × 1.20. Macros remain suitable for structural constants such as readings per day and days per year.

## B. Evaluation of original design

- Annual count: 96 readings/day × 365 days = **35,040**.
- Assuming each interval can consume up to 100,000 Wh (100 kWh), 35,040 × 100,000 = **3,504,000,000 Wh**. This exceeds the maximum signed 32-bit integer (2,147,483,647), so a 32-bit signed accumulator could overflow.
- The count (35,040) fits a typical 32-bit `int`; `long long` is used for energy totals.
- `double` is beginner-friendly but binary floating point cannot represent every decimal exactly. Audited billing should use integer currency subunits or decimal arithmetic with a documented rounding policy.
- Macros suit fixed schedule dimensions, not tariffs expected to change at runtime. Streaming keeps memory use constant.

## C. Input format and program

### Reading representation and time assignment

`readings.txt` contains **interval energy consumption in whole watt-hours (Wh)**, one non-negative integer per line. These are not cumulative meter-register snapshots, so the program sums them directly. If the source provides cumulative register values, calculate each interval as current minus previous register and validate against decreases, rollover, and resets.

The first value represents 00:00–00:15. Every 96 values form one day. Within each day, indexes 72 through 87 represent 18:00 up to but not including 22:00 and receive the 20% higher tariff. A full non-leap year contains 35,040 values.

### Compile and run (Dev-C++)

1. Keep `main.c`, `tariff.txt`, and `readings.txt` together in the program's working directory.
2. Open `main.c` in the **Dev-C++ IDE**, then use its Compile and Run command. Dev-C++ invokes the C compiler configured in the IDE; the exact compiler depends on your Dev-C++ installation.
3. Make sure the program's working directory contains both `tariff.txt` and `readings.txt` when you run it.
4. Alternatively, if GCC is installed and available in your terminal, compile with:
   ```sh
   gcc -std=c11 -Wall -Wextra -pedantic main.c -o smart_meter
   ```
   Then run `smart_meter.exe` on Windows or `./smart_meter` on Linux/macOS.
5. Edit `tariff.txt` (for example, change `5.00` to `6.25`) to change the tariff without recompiling.

## D. Evidence-based defence and test plan

For 35,040 readings and the stated 100,000 Wh maximum per interval, maximum annual energy is 3,504,000,000 Wh (3,504,000 kWh). This exceeds 32-bit signed `int`; `long long` holds integer energy totals. Each interval is validated to 0–100,000 Wh. At Rs 5.00/kWh, peak rate is 5.00 × 1.20 = **Rs 6.00/kWh**. One 1,000 Wh interval costs Rs 5.00 off peak or Rs 6.00 on peak.

| Test | Input/setup | Expected behavior |
|---|---|---|
| Normal period | First reading = 1,000 Wh; rate 5.00 | Adds 1 kWh at Rs 5.00 |
| Peak period | Reading index 72 (18:00–18:15) = 1,000 Wh | Adds 1 kWh at Rs 6.00 |
| 20% increase | tariff.txt contains 5.00 | Peak tariff printed as Rs 6.00/kWh |
| Invalid tariff | Empty file, text, zero, negative, non-finite, or extra token | Clear tariff error and non-zero exit |
| Invalid reading | Negative, text, or value above 100,000 | Clear input error and non-zero exit |
| Missing input | Remove either text file | Clear missing-file error |
| Incomplete year | Fewer than 35,040 valid values | Partial dataset status |
| Full year | Exactly 35,040 valid values | Full non-leap-year status |

### Expected sample result (calculated, not execution-verified)

The sample has 1,000 Wh for each of 35,040 intervals and rate Rs 5.00/kWh. Each day has 80 normal intervals and 16 peak intervals:
- Normal energy: 29,200,000 Wh; 29,200 kWh × Rs 5.00 = Rs 146,000.00.
- Peak energy: 5,840,000 Wh; 5,840 kWh × Rs 6.00 = Rs 35,040.00.
- Total energy: 35,040,000 Wh (35,040 kWh); bill = **Rs 181,040.00**.

These are arithmetic expectations from the sample values, not a claim that the C program has been compiled or executed. No execution screenshot is included.

## Trade-offs and limitations

This educational flat-rate model excludes slab rates, fixed charges, taxes, demand charges, holidays, daylight-saving changes, leap years, meter resets, and fractional-Wh readings. It assumes interval consumption is supplied and a non-leap year begins at midnight. The 100,000 Wh cap is a stated validation assumption, not a universal physical limit. Floating-point billing is suitable for this demonstration, not audited billing.
