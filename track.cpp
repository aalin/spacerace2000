#include "track.hpp"
#include "splines.hpp"
#include <iostream>

Track::Track(std::vector<glm::vec3> key_points) {
	std::vector<glm::vec3> points = Splines(key_points).generate(10);

	std::cout << key_points.size() << std::endl;
	std::cout << points.size() << std::endl;

	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);
	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);

	_size = points.size() * sizeof(glm::vec3);
}

void Track::draw() const {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, _size);
	glDisableVertexAttribArray(0);
}
