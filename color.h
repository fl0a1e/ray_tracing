//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_COLOR_H
#define SIMPLE_SOFTRT_COLOR_H

#include "vec3.h"

using color = vec3;

void write_color(std::vector<uint8_t> &pixels, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // [0, 1] to uint8_t [0, 255]
    int ir = int(255.999 * r);
    int ig = int(255.999 * g);
    int ib = int(255.999 * b);

    pixels.emplace_back(ir);
    pixels.emplace_back(ig);
    pixels.emplace_back(ib);
}

#endif //SIMPLE_SOFTRT_COLOR_H
