#ifndef HitRecord_H
#define HitRecord_H
#include "linear/algebra.h"
// #include "./Material/Material.h"
#include "./Ray.h"

// typedef void Material;

typedef struct {
    Vector3 p;
    Vector3 normal;
    // TODO: figure out how to avoid having the wacky void pointer to avoid circular dependency
    void* material;
    double t;
    bool front;
} HitRecord;

void HitRecord_faceSet(HitRecord record[static 1], const Ray ray, const Vector3 normal);

#endif // HitRecord_H
