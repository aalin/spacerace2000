#include "vertex.hpp"
#include "vertex_array.hpp"

VertexArray::VertexArray(const std::vector<Vertex>& vertices) {
	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);
	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	_size = vertices.size() * 3; // Triangles. They have tree angles.
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &_vertex_buffer_id);
	glDeleteVertexArrays(1, &_vertex_array_id);
}

void VertexArray::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

	unsigned int offset = 0;

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offset));
	offset += sizeof(glm::vec3);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offset));
	offset += sizeof(glm::vec3);

	// Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offset));
	offset += sizeof(glm::vec4);

	glDrawArrays(GL_TRIANGLES, 0, _size);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
