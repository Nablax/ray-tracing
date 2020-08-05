//
// Created by cosmos on 8/4/20.
//

#ifndef RAY_TRACING_UTILITY_H
#define RAY_TRACING_UTILITY_H

#include <glm/glm.hpp>
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

#endif //RAY_TRACING_UTILITY_H
