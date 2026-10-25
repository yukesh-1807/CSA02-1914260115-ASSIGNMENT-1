#include "billing.h"

double calculate_subtotal(int quantity, double unit_price)
{
    return quantity * unit_price;
}

double calculate_tax(double subtotal)
{
    return subtotal * TAX_RATE;
}

double calculate_total(double subtotal, double tax)
{
    return subtotal + tax;
}
