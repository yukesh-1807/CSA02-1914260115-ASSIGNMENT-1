#include <stdio.h>
#include "billing.h"

int main(void)
{
    int quantity;
    double unit_price, subtotal, tax, total;

    printf("Enter quantity: ");
    if (scanf("%d", &quantity) != 1 || quantity < 0 || quantity > MAX_ITEMS) {
        printf("Invalid quantity. Enter a value from 0 to %d.\n", MAX_ITEMS);
        return 1;
    }

    printf("Enter unit price: ");
    if (scanf("%lf", &unit_price) != 1 || unit_price < 0) {
        printf("Invalid unit price.\n");
        return 1;
    }

    subtotal = calculate_subtotal(quantity, unit_price);
    tax = calculate_tax(subtotal);
    total = calculate_total(subtotal, tax);

#ifdef DEBUG
    printf("[DEBUG] quantity = %d\n", quantity);
    printf("[DEBUG] unit price = %.2f\n", unit_price);
    printf("[DEBUG] subtotal = %.2f\n", subtotal);
    printf("[DEBUG] tax = %.2f\n", tax);
#endif

    printf("Subtotal: %.2f\n", subtotal);
    printf("Tax (%.0f%%): %.2f\n", TAX_RATE * 100, tax);
    printf("Total: %.2f\n", total);
    return 0;
}
