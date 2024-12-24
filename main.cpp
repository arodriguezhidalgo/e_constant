#include "compute_engine.cpp"
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>

int main()
{
  const int precision = 12000;
  mpf_set_default_prec(precision);
  const bool VERBOSITY = false;
  const bool WRITE_FILE = false;

  const int userSpecifiedNumberOfDigits = 30;
  MPComputeEngine eng;
  mpf_t output;
  mpf_init(output);

  mpf_t previous_output;
  mpf_init(previous_output);

  mpf_t correct_digits;
  mpf_init(correct_digits);

  // Iterate multiple times to compute the digits of e.
  // for (int i = 1; i <= nDigits; i++)
  int computedNumberOfDigits = 0;
  int nIterations = 1;
  while (computedNumberOfDigits < userSpecifiedNumberOfDigits)
  {
    eng.compute(nIterations, precision, output);
    if (VERBOSITY == true)
    {
      std::cout << nIterations << ". ";
      mpf_out_str(stdout, 1, computedNumberOfDigits, output);
    }

    if (nIterations != 1)
    {
      // Subtract the digits of the current and previous iteration.
      mpf_sub(correct_digits, previous_output, output);

      // Convert such diff in the digits to a string with scientific notation. We will use the exponent value.
      // I am not completely sure about this, but for a huge amount of digits I think it may be a better idea
      // to manipulate this formatted string than a numeric type with a huge
      char buffer[2];
      sprintf(buffer, "%.2e", mpf_get_d(correct_digits));
      std::string digits(buffer);

      // Digits diffs are stored as X.YZe-AB. We will always have a mantissa of 2 elements, then the exponent in base 10.
      // This means that we can grab the exponent value using the positions 6 and 7. See the following explanation:
      //  Digit    - |X |. |Y |Z |e |- |A |B |
      //  Position - |0 |1 |2 |3 |4 |5 |6 |7 |
      // Also, we cast such quantity to integer.

      computedNumberOfDigits = stoi(digits.substr(7, 2));

      if (VERBOSITY == true)
      {
        std::cout << digits << ", " << computedNumberOfDigits;
        std::cout << "\n";
      }
    }

    mpf_set(previous_output, output);
    nIterations++;
  }

  // Write outputs.
  std::cout << "- # iterations: " << nIterations - 1 << "\n- # verified digits: " << computedNumberOfDigits << "\n- e-constant: ";
  mpf_out_str(stdout, 10, computedNumberOfDigits, output);
  std::cout << "\n";

  // Write the result in a file.
  if (WRITE_FILE == true)
  {
    FILE *pFile;
    pFile = fopen("out.txt", "w");
    mpf_out_str(pFile, 10, computedNumberOfDigits, output);
  }

  mpf_clear(output);
  mpf_clear(previous_output);
}