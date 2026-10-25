
#include <stdio.h>

int main(void)
{
    int previousReading, currentReading;
    int unitsConsumed;

    printf("Enter previous meter reading: ");
    if (scanf("%d", &previousReading) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter current meter reading: ");
    if (scanf("%d", &currentReading) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    if (previousReading < 0 || currentReading < 0 ||
        currentReading < previousReading)
    {
        printf("Invalid meter readings!\n");
        return 1;
    }

    unitsConsumed = currentReading - previousReading;

    printf("Units consumed = %d\n", unitsConsumed);

    return 0;
}
