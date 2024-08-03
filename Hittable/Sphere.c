
#include "Hittable.h"
#include <tgmath.h>
#include "linear/algebra.h"
#include "rxi/Array.h"
#include "../HitRecord.h"
#include "../Interval.h"
#include "../Ray.h"

Hittable_Sphere Hittable_Sphere_make(
  Vector3 center,
  double radius,
  Material material[static 1]) {
  Hittable_Sphere result = {
    .center = center,
    .radius = fmax(0, radius),
    .material = material,
  };
  return result;
}
bool Hittable_Sphere_hit(
  const Hittable_Sphere sphere,
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]) {
  bool result;
  Vector3 oc = Vector_subtract(sphere.center, ray.origin);
  double a = Vector_inner(ray.direction, ray.direction);
  double h = Vector_inner(ray.direction, oc);
  double c = Vector_inner(oc, oc) - sphere.radius * sphere.radius;
  double discriminant = h * h - a * c;
  if (discriminant < 0) {
    result = false;
  }
  else {
    double discriminantRoot = sqrt(discriminant);
    double root = (h - discriminantRoot) / a;
    if (!Interval_surrounds(interval, root)) {
      root = (h + discriminantRoot) / a;
      if (!Interval_surrounds(interval, root)) {
        return false;
      }
    }
    record->t = root;
    record->p = Ray_at(&ray, record->t);
    Vector3 normal =
      Vector_scale(1 / sphere.radius, Vector_subtract(record->p, sphere.center));
    HitRecord_faceSet(record, ray, normal);
    record->material = sphere.material;
    result = true;
  }
  return result;
}
Vector3 Hittable_Sphere_at(const Ray ray[const static 1], const double t) {
  return Vector_add(ray->origin, Vector_scale(t, ray->direction));
}
Vector3 Hittable_Sphere_color(const Ray ray[const static 1]) {
  Vector3 direction = Vector_normalize(ray->direction);
  double a = 0.5 * (direction.components[1] + 1.0);
  return Vector_add(
    Vector_scale(1.0 - a, Vector3_make(1.0, 1.0, 1.0)),
    Vector_scale(a, Vector3_make(0.5, 0.7, 1.0)));
}
void Hittable_Sphere_add(Hittable_Array hittables[static 1], const Hittable_Sphere sphere) {
  Hittable item = { .type = Hittable_sphere, .sphere = sphere };
  Array_push(hittables, item);
}
