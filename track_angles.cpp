#include "track_angles.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>
#include "logger.hpp"

glm::vec3 getPoint(const std::vector<glm::vec3> points, int i)  {
	while(i < 0)
		i += points.size();
	return points[i % points.size()];
}

float calculateAngle(const glm::vec3 prev, const glm::vec3 curr, const glm::vec3 next) {
	const glm::vec2 f_1 = glm::normalize(glm::vec2(next - curr));
	const glm::vec2 f_2 = glm::normalize(glm::vec2(curr - prev));

	return -glm::angle(f_1, f_2);
}

TrackAngles::TrackAngles(const std::vector<glm::vec3>& points)
{
	for(unsigned int i = 0; i < points.size(); i++) {
		const glm::vec3 prev(getPoint(points, i - 1));
		const glm::vec3 curr(getPoint(points, i));
		const glm::vec3 next(getPoint(points, i + 1));

		_angles.push_back(calculateAngle(prev, curr, next));
	}
}

float TrackAngles::smoothAngleAt(int i) const {
	return angleAt(i);
}
