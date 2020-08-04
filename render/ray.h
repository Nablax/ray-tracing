//
// Created by cosmos on 8/3/20.
//
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef RAY_TRACING_RAY_HPP
#define RAY_TRACING_RAY_HPP
class ray {
public:
    ray() {}
    ray(const glm::dvec3 origin, const glm::dvec3 direction)
            : orig(origin), dir(direction)
    {}

    glm::dvec3 origin() const  { return orig; }
    glm::dvec3 direction() const { return dir; }

    glm::dvec3 at(double t) const {
        return orig + t * dir;
    }

public:
    glm::dvec3 orig;
    glm::dvec3 dir;
};

#endif //RAY_TRACING_RAY_HPP
