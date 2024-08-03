#ifndef Material_H
#define Material_H

#include "linear/algebra.h"
#include "../Ray.h"
#include "../HitRecord.h"

typedef struct {
    Vector3 albedo;
} Material_Lambertian;
typedef struct {
    Vector3 albedo;
} Material_Metal;
typedef enum { Material_lambertian, Material_metal, Material_type_count } Material_type;
typedef struct {
    Material_type type;
    union {
        Material_Lambertian lambertian;
        Material_Metal metal;
    };
} Material;

Material Material_make(Material_type type, Vector3 albedo);
Material_Metal Material_Metal_make(Vector3 albedo);
Material_Lambertian Material_Lambertian_make(Vector3 albedo);
bool Material_scatter(
  const Material material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]);
bool Material_Lambertian_scatter(
  const Material_Lambertian material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]);
bool Material_Metal_scatter(
  const Material_Metal material,
  const Ray ray,
  const HitRecord record,
  Vector3 attenuation[static 1],
  Ray scattered[static 1]);
Vector3 Material_color(Vector3 normal);

#endif // Material_H
