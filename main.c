#include "HitRecord.h"
#include "Hittable.h"
#include "Hittables.h"
#include "Sphere.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <tgmath.h>
#include "linear/algebra.h"
#include "./Ray.h"

Vector3 color(const Ray ray, Hittables world[static 1]) {
  Vector3 result;
  HitRecord record = { 0 };
  if (Hittables_hit(world, ray, 0, INFINITY, &record)) {
    result = Hittable_color(record.normal);
  }
  else {
    result = Ray_color(&ray);
  }
  return result;
}

void color_print(FILE* stream, const Vector3 color) {
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
void logEnviron() {
  extern char** environ;
  printf("environ: \n");
  char** s = environ;
  for (; *s; s++) {
    printf("%s\n", *s);
  }
}

int main(int argc, char* argv[static argc + 1]) {
  int result = EXIT_FAILURE;
  extern char* optarg;
  int index = 0;
  int option = 0;
  int flag = 0;
  const struct option options[] = {
    {"input", required_argument,     0, 'i'},
    { "flag",       no_argument, &flag,   1},
    {      0,                 0,     0,   0}
  };
  while (option != EOF) {
    option = getopt_long(argc, argv, "", options, &index);
    switch (option) {
      case 0:
        break;
      case '?':
        printf("Error case.");
        break;
      case 'i':
        printf("input: %s\n", optarg);
    }
  }
  double aspectRatio = 16.0 / 9.0;
  size_t image_width = 400;
  size_t image_height = image_width / aspectRatio;
  image_height = (image_height < 1) ? 1 : image_height;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * ((double)image_width / (double)image_height);
  double focal_length = 1.0;
  Vector3 camera_center = Vector3_make(0, 0, 0);
  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  Vector3 viewport_u = Vector3_make(viewport_width, 0, 0);
  Vector3 viewport_v = Vector3_make(0, -viewport_height, 0);
  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  Vector3 pixel_delta_u = Vector_scale(1.0 / image_width, viewport_u);
  Vector3 pixel_delta_v = Vector_scale(1.0 / image_height, viewport_v);
  // Calculate the location of the upper left pixel.
  Vector3 viewport_upper_left = Vector_subtract(
    Vector_subtract(
      Vector_subtract(camera_center, Vector3_make(0, 0, focal_length)),
      Vector_scale(0.5, viewport_u)),
    Vector_scale(0.5, viewport_v));
  Vector3 pixel00_loc = Vector_add(
    viewport_upper_left,
    Vector_scale(0.5, Vector_add(pixel_delta_u, pixel_delta_v)));

  Hittables* world = Hittables_create();
  Hittables_add(world, Sphere_make(Vector3_make(0, 0, -1.0), 0.5));
  Hittables_add(world, Sphere_make(Vector3_make(0, -100.5, -1.0), 100));

  printf("P3\n%zu %zu\n255\n", image_width, image_height);
  for (size_t j = 0; image_height > j; j++) {
    for (size_t i = 0; image_width > i; i++) {
      Vector3 pixel_center = Vector_add(
        pixel00_loc,
        Vector_add(Vector_scale(i, pixel_delta_u), Vector_scale(j, pixel_delta_v)));
      Vector3 ray_direction = Vector_subtract(pixel_center, camera_center);
      Ray ray = { .direction = ray_direction, .origin = camera_center };
      color_print(0, color(ray, world));
    }
  }
  Hittables_destroy(world);
  return result;
}
