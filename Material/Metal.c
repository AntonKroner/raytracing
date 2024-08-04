#include "Material.h"
#define randomDouble_implementation
#include "random.h"
#include <tgmath.h>
#include "linear/algebra.h"
#include "../Ray.h"
#include "../HitRecord.h"

Material_Metal Material_Metal_make(Vector3 albedo, double fuzz) {
  Material_Metal result = {
    .albedo.components[0] = albedo.components[0],
    .albedo.components[1] = albedo.components[1],
    .albedo.components[2] = albedo.components[2],
    .fuzz = fuzz,
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
  Vector3 reflected = Vector_normalize(reflect(ray.direction, record.normal));
  reflected = Vector_add(
    reflected,
    Vector_scale(material.fuzz < 1 ? material.fuzz : 1, Vector3_randomUnit()));
  scattered->origin = record.p;
  scattered->direction = reflected;
  attenuation->components[0] = material.albedo.components[0];
  attenuation->components[1] = material.albedo.components[1];
  attenuation->components[2] = material.albedo.components[2];
  return Vector_inner(scattered->direction, record.normal) > 0;
}
