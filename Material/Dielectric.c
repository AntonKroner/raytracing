#include "Material.h"
#include <tgmath.h>
#include "random.h"
#include "linear/algebra.h"
#include "../Ray.h"
#include "../HitRecord.h"

Material_Dielectric Material_Dielectric_make(Vector3 albedo, double refraction) {
  Material_Dielectric result = {
    .albedo.components[0] = albedo.components[0],
    .albedo.components[1] = albedo.components[1],
    .albedo.components[2] = albedo.components[2],
    .refraction = refraction,
  };
  return result;
}
static double reflectance(double cosine, double refraction) {
  // Use Schlick's approximation for reflectance.
  double r0 = (1 - refraction) / (1 + refraction);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}
static Vector3 reflect(const Vector3 vector, const Vector3 n) {
  return Vector_subtract(vector, Vector_scale(2 * Vector_inner(vector, n), n));
}
static Vector3 refract(const Vector3 uv, const Vector3 n, double etai_over_etat) {
  double cos_theta = fmin(-Vector_inner(uv, n), 1.0);
  Vector3 r_out_perp =
    Vector_scale(etai_over_etat, Vector_add(uv, Vector_scale(cos_theta, n)));
  Vector3 r_out_parallel =
    Vector_scale(-sqrt(fabs(1.0 - Vector_inner(r_out_perp, r_out_perp))), n);
  return Vector_add(r_out_perp, r_out_parallel);
}
bool Material_Dielectric_scatter(
  const Material_Dielectric material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]) {
  double ri = record.front ? (1.0 / material.refraction) : material.refraction;
  Vector3 direction = Vector_normalize(ray.direction);

  double cos_theta = fmin(-Vector_inner(direction, record.normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
  bool cannotRefract = ri * sin_theta > 1.0;

  Vector3 result = cannotRefract || reflectance(cos_theta, ri) > randomDouble()
                     ? reflect(direction, record.normal)
                     : refract(direction, record.normal, ri);
  scattered->origin = record.p;
  scattered->direction = result;
  attenuation->components[0] = 1.0;
  attenuation->components[1] = 1.0;
  attenuation->components[2] = 1.0;
  return true;
}
