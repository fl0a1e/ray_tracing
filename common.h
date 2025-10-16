//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_COMMON_H
#define SIMPLE_SOFTRT_COMMON_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline void print_progress(double progress) {
    int barWidth = 50;
    std::cout << "\r[";

    int pos = static_cast<int>(barWidth * progress);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] "
            << std::fixed << std::setprecision(1)
            << progress * 100.0 << " %";
    std::cout.flush();
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif //SIMPLE_SOFTRT_COMMON_H
