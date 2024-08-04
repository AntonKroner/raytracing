#include <stdbool.h>
#include <stdlib.h>
#include <tgmath.h>
#include <getopt.h>
#include "linear/algebra.h"
#include "./Camera.h"
#include "./Hittable/Hittable.h"
#include "./Material/Material.h"
#include "./Hittables.h"

int main(int argc, char* argv[static argc + 1]) {
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

  camera.position = Vector3_make(-2, 2, 1);
  camera.lookAt = Vector3_make(0, 0, -1);
  camera.up = Vector3_make(0, 1, 0);
  camera.verticalFov = 90;
  camera.defocus.angle = 10.0;
  camera.defocus.distance = 3.4;

  Camera_render(&camera, world, 0);
  Hittables_destroy(world);
  return EXIT_SUCCESS;
}
