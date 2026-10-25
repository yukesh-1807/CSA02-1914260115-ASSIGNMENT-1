#include <stdio.h>

#define RATE 225

int main(void)
{
    int units = 150;
    long bill = 5000L + (units - 100) * RATE;

    printf("Units: %d\n", units);
    printf("Bill: Rs %ld.%02ld\n", bill / 100, bill % 100);

    return 0;
}
