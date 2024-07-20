#ifndef Camera_H
#define Camera_H

#include <stdio.h>
#include "linear/algebra.h"
#include "./HitRecord.h"
#include "./Hittable.h"
#include "./Hittables.h"
#include "./Interval.h"
#include "./Ray.h"

typedef struct {
    double aspectRatio;
    struct {
        size_t width;
        size_t height;
    } image;
    Vector3 center;
    Vector3 pixel_delta_u;
    Vector3 pixel_delta_v;
    Vector3 pixel00_loc;
} Camera;

Camera Camera_make();
void Camera_initialize(Camera camera[static 1]);
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream);
Vector3 Camera_color(const Ray ray, const Hittables world[static 1]);
void Camera_print(FILE* stream, const Vector3 color);
Camera Camera_make() {
  const Camera result = { .aspectRatio = 16.0 / 9.0, .image.width = 400 };
  return result;
}
void Camera_initialize(Camera camera[static 1]) {
  camera->image.height = camera->image.width / camera->aspectRatio;
  camera->image.height = (camera->image.height < 1) ? 1 : camera->image.height;
  double viewport_height = 2.0;
  double viewport_width =
    viewport_height * ((double)camera->image.width / (double)camera->image.height);
  double focal_length = 1.0;
  camera->center = Vector3_make(0, 0, 0);
  Vector3 viewport_u = Vector3_make(viewport_width, 0, 0);
  Vector3 viewport_v = Vector3_make(0, -viewport_height, 0);
  camera->pixel_delta_u = Vector_scale(1.0 / camera->image.width, viewport_u);
  camera->pixel_delta_v = Vector_scale(1.0 / camera->image.height, viewport_v);
  Vector3 viewport_upper_left = Vector_subtract(
    Vector_subtract(
      Vector_subtract(camera->center, Vector3_make(0, 0, focal_length)),
      Vector_scale(0.5, viewport_u)),
    Vector_scale(0.5, viewport_v));
  camera->pixel00_loc = Vector_add(
    viewport_upper_left,
    Vector_scale(0.5, Vector_add(camera->pixel_delta_u, camera->pixel_delta_v)));
}
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream) {
  Camera_initialize(camera);
  printf("P3\n%zu %zu\n255\n", camera->image.width, camera->image.height);
  for (size_t j = 0; camera->image.height > j; j++) {
    for (size_t i = 0; camera->image.width > i; i++) {
      Vector3 pixel_center = Vector_add(
        camera->pixel00_loc,
        Vector_add(
          Vector_scale(i, camera->pixel_delta_u),
          Vector_scale(j, camera->pixel_delta_v)));
      Vector3 ray_direction = Vector_subtract(pixel_center, camera->center);
      Ray ray = { .direction = ray_direction, .origin = camera->center };
      Camera_print(stream, Camera_color(ray, world));
    }
  }
}
Vector3 Camera_color(const Ray ray, const Hittables world[static 1]) {
  Vector3 result;
  HitRecord record = { 0 };
  if (Hittables_hit(world, ray, Interval_make(0, INFINITY), &record)) {
    result = Hittable_color(record.normal);
  }
  else {
    result = Ray_color(&ray);
  }
  return result;
}
void Camera_print(FILE* stream, const Vector3 color) {
  size_t ir = 255.999 * color.components[0];
  size_t ig = 255.999 * color.components[1];
  size_t ib = 255.999 * color.components[2];
  if (stream) {
    fprintf(stream, "%zu %zu %zu\n", ir, ig, ib);
  }
  else {
    printf("%zu %zu %zu\n", ir, ig, ib);
  }
}

#endif // Camera_H
