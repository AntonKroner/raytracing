#ifndef Hittable_H
#define Hittable_H

#include "linear/algebra.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "./Interval.h"

typedef enum { Hittable_Sphere, Hittable_type_count } Hittable_type;

typedef struct {
    Hittable_type type;
    union {
        Sphere sphere;
    };
} Hittable;

bool Hittable_hit(
  Hittable hittable,
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]) {
  switch (hittable.type) {
    case Hittable_Sphere:
      return Sphere_hit(hittable.sphere, ray, interval, record);
    case Hittable_type_count:
      return false;
  }
}
Vector3 Hittable_color(Vector3 normal) {
  return Vector_scale(0.5, Vector_add(normal, Vector3_fill(1)));
}

#endif // Hittable_H
