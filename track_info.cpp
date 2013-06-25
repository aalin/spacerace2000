#include "track_info.hpp"

#include <glm/gtx/closest_point.hpp>
#include <algorithm>

#include "track_loader.hpp"

const unsigned int DETAIL = 5;

TrackInfo::TrackInfo(const std::vector<glm::vec3>& key_points, float width) : _width(width) {
	TrackLoader track_loader(key_points, DETAIL, width + 30.0, 0.0);

	_length = 0.0;

	for(unsigned int i = 0; i < track_loader.numSectionRects(); i++) {
		TrackLoader::SectionRect current = track_loader.getSectionRect(i);
		TrackLoader::SectionRect next = track_loader.getSectionRect(i + 1);

		glm::vec3 p0 = track_loader.getPoint(i);
		glm::vec3 p1 = track_loader.getPoint(i + 1);

		PointInfo point_info;
		point_info.index = 0.0;
		point_info.center = p0;
		point_info.distance = _length;
		point_info.distance_to_next = glm::distance(p0, p1);
		point_info.angle = 0.0; // TODO: fix this

		point_info.left0 = current.top_left;
		point_info.right0 = current.top_right;
		point_info.left1 = next.top_left;
		point_info.right1 = next.top_right;

		_point_information.push_back(point_info);

		_length += point_info.distance_to_next;
	}
}

glm::vec3 TrackInfo::positionAt(float distance) const {
	while(distance > _length)
		distance -= _length;

	unsigned int index = indexAt(distance);

	const PointInfo& current_point = getPointInfo(index);
	const PointInfo& next_point = getPointInfo(index + 1);

	float into = std::fabs(distance - current_point.distance);
	float t = into / current_point.distance_to_next;

	return glm::mix(current_point.center, next_point.center, t);
}

float TrackInfo::distanceNear(float distance, glm::vec3 position) const {
	while(distance > _length)
		distance -= _length;

	std::vector<PointInfo> point_infos_around_position;

	for(auto it = _point_information.begin(); it != _point_information.end(); it++) {
		if(it->hasPoint(position))
			point_infos_around_position.push_back(*it);
	}

	if(point_infos_around_position.empty())
		return distance;

	std::sort(
		point_infos_around_position.begin(),
		point_infos_around_position.end(),
		[distance](const PointInfo &a, const PointInfo &b) -> bool {
			return std::fabs(a.distance - distance) < std::fabs(b.distance - distance);
		}
	);

	const PointInfo& current_segment = point_infos_around_position[0];

	glm::vec3 a = glm::closestPointOnLine(position, current_segment.left0, current_segment.right0);
	glm::vec3 b = glm::closestPointOnLine(position, current_segment.left1, current_segment.right1);

	float a_dist = glm::distance(position, a);
	float b_dist = glm::distance(position, b);

	float into = a_dist / (a_dist + b_dist);

	return current_segment.distance + current_segment.distance_to_next * into;
}

unsigned int TrackInfo::indexAt(float distance) const {
	for(unsigned int i = 0; i < _point_information.size(); i++)
		if(_point_information[i].distance > distance)
			return i - 1;
	return 0;
}
