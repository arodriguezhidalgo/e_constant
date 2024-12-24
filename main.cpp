#include "compute_engine.cpp"
#include <iostream>
#include <gmp.h>
int main()
{
  const int nDigits = 15;
  MPComputeEngine eng;
  mpf_t outputs;
  mpf_init(outputs);

  mpf_t previous_output;
  mpf_init(previous_output);

  mpf_t correct_digits;
  mpf_init(correct_digits);

  for (int i = 1; i <= nDigits; i++)
  {
    std::cout << ".- ";

    const int precision = 1200;
    eng.compute(i, precision, outputs);    
    mpf_out_str(stdout, 1, precision, outputs);
    std::cout << ", ";

    if (i != 1){
      mpf_sub(correct_digits, previous_output, outputs);
      mpf_out_str(stdout, 1, precision, correct_digits);      
    }
    std::cout << "\n";
    mpf_set(previous_output, outputs);
    // mpf_clear(outputs);
  }
}