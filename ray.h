//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_RAY_H
#define SIMPLE_SOFTRT_RAY_H

#include "vec3.h"

// ray = origin + dir
class ray {
public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    const point3 &origin() const { return orig; }

    const vec3 &direction() const { return dir; }

    point3 at(double t) const { return orig + dir * t; }

private:
    point3 orig;
    vec3 dir;
};

#endif //SIMPLE_SOFTRT_RAY_H
