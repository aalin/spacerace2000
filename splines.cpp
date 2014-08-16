#include "splines.hpp"
#include <glm/gtx/spline.hpp>

std::vector<glm::vec3> Splines::generate(unsigned int detail) const {
	std::vector<glm::vec3> points;

	for(unsigned int i = 0; i < _key_points.size(); i++) {
		for(unsigned int u = 0; u < detail; u++) {
			glm::vec3 new_point = glm::catmullRom(
				keyPoint(i),
				keyPoint(i + 1),
				keyPoint(i + 2),
				keyPoint(i + 3),
				u / static_cast<float>(detail)
			);

			if(points.empty())
				points.push_back(new_point);
			else if(glm::distance(points.back(), new_point) > 5.0)
				points.push_back(new_point);
		}
	}

	return points;
}
