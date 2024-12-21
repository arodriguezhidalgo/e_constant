using namespace std;
#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <fstream>


void compute(mpz_t *result, mpz_t a, mpz_t b)
{
  mpz_t out;
  mpz_init(out);

  mpz_init(result[0]);
  mpz_init(result[1]);

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
    compute(am, a, m);

    // Create the second split pointer
    mpz_t mb[2];
    mpz_init(mb[0]);
    mpz_init(mb[1]);

    // Recursively compute mb.
    compute(mb, m, b);

    // Compute the results.
    mpz_mul(result[0], am[0], mb[1]);
    mpz_add(result[0], result[0], mb[0]);
    mpz_mul(result[1], am[1], mb[1]);

    // Internal clean up
    mpz_clear(am[0]);
    mpz_clear(am[1]);
    mpz_clear(mb[0]);
    mpz_clear(mb[1]);
    mpz_clear(m);
  }

  // Clean up
  mpz_clear(aplusone);
  mpz_clear(out);
}

void createArray(mpz_t *data)
{
  mpz_init(data[0]);
  mpz_set_ui(data[0], 1);
}

int main()
{
  mpz_t results[2];

  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);

  // Define variable values.
  mpz_set_ui(a, 0);
  mpz_set_ui(b, 128);

  compute(results, a, b);

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

  // mpf_out_str(stdout, 1, 1000, e);
}
