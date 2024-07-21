#include "HitRecord.h"
#include "linear/algebra.h"
#include "./Ray.h"

void HitRecord_faceSet(HitRecord record[static 1], const Ray ray, const Vector3 normal) {
  record->front = Vector_inner(ray.direction, normal) < 0;
  record->normal = record->front ? normal : Vector_scale(-1, normal);
}

