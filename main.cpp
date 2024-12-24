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

  for (int i = 1; i <= nDigits; i++)
  {
    std::cout << ".- ";

    const int precision = 1200;
    eng.compute(i, precision, output);
    mpf_out_str(stdout, 10, precision, output);

    std::cout << "@ ";
    if (i != 1)
    {
      mpf_sub(correct_digits, previous_output, output);
      std::cout << "@";      
      char buffer[2];
      sprintf(buffer, "%.2e", mpf_get_d(correct_digits));
      printf(buffer);
    }

    std::cout << "\n";
    mpf_set(previous_output, output);
  }
  mpf_clear(output);
  mpf_clear(previous_output);
}