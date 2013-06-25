#include "track_loader.hpp"
#include "splines.hpp"

TrackLoader::TrackLoader(std::vector<glm::vec3> key_points, float width, float height)
	: _width(width), _height(height) {
	_points = Splines(key_points).generate(30);

	for(unsigned int i = 0; i < _points.size(); i++)
		_section_rects.push_back(generateSectionRect(i));
}

TrackLoader::SectionRect TrackLoader::generateSectionRect(unsigned int i) const {
	glm::vec3 current(getPoint(i));;
	glm::vec3 next(getPoint(i + 1));

	glm::vec3 delta(current - next);

	glm::vec3 outwards(glm::normalize(glm::vec3(delta.y, -delta.x, 0)));

	glm::vec3 top_left(current + outwards * -_width);
	glm::vec3 top_right(current + outwards * _width);
	glm::vec3 bottom_left(top_left - glm::vec3(0.0, 0.0, _height));
	glm::vec3 bottom_right(top_right - glm::vec3(0.0, 0.0, _height));

	return SectionRect{ top_left, top_right, bottom_left, bottom_right };
}

glm::vec3 TrackLoader::getPoint(unsigned int i) const {
	return _points[i % _points.size()];
}
