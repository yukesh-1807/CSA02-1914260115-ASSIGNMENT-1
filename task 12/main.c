
#include <stdio.h>

#define READINGS_PER_DAY 96
#define DAYS_PER_YEAR 365
#define EXPECTED_READINGS (READINGS_PER_DAY * DAYS_PER_YEAR)

int main(void)
{
    FILE *tariffFile;
    FILE *readingFile;

    double normalRate;
    double peakRate;
    double bill = 0.0;

    long long readingWh;
    long long yearlyWh = 0;
    long long peakWh = 0;
    long long normalWh = 0;

    int count = 0;
    int interval;
    int hour;

    tariffFile = fopen("tariff.txt", "r");

    if (tariffFile == NULL)
    {
        printf("Error: Cannot open tariff.txt\n");
        return 1;
    }

    if (fscanf(tariffFile, "%lf", &normalRate) != 1 ||
        normalRate < 0)
    {
        printf("Error: Invalid tariff in tariff.txt\n");
        fclose(tariffFile);
        return 1;
    }

    fclose(tariffFile);

    peakRate = normalRate * 1.20;

    readingFile = fopen("readings.txt", "r");

    if (readingFile == NULL)
    {
        printf("Error: Cannot open readings.txt\n");
        return 1;
    }

    while (fscanf(readingFile, "%lld", &readingWh) == 1)
    {
        if (readingWh < 0)
        {
            printf("Error: Negative reading found.\n");
            fclose(readingFile);
            return 1;
        }

        interval = count % READINGS_PER_DAY;
        hour = interval / 4;

        yearlyWh += readingWh;

        if (hour >= 18 && hour < 22)
        {
            peakWh += readingWh;
            bill += (readingWh / 1000.0) * peakRate;
        }
        else
        {
            normalWh += readingWh;
            bill += (readingWh / 1000.0) * normalRate;
        }

        count++;
    }

    if (!feof(readingFile))
    {
        printf("Error: readings.txt contains invalid data.\n");
        fclose(readingFile);
        return 1;
    }

    fclose(readingFile);

    printf("\nSMART METER YEARLY REPORT\n");
    printf("-------------------------\n");
    printf("Readings processed: %d\n", count);
    printf("Expected yearly readings: %d\n", EXPECTED_READINGS);
    printf("Normal tariff: Rs %.2f per kWh\n", normalRate);
    printf("Peak tariff: Rs %.2f per kWh\n", peakRate);
    printf("Total energy: %lld Wh\n", yearlyWh);
    printf("Normal-period energy: %lld Wh\n", normalWh);
    printf("Peak-period energy: %lld Wh\n", peakWh);
    printf("Total bill: Rs %.2f\n", bill);

    if (count == EXPECTED_READINGS)
        printf("Status: Full non-leap-year dataset processed.\n");
    else
        printf("Status: Partial dataset; yearly result is incomplete.\n");

    return 0;
}
