//
// Created by cosmos on 8/3/20.
//
#ifndef RAY_TRACING_RAY_HPP
#define RAY_TRACING_RAY_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <types.h>

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
    {}

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};

#endif //RAY_TRACING_RAY_HPP
