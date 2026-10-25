#ifndef BILLING_H
#define BILLING_H

#define TAX_RATE 0.05
#define MAX_ITEMS 100

/* Calculate the bill subtotal, tax, and final total. */
double calculate_subtotal(int quantity, double unit_price);
double calculate_tax(double subtotal);
double calculate_total(double subtotal, double tax);

#endif /* BILLING_H */
