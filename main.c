#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <tgmath.h>
#include <getopt.h>
#include "linear/algebra.h"
#include "./Camera.h"
#include "./Hittable/Hittable.h"
#include "./Hittables.h"

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
  Camera camera = Camera_make();
  Hittables* world = Hittables_create();
  Hittables_add(world, Hittable_Sphere_make(Vector3_make(0, 0, -1.0), 0.5));
  Hittables_add(world, Hittable_Sphere_make(Vector3_make(0, -100.5, -1.0), 100));
  Camera_render(&camera, world, 0);
  Hittables_destroy(world);
  return result;
}
