#ifndef Hittables_H
#define Hittables_H
#include "./Hittable/Hittable.h"
#include "./HitRecord.h"
#include "./Interval.h"
#include "./Ray.h"

typedef struct {
    Hittable_Array* list;
} Hittables;

Hittables* Hittables_create();
void Hittables_destroy(Hittables* hittables);
#define Hittables_add(Hittables, Hittable)                    \
  _Generic((Hittable), Hittable_Sphere: Hittable_Sphere_add)( \
    (Hittables->list),                                        \
    (Hittable))
void Hittables_clear(Hittables hittables[static 1]);
bool Hittables_hit(
  const Hittables hittables[static 1],
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]);

#endif // Hittables_H
