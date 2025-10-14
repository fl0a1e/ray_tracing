//
// Created by 13240 on 2025/10/14.
//

#ifndef SIMPLE_SOFTRT_HITTABLE_H
#define SIMPLE_SOFTRT_HITTABLE_H

class hit_record{
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal; // 判断是否反转法线
    }
};

class hittable{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec)const  = 0;
};

#endif //SIMPLE_SOFTRT_HITTABLE_H
