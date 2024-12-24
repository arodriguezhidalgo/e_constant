#include "compute_engine.cpp"
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>

int main()
{
  const int nDigits = 15;
  MPComputeEngine eng;
  mpf_t output;
  mpf_init(output);

  mpf_t previous_output;
  mpf_init(previous_output);

  mpf_t correct_digits;
  mpf_init(correct_digits);

  mp_exp_t exponent;

// Iterate multiple times to compute the digits of e.
  for (int i = 1; i <= nDigits; i++)
  {
    std::cout << ".- ";

    const int precision = 1200;
    eng.compute(i, precision, output);
    mpf_out_str(stdout, 10, precision, output);

    std::cout << "@ ";
    if (i != 1)
    {
      // Subtract the digits of the current and previous iteration.
      mpf_sub(correct_digits, previous_output, output);
      std::cout << "@";      

      // Convert such diff in the digits to a string with scientific notation. We will use the exponent value.
      // I am not completely sure about this, but for a huge amount of digits I think it may be a better idea 
      // to manipulate this formatted string than a numeric type with a huge mantissa.
      char buffer[2];
      sprintf(buffer, "%.2e", mpf_get_d(correct_digits));
      std::string digits(buffer);

      // Digits diffs are stored as X.YZe-AB. We will always have a mantissa of 2 elements, then the exponent in base 10.
      // This means that we can grab the exponent value using the positions 6 and 7. See the following explanation:
      //  Digit    - |X |. |Y |Z |e |- |A |B |
      //  Position - |0 |1 |2 |3 |4 |5 |6 |7 |
      // Also, we cast such quantity to integer.
      std::cout << "@";      
      std::cout << digits << ", " << stoi(digits.substr(7, 2));
    }

    std::cout << "\n";
    mpf_set(previous_output, output);
  }
  mpf_clear(output);
  mpf_clear(previous_output);
}