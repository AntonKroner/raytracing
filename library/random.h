#ifndef randomDouble_H_
#define randomDouble_H_

#include <stdlib.h>

double randomDouble() {
  return (double)rand() / ((double)RAND_MAX + 1.0);
}
double randomDoubleInterval(double min, double max) {
  return min + (max - min) * randomDouble();
}

#endif // randomDouble_H_
