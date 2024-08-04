#ifndef randomDouble_H_
#define randomDouble_H_

#include <stdlib.h>
#include "linear/algebra.h"

double randomDouble();
double randomDoubleInterval(double min, double max);
Vector3 Vector3_random();
Vector3 Vector3_randomInterval(double min, double max);
Vector3 Vector3_randomUnitSphere();
Vector3 Vector3_randomUnit();
Vector3 Vector3_randomOnHemisphere(Vector3 normal);
Vector3 Vector3_randomInUnitDisk();

#ifdef randomDouble_implementation
double randomDouble() {
  return (double)rand() / ((double)RAND_MAX + 1.0);
}
double randomDoubleInterval(double min, double max) {
  return min + (max - min) * randomDouble();
}
Vector3 Vector3_random() {
  return Vector3_make(randomDouble(), randomDouble(), randomDouble());
}
Vector3 Vector3_randomInterval(double min, double max) {
  return Vector3_make(
    randomDoubleInterval(min, max),
    randomDoubleInterval(min, max),
    randomDoubleInterval(min, max));
}
Vector3 Vector3_randomUnitSphere() {
  while (true) {
    Vector3 result = Vector3_randomInterval(-1, 1);
    if (Vector_norm(result) < 1) {
      return result;
    }
  }
}
Vector3 Vector3_randomUnit() {
  return Vector3_normalize(Vector3_randomUnitSphere());
}
Vector3 Vector3_randomOnHemisphere(Vector3 normal) {
  Vector3 result = Vector3_randomUnit();
  if (Vector_inner(result, normal) > 0.0) {
    return result;
  }
  else {
    return Vector_scale(-1, result);
  }
}
Vector3 Vector3_randomInUnitDisk() {
  while (true) {
    Vector3 p = Vector3_make(randomDoubleInterval(-1, 1), randomDoubleInterval(-1, 1), 0);
    if (Vector_inner(p, p) < 1) {
      return p;
    }
  }
}
#endif //

#endif // randomDouble_H_
