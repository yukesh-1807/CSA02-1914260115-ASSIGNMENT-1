#include <stdio.h>

int main(void)
{
    int n[] = {4000, 60000, 800000};
    int i;

    float float_total = 0.0f;
    long long paise_total = 0;

    for (i = 0; i < 800000; i++)
    {
        float_total += 162.50f;
        paise_total += 16250;

        if (i + 1 == 4000 || i + 1 == 60000 ||
            i + 1 == 800000)
        {
            printf("\nHouseholds: %d\n", i + 1);
            printf("Float total: %.2f\n", float_total);
            printf("Paise total: %lld\n", paise_total);
            printf("Paise total in rupees: %lld.%02lld\n",
                   paise_total / 100, paise_total % 100);
        }
    }

    printf("\nSize of int: %zu\n", sizeof(int));
    printf("Size of long: %zu\n", sizeof(long));
    printf("Size of long long: %zu\n", sizeof(long long));

    return 0;
}
