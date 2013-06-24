#include "track_info.hpp"
#include "splines.hpp"

const float WIDTH = 10.0f;

struct LeftRight {
	glm::vec3 left;
	glm::vec3 right;
};

glm::vec3 getPoint(const std::vector<glm::vec3> points, unsigned int i) {
	return points[i % points.size()];
}

LeftRight pointVertices(const std::vector<glm::vec3> points, unsigned int i) {
	glm::vec3 p0(getPoint(points, i));
	glm::vec3 p1(getPoint(points, i + 1));

	glm::vec3 delta(p0 - p1);

	glm::vec3 outwards(glm::normalize(glm::vec3(delta.y, -delta.x, 0)));

	glm::vec3 left(p0 + outwards * -WIDTH);
	glm::vec3 right(p0 + outwards * WIDTH);

	return { left, right };
}

TrackInfo::TrackInfo(const std::vector<glm::vec3>& key_points) {
	std::vector<glm::vec3> points(Splines(key_points).generate(5));

	_length = 0.0;

	for(unsigned int i = 0; i < points.size(); i++) {
		glm::vec3 p0 = getPoint(points, i);
		glm::vec3 p1 = getPoint(points, i + 1);

		LeftRight lr0 = pointVertices(points, i);
		LeftRight lr1 = pointVertices(points, i + 1);

		PointInfo point_info;
		point_info.index = 0.0;
		point_info.center = p0;
		point_info.distance = _length;
		point_info.distance_to_next = glm::distance(p0, p1);
		point_info.angle = 0.0; // TODO: fix this

		point_info.left0 = lr0.left;
		point_info.right0 = lr0.right;
		point_info.left1 = lr1.left;
		point_info.right1 = lr1.right;

		_point_information.push_back(point_info);

		_length += point_info.distance_to_next;
	}
}

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

glm::vec3 TrackInfo::positionAt(float distance) const {
	while(distance > _length)
		distance -= _length;

	unsigned int index = indexAt(distance);

	const PointInfo& current_point = getPointInfo(index);
	const PointInfo& next_point = getPointInfo(index + 1);

	float into = std::fabs(distance - current_point.distance);
	float t = into / current_point.distance_to_next;

	return glm::vec3(
		lerp(current_point.center.x, next_point.center.x, t),
		lerp(current_point.center.y, next_point.center.y, t),
		lerp(current_point.center.z, next_point.center.z, t)
	);
}

float TrackInfo::distanceNear(float distance, glm::vec3 position) const {
	return 0.0;
}

unsigned int TrackInfo::indexAt(float distance) const {
	for(unsigned int i = 0; i < _point_information.size(); i++)
		if(_point_information[i].distance > distance)
			return i - 1;
	return 0;
}
