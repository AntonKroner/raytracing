#include "Hittables.h"
#include <stdlib.h>
#include <string.h>
#include "rxi/Array.h"
#include "./Hittable/Hittable.h"
#include "./HitRecord.h"
#include "./Interval.h"
#include "./Ray.h"

Hittables* Hittables_create() {
  Hittables* result = calloc(1, sizeof(*result));
  result->list = calloc(sizeof(*result->list), 1);
  Array_init(result->list);
  return result;
}
void Hittables_destroy(Hittables* hittables) {
  Array_deinit(hittables->list);
  free(hittables->list);
  free(hittables);
  hittables = 0;
}
void Hittables_clear(Hittables hittables[static 1]) {
  Array_clear(hittables->list);
}
bool Hittables_hit(
  const Hittables hittables[static 1],
  const Ray ray,
  Interval interval,
  HitRecord record[static 1]) {
  HitRecord newRecord = { 0 };
  bool hit = false;
  double closest = interval.max;
  for (size_t i = 0; hittables->list->length > i; i++) {
    if (Hittable_hit(
          hittables->list->data[i],
          ray,
          Interval_make(interval.min, closest),
          &newRecord)) {
      hit = true;
      closest = newRecord.t;
      memcpy(record, &newRecord, sizeof(HitRecord));
    }
  }
  return hit;
}
