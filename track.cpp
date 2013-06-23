#include "track.hpp"
#include "track_model.hpp"
#include <iostream>

Track::Track(std::vector<glm::vec3> key_points) {
	std::vector<glm::vec3> vertices = TrackModel(key_points).generateVertices();

	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);
	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	_size = vertices.size() * sizeof(glm::vec3);
	std::cout << _size << std::endl;
}

void Track::draw() const {
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, _size);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
