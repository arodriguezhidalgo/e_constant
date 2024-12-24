#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>
#include <fstream>
class ComputeEngine
{
public:
  virtual void compute(int n, int prec, mpf_t output) = 0;
};

class MPComputeEngine : public ComputeEngine
// Use GMP to compute the e constant.
{
public:
  void compute(int nIterations, int prec, mpf_t output)
  {    
    mpf_set_default_prec(prec);

    mpz_t results[2];
    mpz_init(results[0]);
    mpz_init(results[1]);

    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);

    // Define variable values.
    mpz_set_ui(a, 0);
    mpz_set_ui(b, nIterations);

    // Compute p and q, and store it in results.
    internal_compute(results, a, b);

    // Compute e = 1+p/q.
    mpf_t e;
    mpf_init(e);

    mpf_t p;
    mpf_init(p);

    mpf_t q;
    mpf_init(q);

    mpf_set_z(p, results[0]);
    mpf_set_z(q, results[1]);
    mpf_div(e, p, q);
    mpf_add_ui(e, e, 1);

    // Print the results.    
    mpf_set(output, e);

    // Clean up.
    clear_z_array(results);
    mpz_clear(a);
    mpz_clear(b);
    mpf_clear(e);
    mpf_clear(p);
    mpf_clear(q);
  }

private:
  void internal_compute(mpz_t *result, mpz_t a, mpz_t b)
  {
    // Compute a+1
    mpz_t aplusone;
    mpz_init(aplusone);
    mpz_add_ui(aplusone, a, 1);

    // Check if b == a+1
    if (mpz_cmp(b, aplusone) == 0)
    {
      mpz_set_ui(result[0], 1);
      mpz_set(result[1], b);
    }
    else
    {
      // Compute m = floor((a+b)/2)
      mpz_t m;
      mpz_init(m);
      // First, add a and b.
      mpz_add(m, a, b);
      // Then, divide everything by 2.
      mpz_div_ui(m, m, 2);

      // Create the first split pointer.
      mpz_t am[2];
      mpz_init(am[0]);
      mpz_init(am[1]);

      // Recursively compute am.
      internal_compute(am, a, m);

      // Create the second split pointer
      mpz_t mb[2];
      mpz_init(mb[0]);
      mpz_init(mb[1]);

      // Recursively compute mb.
      internal_compute(mb, m, b);

      // Compute the results.
      mpz_mul(result[0], am[0], mb[1]);
      mpz_add(result[0], result[0], mb[0]);
      mpz_mul(result[1], am[1], mb[1]);

      // Internal clean up
      clear_z_array(am);
      clear_z_array(mb);
      mpz_clear(m);
    }

    // Clean up
    mpz_clear(aplusone);
  }

  void clear_z_array(mpz_t *ptr)
  {
    mpz_clear(ptr[0]);
    mpz_clear(ptr[1]);
  }
};