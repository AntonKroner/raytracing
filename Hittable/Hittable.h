#ifndef Hittable_H
#define Hittable_H
#include "linear/algebra.h"
#include "rxi/Array.h"
#include "../HitRecord.h"
#include "../Interval.h"
#include "../Ray.h"
#include "../Material/Material.h"

typedef struct {
    Vector3 center;
    double radius;
    Material* material;
} Hittable_Sphere;
typedef enum { Hittable_sphere, Hittable_type_count } Hittable_type;
typedef struct {
    Hittable_type type;
    union {
        Hittable_Sphere sphere;
    };
} Hittable;
typedef Array_t(Hittable) Hittable_Array;

bool Hittable_hit(
  Hittable hittable,
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]);
Vector3 Hittable_color(Vector3 normal);

Hittable_Sphere Hittable_Sphere_make(Vector3 center, double radius, Material material[static 1]);
bool Hittable_Sphere_hit(
  const Hittable_Sphere sphere,
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]);
Vector3 Hittable_Sphere_at(const Ray ray[const static 1], const double t);
Vector3 Hittable_Sphere_color(const Ray ray[const static 1]);
void Hittable_Sphere_add(Hittable_Array hittables[static 1], const Hittable_Sphere sphere);

#endif // Hittable_H
