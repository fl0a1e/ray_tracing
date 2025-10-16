//
// Created by 13240 on 2025/10/15.
//

#ifndef SIMPLE_SOFTRT_CAMERA_H
#define SIMPLE_SOFTRT_CAMERA_H

#include "hittable.h"
#include "material.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

class camera {
public:
    int image_width = 100;
    double aspect_ratio = 1.0;
    int samples_per_pixel = 10; // SSAA
    int max_depth = 10; // Maximum number of ray bounces into scene

    double vfov = 90; // Vertical view angle (field of view)
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);

    double defocus_angle = 0;   // Variation angle of rays through each pixel
    double focus_dist = 10;     // Distance from camera lookfrom point to plane of perfect focus

    // Public Camera Parameters
    void render(const hittable &world, const char *filename) {
        initialize();

        for (int j = 0; j < image_height; j++) {
            print_progress(double(j + 1) / image_height);
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(pixels, pixel_color * pixel_samples_scale);
            }
        }

        std::clog << "\nDone.            \n";
        stbi_write_png(filename, image_width, image_height, channels, pixels.data(), image_width * channels);
    }

private:
    // Private Camera Variables
    int image_height;       // Rendered image height
    double pixel_samples_scale; // spp
    point3 center;          // Camera center
    point3 pixel00_loc;     // Location of pixel 0, 0
    vec3 pixel_delta_u;     // Offset to pixel to the right
    vec3 pixel_delta_v;     // Offset to pixel below
    vec3 u, v, w;           // Camera frame basis vectors
    vec3   defocus_disk_u;  // Defocus disk horizontal radius
    vec3   defocus_disk_v;  // Defocus disk vertical radius
    int channels = 3;       // RGB
    std::vector<uint8_t> pixels; // to stb

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = lookfrom;

        // Camera
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        double viewport_height = 2 * h * focus_dist;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the u,v,w
        w = unit_vector( lookfrom - lookat);  // lookdir
        u = unit_vector(cross(vup, w));  // right
        v = cross(w, u); // up

        // viewport_uv
        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel in 3D
        vec3 viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

        pixels.clear();
    }

    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the defocus disk and directed at a randomly
        // sampled point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                            + (i + offset.x()) * pixel_delta_u
                            + (j + offset.y()) * pixel_delta_v;

        auto ray_origin =  (defocus_angle <= 0) ? center : defocus_disk_sample();;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    color ray_color(const ray &r, int depth, const hittable &world) const {
        if(depth <= 0)
            return color(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, depth-1, world);
            }
            return color(0, 0, 0);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0); // [-1-1] to [0-1]
        return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif //SIMPLE_SOFTRT_CAMERA_H
