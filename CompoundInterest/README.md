# Compound Interest

This C++ console program calculates the compounding interest on a loan or an deposited investment amount. It takes the `principal amount`, `rate`, `compounding frequency` and `number of years` as inputs from the user. It then uses the formula `T = PA * (1 + ((roi / 100) / t))^(t*y)` to calculate the compound interest on a loan.

**Formula decoded:**

- _**T** = total accrued, including interest_
- _**PA** = principal amount_
- _**roi** = the annual interest rate for the amount borrowed or deposited_
- _**t** = the number of times the interest compounds yearly (compounding frequency)_
- _**y** = the number of years the principal amount has been borrowed or deposited_

Example: `T = 1000 * (1 + (0.050 / 2))^(2 * 5) = 1280.08`

##

Compile and run the program with:

```bash
g++ main.cpp -o a.out

./a.out
```
