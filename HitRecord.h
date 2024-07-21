#ifndef HitRecord_H
#define HitRecord_H

#include "linear/algebra.h"
#include "./Ray.h"

typedef struct {
    Vector3 p;
    Vector3 normal;
    double t;
    bool front;
} HitRecord;

void HitRecord_faceSet(HitRecord record[static 1], const Ray ray, const Vector3 normal);

#endif // HitRecord_H
