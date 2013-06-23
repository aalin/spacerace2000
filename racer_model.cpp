#include "racer_model.hpp"

RacerModel::RacerModel() {
	std::vector<Vertex> vertices = generateVertices();

	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);
	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	_size = vertices.size() * sizeof(glm::vec3);
}

RacerModel::~RacerModel() {
	glDeleteBuffers(1, &_vertex_buffer_id);
	glDeleteVertexArrays(1, &_vertex_array_id);
}

void RacerModel::draw() const {
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

void addSimpleTriangle(std::vector<RacerModel::Triangle> &triangles, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	triangles.push_back(RacerModel::Triangle{
		Vertex{a, glm::vec3(), glm::vec4()},
		Vertex{b, glm::vec3(), glm::vec4()},
		Vertex{c, glm::vec3(), glm::vec4()},
	});
}

std::vector<Vertex> RacerModel::generateVertices() const {
	std::vector<Vertex> vertices;

	std::vector<Triangle> triangles;

	float h = 4.0;

	addSimpleTriangle(triangles, glm::vec3(0, 28, 0), glm::vec3(0, 11, h), glm::vec3(4, 15, 0));
	addSimpleTriangle(triangles, glm::vec3(4, 15, 0), glm::vec3(0, 11, h), glm::vec3(8, 10, 0));
	addSimpleTriangle(triangles, glm::vec3(4, 0, 0), glm::vec3(8, 10, 0), glm::vec3(0, 11, h));
	addSimpleTriangle(triangles, glm::vec3(4, 0, 0), glm::vec3(0, 11, h), glm::vec3(2, 0, h / 2));
	addSimpleTriangle(triangles, glm::vec3(0, 11, h), glm::vec3(0, 0, 0), glm::vec3(2, 0, h / 2));
	addSimpleTriangle(triangles, glm::vec3(0, 11, 0), glm::vec3(2, 0, -h / 2), glm::vec3(0, 0, 0));

	// Backside
	addSimpleTriangle(triangles, glm::vec3(2, 0, h / 2), glm::vec3(0, 0, 0), glm::vec3(4, 0, 0));
	addSimpleTriangle(triangles, glm::vec3(0, 0, 0), glm::vec3(2, 0, -h / 2), glm::vec3(4, 0, 0));

	// Wings
	addSimpleTriangle(triangles, glm::vec3(8, 20, 0), glm::vec3(6, 0, 0), glm::vec3(7, 0, 0.5));
	addSimpleTriangle(triangles, glm::vec3(8, 20, 0), glm::vec3(7, 0, 0.5), glm::vec3(10, 0, 0));
	addSimpleTriangle(triangles, glm::vec3(10, 0, 0), glm::vec3(7, 0, 0.5), glm::vec3(6, 0, 0));
	addSimpleTriangle(triangles, glm::vec3(6, 0, 0), glm::vec3(8, 20, 0), glm::vec3(7, 0, -0.5));
	addSimpleTriangle(triangles, glm::vec3(7, 0, -0.5), glm::vec3(8, 20, 0), glm::vec3(10, 0, 0));
	addSimpleTriangle(triangles, glm::vec3(6, 0, 0), glm::vec3(7, 0, -0.5), glm::vec3(10, 0, 0));

	// Scale everything...
	for(auto it = triangles.begin(); it != triangles.end(); it++) {
		it->a.position = it->a.position / 4.0f;
		it->b.position = it->b.position / 4.0f;
		it->c.position = it->c.position / 4.0f;
	}

	// Set colors
	for(auto it = triangles.begin(); it != triangles.end(); it++) {
		it->a.color = glm::vec4(0.0, 0.0, 1.0, 1.0);
		it->b.color = glm::vec4(0.0, 0.0, 1.0, 1.0);
		it->c.color = glm::vec4(0.0, 0.0, 1.0, 1.0);
	}

	// Right side
	for(auto it = triangles.begin(); it != triangles.end(); it++) {
		glm::vec3 a = it->a.position;
		glm::vec3 b = it->c.position;
		glm::vec3 c = it->b.position;
		glm::vec3 surface_normal = glm::normalize(glm::cross(c - a, b - a));

		it->a.normal = surface_normal;
		it->b.normal = surface_normal;
		it->c.normal = surface_normal;

		vertices.push_back(it->a);
		vertices.push_back(it->b);
		vertices.push_back(it->c);
	}

	// Left side

	glm::vec3 reverse_x(-1.0, 1.0, 1.0);

	for(auto it = triangles.begin(); it != triangles.end(); it++) {
		glm::vec3 p0 = it->a.position * reverse_x;
		glm::vec3 p1 = it->b.position * reverse_x;
		glm::vec3 p2 = it->c.position * reverse_x;

		glm::vec3 surface_normal = glm::normalize(glm::cross(p2 - p0, p1 - p0));

		it->a.position = p0;
		it->b.position = p1;
		it->c.position = p2;

		it->a.normal = surface_normal;
		it->b.normal = surface_normal;
		it->c.normal = surface_normal;

		vertices.push_back(it->a);
		vertices.push_back(it->b);
		vertices.push_back(it->c);
	}

	return vertices;
}
