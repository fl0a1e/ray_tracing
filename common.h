//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_COMMON_H
#define SIMPLE_SOFTRT_COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif //SIMPLE_SOFTRT_COMMON_H
