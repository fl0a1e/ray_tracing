//
// Created by 13240 on 2025/10/15.
//

#ifndef SIMPLE_SOFTRT_CAMERA_H
#define SIMPLE_SOFTRT_CAMERA_H

#include "hittable.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

class camera {
public:
    int image_width = 100;
    double aspect_ratio = 1.0;
    int samples_per_pixel = 10; // SSAA
    int max_depth = 10; // Maximum number of ray bounces into scene

    // Public Camera Parameters
    void render(const hittable &world, const char *filename) {
        initialize();

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(pixels, pixel_color * pixel_samples_scale);
            }
        }

        std::clog << "\rDone.            \n";
        stbi_write_png(filename, image_width, image_height, channels, pixels.data(), image_width * channels);
    }

private:
    // Private Camera Variables
    int image_height;   // Rendered image height
    double pixel_samples_scale;
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3 pixel_delta_u;  // Offset to pixel to the right
    vec3 pixel_delta_v;  // Offset to pixel below
    int channels = 3; // RGB
    std::vector<uint8_t> pixels; // to stb

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = point3(0, 0, 0);

        // Camera
        double focal_length = 1.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // viewport_uv
        vec3 viewport_u = vec3(viewport_width, 0, 0);
        vec3 viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel in 3D
        vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        pixels.clear();
    }

    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                            + (i + offset.x()) * pixel_delta_u
                            + (j + offset.y()) * pixel_delta_v;

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    color ray_color(const ray &r, int depth, const hittable &world) const {
        if(depth <= 0)
            return color(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {
            vec3 direction = random_on_hemisphere(rec.normal);
            return 0.1 * ray_color(ray(rec.p, direction), depth-1, world);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0); // [-1-1] to [0-1]
        return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif //SIMPLE_SOFTRT_CAMERA_H
