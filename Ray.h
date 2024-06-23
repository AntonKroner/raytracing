#ifndef Ray_H
#define Ray_H

#include "linear/algebra.h"

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

Vector3 Ray_at(const Ray ray[const static 1], const double t) {
  return Vector_add(ray->origin, Vector_scale(t, ray->direction));
}
Vector3 Ray_color(const Ray ray[const static 1]) {
  Vector3 direction = Vector_normalize(ray->direction);
  double a = 0.5 * (direction.components[1] + 1.0);
  return Vector_add(
    Vector_scale(1.0 - a, Vector3_make(1.0, 1.0, 1.0)),
    Vector_scale(a, Vector3_make(0.5, 0.7, 1.0)));
}

#endif // Ray_H
