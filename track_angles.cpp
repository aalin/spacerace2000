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

float TrackAngles::calculateSmoothAngle(int i) const {
	const int radius = 5;

	float total = 0.0;

	const float PI = 3.14159265358979;

	for(int x = -radius; x < radius; x++) {
		float f = x * 1.0 / radius;
		total += angleAt(i) * ((std::cos(f * PI) + 1.0) / 2.0);
	}

	return total;
}

TrackAngles::TrackAngles(const std::vector<glm::vec3>& points)
{
	for(unsigned int i = 0; i < points.size(); i++) {
		const glm::vec3 prev(getPoint(points, i - 1));
		const glm::vec3 curr(getPoint(points, i));
		const glm::vec3 next(getPoint(points, i + 1));

		_angles.push_back(calculateAngle(prev, curr, next));
	}

	for(unsigned int i = 0; i < points.size(); i++) {
		_smooth_angles.push_back(calculateSmoothAngle(i));
	}
}
