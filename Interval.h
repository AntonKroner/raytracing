#ifndef Interval_H
#define Interval_H

#include <tgmath.h>
typedef struct {
    double min, max;
} Interval;

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

#endif // Interval_H
