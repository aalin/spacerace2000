#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>

struct Triangle {
	glm::vec3 a, b, c;

	glm::vec3 surfaceNormal() const {
		return glm::normalize(glm::cross(c - a, b - a));
	}
};

#endif
