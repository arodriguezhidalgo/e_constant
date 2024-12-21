using namespace std;
#include <iostream>
#include <gmp.h>
#include <stdio.h>

void createArray(mpz_t *data){  
  mpz_init(data[0]);
  mpz_set_ui(data[0],1);
}



int main()
{

  mpz_t myPtr[2];

  createArray(myPtr);
  mpz_out_str(stdout, 10, myPtr[0]);
   
}