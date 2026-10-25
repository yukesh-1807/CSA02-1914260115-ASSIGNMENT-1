#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define READINGS_PER_DAY 96
#define DAYS_PER_YEAR 365
#define EXPECTED_READINGS (READINGS_PER_DAY * DAYS_PER_YEAR)
#define MAX_INTERVAL_WH 100000LL

int main(void)
{
    FILE *file;
    double normalRate, peakRate, bill = 0.0;
    long long readingWh, yearlyWh = 0, normalWh = 0, peakWh = 0;
    int count = 0, interval, hour, ch;

    file = fopen("tariff.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open tariff.txt.\n");
        return 1;
    }
    if (fscanf(file, "%lf", &normalRate) != 1 ||
        !isfinite(normalRate) || normalRate <= 0.0) {
        fprintf(stderr, "Error: tariff.txt must contain one positive, finite tariff.\n");
        fclose(file);
        return 1;
    }
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            fprintf(stderr, "Error: Unexpected extra data in tariff.txt.\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    peakRate = normalRate * 1.20;
    if (!isfinite(peakRate)) {
        fprintf(stderr, "Error: Tariff is too large to calculate safely.\n");
        return 1;
    }

    file = fopen("readings.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open readings.txt.\n");
        return 1;
    }

    while (1) {
        int result = fscanf(file, "%lld", &readingWh);
        if (result == EOF) {
            if (ferror(file)) {
                fprintf(stderr, "Error: Failed while reading readings.txt.\n");
                fclose(file);
                return 1;
            }
            break;
        }
        if (result != 1) {
            fprintf(stderr, "Error: readings.txt contains non-integer or invalid data.\n");
            fclose(file);
            return 1;
        }
        if (readingWh < 0 || readingWh > MAX_INTERVAL_WH) {
            fprintf(stderr, "Error: Each interval reading must be between 0 and %lld Wh.\n",
                    MAX_INTERVAL_WH);
            fclose(file);
            return 1;
        }
        if (count >= EXPECTED_READINGS) {
            fprintf(stderr, "Error: More than %d readings found; refusing extra data.\n",
                    EXPECTED_READINGS);
            fclose(file);
            return 1;
        }

        /* Interval consumption, not cumulative register values.
           Index 0 is 00:00-00:15; index 72 is 18:00-18:15. */
        interval = count % READINGS_PER_DAY;
        hour = interval / 4;
        yearlyWh += readingWh;

        if (hour >= 18 && hour < 22) {
            peakWh += readingWh;
            bill += ((double)readingWh / 1000.0) * peakRate;
        } else {
            normalWh += readingWh;
            bill += ((double)readingWh / 1000.0) * normalRate;
        }
        count++;
    }
    fclose(file);

    printf("\nSMART METER YEARLY REPORT\n");
    printf("-------------------------\n");
    printf("Readings processed: %d\n", count);
    printf("Expected yearly readings: %d\n", EXPECTED_READINGS);
    printf("Normal tariff: Rs %.2f per kWh\n", normalRate);
    printf("Peak tariff: Rs %.2f per kWh (20%% higher)\n", peakRate);
    printf("Total energy: %lld Wh (%.3f kWh)\n", yearlyWh, (double)yearlyWh / 1000.0);
    printf("Normal-period energy: %lld Wh\n", normalWh);
    printf("Peak-period energy: %lld Wh\n", peakWh);
    printf("Total bill: Rs %.2f\n", bill);

    if (count == EXPECTED_READINGS)
        printf("Status: Full non-leap-year dataset processed.\n");
    else
        printf("Status: Partial dataset; yearly result is incomplete.\n");
    return 0;
}
