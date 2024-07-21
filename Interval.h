#ifndef Interval_H
#define Interval_H

typedef struct {
    double min, max;
} Interval;

Interval Interval_make(double min, double max);
Interval Interval_empty();
Interval Interval_universe();
double Interval_size(const Interval interval);
bool Interval_contains(const Interval interval, const double x);
bool Interval_surrounds(const Interval interval, const double x);
double Interval_clamp(const Interval interval, double x);

#endif // Interval_H
