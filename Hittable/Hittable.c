#include "Hittable.h"
#include "linear/algebra.h"
#include "../HitRecord.h"
#include "../Interval.h"
#include "../Ray.h"

bool Hittable_hit(
  Hittable hittable,
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]) {
  switch (hittable.type) {
    case Hittable_sphere:
      return Hittable_Sphere_hit(hittable.sphere, ray, interval, record);
      break;
    case Hittable_type_count:
      return false;
      break;
  }
}
Vector3 Hittable_color(Vector3 normal) {
  return Vector_scale(0.5, Vector_add(normal, Vector3_fill(1)));
}
