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

class lambertian : public material {
public:
    lambertian(const color &albedo) : albedo(albedo) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const override {
        // N+R,在法线半球的某个随机方向上（除非 R=0）
        auto scatter_direction = rec.normal + random_unit_vector();

        // 处理 R=0 的情况
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class metal : public material {
public:
    metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1){}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
    const override {
        vec3 reflectd = reflect(r_in.direction(), rec.normal);
        reflectd = unit_vector(reflectd) + (fuzz * random_unit_vector()); // Fuzzy Reflection
        scattered = ray(rec.p, reflectd);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);;
    }

private:
    color albedo;
    double fuzz;
};

#endif //SIMPLE_SOFTRT_MATERIAL_H
