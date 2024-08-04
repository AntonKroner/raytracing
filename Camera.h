#ifndef Camera_H
#define Camera_H
#include <stdio.h>
#include "linear/algebra.h"
#include "./Hittables.h"

typedef struct {
    double aspectRatio;
    struct {
        size_t width;
        size_t height;
    } image;
    Vector3 center;
    struct {
        Vector3 delta_u;
        Vector3 delta_v;
        size_t samples;
        double scale;
    } pixel;
    Vector3 pixel00_loc;
    size_t maxDepth;
    double verticalFov;
    Vector3 position;
    Vector3 up;
    Vector3 lookAt;
    struct {
        Vector3 u;
        Vector3 v;
        Vector3 w;
    } basis;
    struct {
        Vector3 u;
        Vector3 v;
        double distance;
        double angle;
    } defocus;
} Camera;

Camera Camera_make();
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream);

#endif // Camera_H
