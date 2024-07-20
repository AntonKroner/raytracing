#ifndef Camera_H
#define Camera_H

#include <stdio.h>
#include "linear/algebra.h"
#include "random.h"
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
    struct {
        Vector3 delta_u;
        Vector3 delta_v;
        size_t samples;
        double scale;
    } pixel;
    Vector3 pixel00_loc;
} Camera;

Camera Camera_make();
void Camera_initialize(Camera camera[static 1]);
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream);
Vector3 Camera_color(const Ray ray, const Hittables world[static 1]);
void Camera_print(FILE* stream, const Vector3 color);
Vector3 sampleSquare() {
  return Vector3_make(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}
Ray Camera_ray(Camera camera[static 1], size_t i, size_t j) {
  Vector3 offset = sampleSquare();
  Vector3 sample = Vector_add(
    camera->pixel00_loc,
    Vector_add(
      Vector_scale(i + offset.components[0], camera->pixel.delta_u),
      Vector_scale(j + offset.components[1], camera->pixel.delta_v)));
  Vector3 direction = Vector_subtract(sample, camera->center);
  Ray result = { .direction = direction, .origin = camera->center };
  return result;
}
Camera Camera_make() {
  const Camera result = {
    .aspectRatio = 16.0 / 9.0,
    .image.width = 400,
    .pixel.samples = 100,
  };
  return result;
}
void Camera_initialize(Camera camera[static 1]) {
  camera->image.height = camera->image.width / camera->aspectRatio;
  camera->image.height = (camera->image.height < 1) ? 1 : camera->image.height;
  camera->pixel.scale = 1.0 / camera->pixel.samples;
  double viewport_height = 2.0;
  double viewport_width =
    viewport_height * ((double)camera->image.width / (double)camera->image.height);
  double focal_length = 1.0;
  camera->center = Vector3_make(0, 0, 0);
  Vector3 viewport_u = Vector3_make(viewport_width, 0, 0);
  Vector3 viewport_v = Vector3_make(0, -viewport_height, 0);
  camera->pixel.delta_u = Vector_scale(1.0 / camera->image.width, viewport_u);
  camera->pixel.delta_v = Vector_scale(1.0 / camera->image.height, viewport_v);
  Vector3 viewport_upper_left = Vector_subtract(
    Vector_subtract(
      Vector_subtract(camera->center, Vector3_make(0, 0, focal_length)),
      Vector_scale(0.5, viewport_u)),
    Vector_scale(0.5, viewport_v));
  camera->pixel00_loc = Vector_add(
    viewport_upper_left,
    Vector_scale(0.5, Vector_add(camera->pixel.delta_u, camera->pixel.delta_v)));
}
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream) {
  Camera_initialize(camera);
  printf("P3\n%zu %zu\n255\n", camera->image.width, camera->image.height);
  for (size_t j = 0; camera->image.height > j; j++) {
    for (size_t i = 0; camera->image.width > i; i++) {
      Vector3 pixel = Vector3_fill(0);
      for (size_t sample = 0; camera->pixel.samples > sample; sample++) {
        Ray ray = Camera_ray(camera, i, j);
        pixel = Vector_add(pixel, Camera_color(ray, world));
      }
      Camera_print(stream, Vector_scale(camera->pixel.scale, pixel));
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
  static const Interval intensity = { .min = 0.000, .max = 0.999 };
  size_t red = 256 * Interval_clamp(intensity, color.components[0]);
  size_t green = 256 * Interval_clamp(intensity, color.components[1]);
  size_t blue = 256 * Interval_clamp(intensity, color.components[2]);
  if (stream) {
    fprintf(stream, "%zu %zu %zu\n", red, green, blue);
  }
  else {
    printf("%zu %zu %zu\n", red, green, blue);
  }
}

#endif // Camera_H
