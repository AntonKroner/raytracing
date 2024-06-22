#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include "linear/algebra.h"

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

  printf("P3\n%zu %zu\n255\n", image_width, image_height);
  for (size_t j = 0; image_height > j; j++) {
    for (size_t i = 0; image_width > i; i++) {
      color_print(
        0,
        Vector3_make((double)i / (image_width - 1), (double)j / (image_height - 1), 0.0));
    }
  }
  return result;
}
