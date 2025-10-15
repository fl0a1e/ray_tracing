//
// Created by 13240 on 2025/10/15.
//

#ifndef SIMPLE_SOFTRT_INTERVAL_H
#define SIMPLE_SOFTRT_INTERVAL_H

class interval {
public:
    double max, min;

    interval() : max(-infinity), min(+infinity) {}

    interval(double min, double max) : max(max), min(min) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif //SIMPLE_SOFTRT_INTERVAL_H
