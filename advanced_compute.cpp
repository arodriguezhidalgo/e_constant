using namespace std;
#include <iostream>
#include <gmp.h>
#include <stdio.h>

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
  // mpz_set_ui(out, mpz_cmp(b, aplusone) == 0);
  // mpz_out_str(stdout, 1, out);
  if (mpz_cmp(b, aplusone) == 0)
  {
    mpz_set_ui(result[0], 1);
    mpz_set(result[1], b);
  }

  // mpz_set_ui(out, mpz_cmp(aplusone,b));
  // mpz_out_str(stdout, 1, out);

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
  mpz_t myPtr[2];

  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);

  // Define variable values.
  mpz_set_ui(a, 1);
  mpz_set_ui(b, 2);

  // createArray(myPtr);

  compute(myPtr, a, b);
  mpz_out_str(stdout, 0, myPtr[0]);
  mpz_out_str(stdout, 1, myPtr[1]);
  // mpz_out_str(stdout, 10, myPtr[0]);
}
