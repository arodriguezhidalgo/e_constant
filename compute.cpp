using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <gmp.h>

std::vector<long int> compute(int a, int b) {
  std::vector<long int> result;

  if (b == a+1) {
    result = {1, b};
  }
  else{
    const int m = floor((a+b)/2);
    const std::vector<long int> am = compute(a, m);
    const std::vector<long int> mb = compute(m, b);

    result = {am[0]*mb[1]+mb[0], am[1]*mb[1]};
  }
  
  return result;
}

int main() {
  // Open file
  ofstream MyFile("Results.txt");
  const int n = 21;
  
  const std::vector<long int> result = compute(0,n);  
  long double num = result[0];
  long double denom = result[1];

  MyFile << std::setprecision(100) << std::fixed << (1+ num/denom);
  MyFile.close();
}