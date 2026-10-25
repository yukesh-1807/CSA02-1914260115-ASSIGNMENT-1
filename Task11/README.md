# Task 11 – Design Recommendations

## 1. Problem Analysis
The electricity billing program calculates units consumed from previous and current meter readings and determines the bill using tariff slabs.

## 2. Design Recommendations
- Use meaningful variable and function names.
- Validate user input before calculating the bill.
- Use constants for fixed charges and tariff rates.
- Handle meter rollover correctly.
- Test normal, boundary, and invalid input cases.

## 3. Justification
Constants make tariff changes easier. Input validation prevents incorrect readings from producing wrong bills. Separate functions improve readability and testing.

## 4. Testing
Test zero units, tariff boundaries, normal readings, meter rollover, and invalid inputs.

## 5. Conclusion
A good billing program should be reliable, readable, easy to test, and easy to maintain.
