//
// Created by 13240 on 2025/10/15.
//

#ifndef SIMPLE_SOFTRT_MATERIAL_H
#define SIMPLE_SOFTRT_MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const {
        return false;
    }
};

class lambertian : public material{
public:
    lambertian(const color& albedo):albedo(albedo){}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const override {
        // ToDo

        return true;
    }
private:
    color albedo;
};

#endif //SIMPLE_SOFTRT_MATERIAL_H
