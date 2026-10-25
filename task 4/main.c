#include <stdio.h>

#define SQUARE(x) ((x) * (x))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define RUPEES_TO_PAISE(x) ((x) * 100)

static inline int square(int x)
{
    return x * x;
}

static inline int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int a = 5, b = 10;

    printf("Square: %d\n", SQUARE(a + 1));
    printf("Maximum: %d\n", MAX(a, b));
    printf("Rupees to paise: %d\n", RUPEES_TO_PAISE(50));

    printf("Inline square: %d\n", square(6));
    printf("Inline maximum: %d\n", maximum(a, b));

    return 0;
}
