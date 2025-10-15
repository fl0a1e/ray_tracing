//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_COLOR_H
#define SIMPLE_SOFTRT_COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_color(std::vector<uint8_t> &pixels, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // [0, 1] to uint8_t [0, 255]
    static const interval intensity(0.000, 0.999);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

    pixels.emplace_back(ir);
    pixels.emplace_back(ig);
    pixels.emplace_back(ib);
}

#endif //SIMPLE_SOFTRT_COLOR_H
