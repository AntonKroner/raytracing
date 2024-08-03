#include "Material.h"
#include "isNearZero.h"
#include <tgmath.h>
#include "linear/algebra.h"
#include "random.h"
#include "../Ray.h"
#include "../HitRecord.h"

Material_Lambertian Material_Lambertian_make(Vector3 albedo) {
  Material_Lambertian result = {
    .albedo.components[0] = albedo.components[0],
    .albedo.components[1] = albedo.components[1],
    .albedo.components[2] = albedo.components[2],
  };
  return result;
}
bool Material_Lambertian_scatter(
  const Material_Lambertian material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]) {
  Vector3 scatterDirection = Vector_add(record.normal, Vector3_randomUnit());
  // Catch degenerate scatter direction
  if (Vector3_isNearZero(scatterDirection)) {
    scatterDirection = record.normal;
  }
  scattered->origin = record.p;
  scattered->direction = scatterDirection;
  attenuation->components[0] = material.albedo.components[0];
  attenuation->components[1] = material.albedo.components[1];
  attenuation->components[2] = material.albedo.components[2];
  return true;
}
