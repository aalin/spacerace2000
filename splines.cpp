#include "splines.hpp"
#include <glm/gtx/spline.hpp>

std::vector<glm::vec3> Splines::generate(unsigned int detail) const {
	std::vector<glm::vec3> points;

	for(unsigned int i = 0; i < _key_points.size(); i++) {
		for(unsigned int u = 0; u < detail; u++) {
			points.push_back(
				glm::catmullRom(
					keyPoint(i),
					keyPoint(i + 1),
					keyPoint(i + 2),
					keyPoint(i + 3),
					u / static_cast<float>(detail)
				)
			);
		}
	}

	return points;
}
