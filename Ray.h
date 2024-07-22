#ifndef Ray_H
#define Ray_H
#include "linear/algebra.h"

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

Vector3 Ray_at(const Ray ray[const static 1], const double t);
Vector3 Ray_color(const Ray ray[const static 1]);

#endif // Ray_H
