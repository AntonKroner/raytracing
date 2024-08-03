#include "Material.h"
#include <tgmath.h>
#include "linear/algebra.h"
#include "../Ray.h"
#include "../HitRecord.h"

Material_Metal Material_Metal_make(Vector3 albedo) {
  Material_Metal result = {
    .albedo.components[0] = albedo.components[0],
    .albedo.components[1] = albedo.components[1],
    .albedo.components[2] = albedo.components[2],
  };
  return result;
}
static Vector3 reflect(const Vector3 vector, const Vector3 n) {
  return Vector_subtract(vector, Vector_scale(2 * Vector_inner(vector, n), n));
}
bool Material_Metal_scatter(
  const Material_Metal material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]) {
  Vector3 reflected = reflect(ray.direction, record.normal);
  scattered->origin = record.p;
  scattered->direction = reflected;
  attenuation->components[0] = material.albedo.components[0];
  attenuation->components[1] = material.albedo.components[1];
  attenuation->components[2] = material.albedo.components[2];
  return true;
}
