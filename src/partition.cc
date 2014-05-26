
#include "partition.h"

int Gcd(int a, int b)
{
  int t;
  while (b) {
    t = a % b;
    a = b;
    b = t;
  }
  return a;
}


