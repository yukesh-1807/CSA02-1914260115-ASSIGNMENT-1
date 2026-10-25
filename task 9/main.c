
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_READING 65535L
#define FIXED_CHARGE 5000L
#define RATE2 225L
#define RATE3 450L

int read_reading(const char *prompt, long *reading)
{
    char line[100];
    char *end;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;

    errno = 0;
    long value = strtol(line, &end, 10);

    while (*end == ' ' || *end == '\t' ||
           *end == '\n' || *end == '\r')
        end++;

    if (end == line || *end != '\0' || errno != 0 ||
        value < 0 || value > MAX_READING)
    {
        printf("Invalid input! Enter a reading from 0 to 65535.\n");
        return 0;
    }

    *reading = value;
    return 1;
}

long calculate_bill(long units)
{
    long bill = FIXED_CHARGE;

    if (units > 200)
        bill += 100 * RATE2 + (units - 200) * RATE3;
    else if (units > 100)
        bill += (units - 100) * RATE2;

    return bill;
}

int main(void)
{
    long previous, current, units;
    char answer[20];

    if (!read_reading("Enter previous reading: ", &previous))
        return 1;

    if (!read_reading("Enter current reading: ", &current))
        return 1;

    if (current < previous)
    {
        printf("Did the meter roll over? (y/n): ");

        if (fgets(answer, sizeof(answer), stdin) == NULL)
            return 1;

        if (answer[0] != 'y' && answer[0] != 'Y')
        {
            printf("Invalid readings: current is less than previous.\n");
            return 1;
        }

        units = (MAX_READING - previous) + current + 1;
    }
    else
    {
        units = current - previous;
    }

    long bill = calculate_bill(units);

    printf("Units consumed = %ld\n", units);
    printf("Electricity bill = Rs %ld.%02ld\n",
           bill / 100, bill % 100);

    return 0;
}
