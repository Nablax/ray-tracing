//
// Created by cosmos on 8/4/20.
//

#ifndef RAY_TRACING_UTILITY_H
#define RAY_TRACING_UTILITY_H

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

using color = glm::dvec3;
using point3 = glm::dvec3;
using vec3 = glm::dvec3;

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double sqrt2div2 = 0.70710678;
const double sqrt3div3 = 0.57735;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline vec3 random_vec3(){
    return vec3(random_double(), random_double(), random_double());
}

inline vec3 random_vec3(double min, double max){
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1,1);
        if (dot(p , p) >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - dot(r_out_perp, r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (dot(p, p) >= 1) continue;
        return p;
    }
}

#endif //RAY_TRACING_UTILITY_H
