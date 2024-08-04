#include "Camera.h"
#include <stdio.h>
#include <tgmath.h>
#include "linear/algebra.h"
#include "random.h"
#include "./HitRecord.h"
#include "./Hittables.h"
#include "./Interval.h"
#include "./Ray.h"
#include "./Material/Material.h"

static void initialize(Camera camera[static 1]);
static Vector3 Camera_color(const Ray ray, const Hittables world[static 1], size_t depth);
static void print(FILE* stream, const Vector3 color);
static Vector3 sampleSquare();
static Ray Camera_ray(Camera camera[static 1], size_t i, size_t j);

Camera Camera_make() {
  const Camera result = {
    .aspectRatio = 16.0 / 9.0,
    .image.width = 400,
    .pixel.samples = 100,
    .verticalFov = 90,
    .position = Vector3_fill(0),
    .up = Vector3_make(0, 1, 0),
    .lookAt = Vector3_make(0, 0, -1),
    .defocus.distance = 10,
    .defocus.angle = 0,
  };
  return result;
}
static void initialize(Camera camera[static 1]) {
  camera->image.height = camera->image.width / camera->aspectRatio;
  camera->image.height = (camera->image.height < 1) ? 1 : camera->image.height;
  camera->pixel.scale = 1.0 / camera->pixel.samples;
  camera->maxDepth = 50;
  camera->center = camera->position;

  double h = tan(M_PI / 360 * camera->verticalFov);
  double viewport_height = 2.0 * h * camera->defocus.distance;
  double viewport_width =
    viewport_height * ((double)camera->image.width / (double)camera->image.height);

  camera->basis.w = Vector_normalize(Vector_subtract(camera->position, camera->lookAt));
  camera->basis.u = Vector_normalize(Vector_cross(camera->up, camera->basis.w));
  camera->basis.v = Vector_cross(camera->basis.w, camera->basis.u);

  Vector3 viewport_u = Vector_scale(viewport_width, camera->basis.u);
  Vector3 viewport_v = Vector_scale(-viewport_height, camera->basis.v);

  camera->pixel.delta_u = Vector_scale(1.0 / camera->image.width, viewport_u);
  camera->pixel.delta_v = Vector_scale(1.0 / camera->image.height, viewport_v);
  Vector3 viewport_upper_left = Vector_subtract(
    Vector_subtract(
      Vector_subtract(
        camera->center,
        Vector_scale(camera->defocus.distance, camera->basis.w)),
      Vector_scale(0.5, viewport_u)),
    Vector_scale(0.5, viewport_v));
  camera->pixel00_loc = Vector_add(
    viewport_upper_left,
    Vector_scale(0.5, Vector_add(camera->pixel.delta_u, camera->pixel.delta_v)));

  double defocus_radius =
    camera->defocus.distance * tan(M_PI / 360 * camera->defocus.angle);
  camera->defocus.u = Vector_scale(defocus_radius, camera->basis.u);
  camera->defocus.v = Vector_scale(defocus_radius, camera->basis.v);
}
void Camera_render(Camera camera[static 1], const Hittables world[static 1], FILE* stream) {
  initialize(camera);
  printf("P3\n%zu %zu\n255\n", camera->image.width, camera->image.height);
  for (size_t j = 0; camera->image.height > j; j++) {
    for (size_t i = 0; camera->image.width > i; i++) {
      Vector3 pixel = Vector3_fill(0);
      for (size_t sample = 0; camera->pixel.samples > sample; sample++) {
        Ray ray = Camera_ray(camera, i, j);
        pixel = Vector_add(pixel, Camera_color(ray, world, camera->maxDepth));
      }
      print(stream, Vector_scale(camera->pixel.scale, pixel));
    }
  }
}
static Vector3 Camera_color(const Ray ray, const Hittables world[static 1], size_t depth) {
  Vector3 result;
  HitRecord record = { 0 };
  if (!depth) {
    result = Vector3_fill(0);
  }
  else if (Hittables_hit(world, ray, Interval_make(0.001, INFINITY), &record)) {
    Ray scattered = { 0 };
    Vector3 attenuation = { 0 };
    if (
      Material_scatter(*(Material*)record.material, ray, record, &attenuation, &scattered)) {
      result = Vector_multiply(attenuation, Camera_color(scattered, world, depth - 1));
    }
    else {
      result = Vector3_fill(0);
    }
  }
  else {
    result = Ray_color(&ray);
  }
  return result;
}
static void print(FILE* stream, const Vector3 color) {
  static const Interval intensity = { .min = 0.000, .max = 0.999 };
  size_t red = 256 * Interval_clamp(intensity, sqrt(fmax(0, color.components[0])));
  size_t green = 256 * Interval_clamp(intensity, sqrt(fmax(0, color.components[1])));
  size_t blue = 256 * Interval_clamp(intensity, sqrt(fmax(0, color.components[2])));
  fprintf(stream ? stream : stdout, "%zu %zu %zu\n", red, green, blue);
}
static Vector3 sampleSquare() {
  return Vector3_make(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}
static Vector3 sampleDefocusDisk(const Camera camera) {
  Vector3 p = Vector3_randomInUnitDisk();
  return Vector3_add(
    camera.center,
    Vector3_add(
      Vector3_scale(p.components[0], camera.defocus.u),
      Vector3_scale(p.components[1], camera.defocus.v)));
}
static Ray Camera_ray(Camera camera[static 1], size_t i, size_t j) {
  Vector3 offset = sampleSquare();
  Vector3 sample = Vector_add(
    camera->pixel00_loc,
    Vector_add(
      Vector_scale(i + offset.components[0], camera->pixel.delta_u),
      Vector_scale(j + offset.components[1], camera->pixel.delta_v)));
  Vector3 origin =
    (camera->defocus.angle <= 0) ? camera->center : sampleDefocusDisk(*camera);
  Vector3 direction = Vector_subtract(sample, origin);
  Ray result = { .direction = direction, .origin = origin };
  return result;
}
