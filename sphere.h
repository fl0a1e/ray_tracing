//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_SPHERE_H
#define SIMPLE_SOFTRT_SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3 &center, double radius, std::shared_ptr<material> mat)
    : center(center), radius(std::fmax(0, radius)), mat(mat) {
        // Initialize the material pointer `mat`
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a; // 尝试 第一个解（前表面交点）
        if (!ray_t.surrounds(root)) { //
            root = (h + sqrtd) / a; // 尝试第二个解
            if (!ray_t.surrounds(root))
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};

#endif //SIMPLE_SOFTRT_SPHERE_H
