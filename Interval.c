#include "Interval.h"
#include <tgmath.h>

Interval Interval_make(double min, double max) {
  const Interval result = { .min = min, .max = max };
  return result;
}
Interval Interval_empty() {
  const Interval result = { .min = INFINITY, .max = +INFINITY };
  return result;
}
Interval Interval_universe() {
  const Interval result = { .min = -INFINITY, .max = INFINITY };
  return result;
}
double Interval_size(const Interval interval) {
  return interval.max - interval.min;
}
bool Interval_contains(const Interval interval, const double x) {
  return interval.min <= x && x <= interval.max;
}
bool Interval_surrounds(const Interval interval, const double x) {
  return interval.min < x && x < interval.max;
}
double Interval_clamp(const Interval interval, double x) {
  if (x < interval.min) {
    return interval.min;
  }
  if (x > interval.max) {
    return interval.max;
  }
  return x;
}
