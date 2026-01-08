# Compound Interest

This C++ console program calculates the compounding interest on a loan or a deposited investment amount. It takes the `principal amount`, `rate`, `compounding frequency` and `number of years` as inputs from the user. It then uses the formula `T = PA * (1 + ((roi / 100) / t))^(t*y)` to calculate the compound interest on a loan.

**Formula decoded:**

- _**T** = total accrued, including interest_
- _**PA** = principal amount_
- _**roi** = the annual interest rate for the amount borrowed or deposited_
- _**t** = the number of times the interest compounds yearly (compounding frequency)_
- _**y** = the number of years the principal amount has been borrowed or deposited_

**Example:**

Given the following values:

```text
PA = 1000
roi = 5%
t = 2
y = 5
```

`T = 1000 * (1 + ((5 / 100) / 2))^(2 * 5) = 1280.08`

##

To run the program, first compile it with:

```bash
g++ main.cpp -o a.out
```

then you can run the generated executable file with:

```bash
./a.out
```
