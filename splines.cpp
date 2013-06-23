#include "splines.hpp"

glm::vec3 interpolate(float u, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	float u3 = u * u * u;
	float u2 = u * u;
	float f1 = -0.5 * u3 + u2 - 0.5 * u;
	float f2 =  1.5 * u3 - 2.5 * u2 + 1.0;
	float f3 = -1.5 * u3 + 2.0 * u2 + 0.5 * u;
	float f4 =  0.5 * u3 - 0.5 * u2;

	return glm::vec3(
		p0.x * f1 + p1.x * f2 + p2.x * f3 + p3.x * f4,
		p0.y * f1 + p1.y * f2 + p2.y * f3 + p3.y * f4,
		p0.z * f1 + p1.z * f2 + p2.z * f3 + p3.z * f4
	);
}

std::vector<glm::vec3> Splines::generate(unsigned int detail) const {
	std::vector<glm::vec3> points;

	for(unsigned int i = 0; i < _key_points.size(); i++) {
		for(unsigned int u = 0; u < detail; u++) {
			points.push_back(
				interpolate(
					u / static_cast<float>(detail),
					keyPoint(i - 1),
					keyPoint(i),
					keyPoint(i + 1),
					keyPoint(i + 2)
				)
			);
		}
	}

	return points;
}
