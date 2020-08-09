#include "Png_Image.h"
#include "physics/hittable_list.h"
#include "physics/sphere.h"
#include "camera.h"
#include "texture/material.h"

color ray_color(const ray& r, const hittable &world, int depth) {
    hit_record rec;
    if (depth <= 0)
        return color(0,0,0);
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0,0,0);
    }
    vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

//    for (int a = -11; a < 11; a++) {
//        for (int b = -11; b < 11; b++) {
//            auto choose_mat = random_double();
//            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
//
//            if (glm::distance(center, point3(4, 0.2, 0)) > 0.9) {
//                shared_ptr<material> sphere_material;
//
//                if (choose_mat < 0.8) {
//                    // diffuse
//                    auto albedo = random_vec3() * random_vec3();
//                    sphere_material = make_shared<lambertian>(albedo);
//                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                } else if (choose_mat < 0.95) {
//                    // metal
//                    auto albedo = random_vec3(0.5, 1);
//                    auto fuzz = random_double(0, 0.5);
//                    sphere_material = make_shared<metal>(albedo, fuzz);
//                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                } else {
//                    // glass
//                    sphere_material = make_shared<dielectric>(1.5);
//                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                }
//            }
//        }
//    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main(){
    // Image

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 5;

    // World

    auto world = random_scene();

    // Camera

    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    Png_Image png(image_width, image_height);
    for (int row = 0; row < png.height(); row++) {
        for (int col = 0; col < png.width(); col++) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (col + random_double()) / (image_width - 1);
                auto v = (row + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            png.saveColor(pixel_color, row, col, samples_per_pixel);
        }
    }
    png.write("13.randomScene.png");
    return 0;
}