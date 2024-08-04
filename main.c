#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <tgmath.h>
#include <getopt.h>
#include "linear/algebra.h"
#include "./Camera.h"
#include "./Hittable/Hittable.h"
#include "./Material/Material.h"
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

  Material material_ground =
    Material_make(Material_lambertian, Vector3_make(0.8, 0.8, 0.0), 0);
  Material material_center =
    Material_make(Material_lambertian, Vector3_make(0.1, 0.2, 0.5), 0);
  Material material_left =
    Material_make(Material_dielectric, Vector3_make(0.8, 0.8, 0.8), 1.5);
  Material material_bubble =
    Material_make(Material_dielectric, Vector3_make(0.8, 0.6, 0.2), 1.0 / 1.5);
  Material material_right =
    Material_make(Material_metal, Vector3_make(0.8, 0.6, 0.2), 1.0);

  Hittables_add(
    world,
    Hittable_Sphere_make(Vector3_make(0, -100.5, -1.0), 100, &material_ground));
  Hittables_add(
    world,
    Hittable_Sphere_make(Vector3_make(0, 0, -1.2), 0.5, &material_center));
  Hittables_add(
    world,
    Hittable_Sphere_make(Vector3_make(-1, 0, -1.0), 0.5, &material_left));
  Hittables_add(
    world,
    Hittable_Sphere_make(Vector3_make(-1, 0, -1.0), 0.4, &material_bubble));
  Hittables_add(
    world,
    Hittable_Sphere_make(Vector3_make(1, 0, -1.0), 0.5, &material_right));
  Camera_render(&camera, world, 0);
  Hittables_destroy(world);
  return result;
}
