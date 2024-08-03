#ifndef isNearZero_H_
#define isNearZero_H_

#include "linear/algebra.h"
#include <stdbool.h>
#include <tgmath.h>

bool Vector3_isNearZero(Vector3 vector) {
  double s = 1e-8;
  return (fabs(vector.components[0]) < s) && (fabs(vector.components[1]) < s) && (fabs(vector.components[2]) < s);
}

#endif // isNearZero_H_
