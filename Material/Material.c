#include "Material.h"
#include "linear/algebra.h"
#include "../Ray.h"
#include "../HitRecord.h"

Material Material_make(Material_type type, Vector3 albedo, double parameter) {
  Material result = { .type = type };
  switch (type) {
    case Material_lambertian:
      result.lambertian = Material_Lambertian_make(albedo);
      break;
    case Material_metal:
      result.metal = Material_Metal_make(albedo, parameter);
      break;
    case Material_dielectric:
      result.dielectric = Material_Dielectric_make(albedo, parameter);
      break;
    case Material_type_count:
      break;
  }
  return result;
}
bool Material_scatter(
  const Material material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]) {
  switch (material.type) {
    case Material_lambertian:
      return Material_Lambertian_scatter(
        material.lambertian,
        ray,
        record,
        attenuation,
        scattered);
      break;
    case Material_metal:
      return Material_Metal_scatter(material.metal, ray, record, attenuation, scattered);
      break;
    case Material_dielectric:
      return Material_Dielectric_scatter(
        material.dielectric,
        ray,
        record,
        attenuation,
        scattered);
    case Material_type_count:
      return false;
      break;
  }
}
Vector3 Material_color(Vector3 normal) {
  return Vector_scale(0.5, Vector_add(normal, Vector3_fill(1)));
}
