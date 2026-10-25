
#include <stdio.h>

int main(void)
{
    int units = 150;
    float rate = 2.25f;
    float bill;
    int wholeNumber;

    bill = units * rate;
    wholeNumber = bill;

    printf("Units consumed = %d\n", units);
    printf("Rate per unit = %.2f\n", rate);
    printf("Bill amount = %.2f\n", bill);
    printf("Bill converted to int = %d\n", wholeNumber);

    return 0;
}
