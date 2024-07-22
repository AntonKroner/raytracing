#ifndef Material_H
#define Material_H

#include "linear/algebra.h"
typedef struct {
    Vector3 albedo;
} Material_Lambertian;
typedef enum { Material_lambertian, Material_type_count } Material_type;
typedef struct {
    Material_type type;
    union {
        Material_Lambertian lambertian;
    };
} Material;

bool Material_scatter(Material Material, HitRecord record[static 1]) {
  switch (Material.type) {
    case Material_lambertian:
      return Sphere_hit(Material.sphere, ray, interval, record);
    case Material_type_count:
      return false;
  }
}
Vector3 Material_color(Vector3 normal) {
  return Vector_scale(0.5, Vector_add(normal, Vector3_fill(1)));
}

#endif // Material_H
