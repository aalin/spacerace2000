#include "track_loader.hpp"
#include "splines.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

TrackLoader::TrackLoader(std::vector<glm::vec3> key_points, unsigned int detail, float width, float height)
	: _width(width), _height(height) {
	_points = Splines(key_points).generate(detail);

	std::cout << "Number of points: " << _points.size() << std::endl;
	for(unsigned int i = 0; i < _points.size(); i++)
		_section_rects.push_back(generateSectionRect(i));
}

float magnitude(const glm::vec2 v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float calculateDegrees(const glm::vec3 prev, const glm::vec3 curr, const glm::vec3 next) {
	const glm::vec3 f_1 = glm::normalize(next - curr);
	const glm::vec3 f_2 = glm::normalize(curr - prev);

	return glm::angle(f_1, f_2);
}

TrackLoader::SectionRect TrackLoader::generateSectionRect(unsigned int i) const {
	const glm::vec3 current(getPoint(i));;
	const glm::vec3 next(getPoint(i + 1));
	const glm::vec3 prev(getPoint(i - 1));

	const glm::vec3 delta(current - next);
	const glm::vec3 forward(glm::normalize(delta));

	const glm::vec3 outwards(glm::normalize(glm::vec3(delta.y, -delta.x, 0)));
	const glm::vec4 height(0.0, 0.0, _height, 0.0);

	glm::vec4 top_left(outwards * -_width, 1.0);
	glm::vec4 top_right(outwards * _width, 1.0);
	glm::vec4 bottom_left(top_left - height);
	glm::vec4 bottom_right(top_right - height);

	float degrees = calculateDegrees(prev, current, next);

	glm::mat4 translation = glm::translate(glm::mat4(1.0), current);
	float scale_factor = -12.0;
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0), degrees * scale_factor, forward);

	glm::mat4 final = translation * rotation;

	return SectionRect{
		glm::vec3(final * top_left),
		glm::vec3(final * top_right),
		glm::vec3(final * bottom_left),
		glm::vec3(final * bottom_right)
	};
}
