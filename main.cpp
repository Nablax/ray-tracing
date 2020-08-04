#include "Png_Image.h"
#include "types.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = glm::normalize(r.at(t) - point3(0,0,-1));
        return 0.5*color(N.x+1, N.y+1, N.z+1);
    }
    vec3 unit_direction = glm::normalize(r.direction());
    t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(){
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal * 0.5 - vertical * 0.5 - vec3(0, 0, focal_length);

    Png_Image png(image_width, image_height);
    for (int row = png.height() - 1; row >= 0; row--) {
        for (int col = 0; col < png.width(); col++) {
            auto u = double(col) / (image_width-1);
            auto v = double(row) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            png.saveColorSeq(pixel_color);
        }
    }
    png.write("6.sphereNormalize.png");
    return 0;
}