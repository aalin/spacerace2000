#include "racer_model.hpp"
#include "triangle.hpp"

RacerModel::RacerModel() {
	_vertex_array = new VertexArray(generateVertices());
}

RacerModel::~RacerModel() {
	delete _vertex_array;
}

void RacerModel::draw() const {
	_vertex_array->draw();
}

void addSimpleTriangle(std::vector<Triangle> &triangles, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	triangles.push_back(Triangle{
		Vertex{a, glm::vec3(), glm::vec4()},
		Vertex{b, glm::vec3(), glm::vec4()},
		Vertex{c, glm::vec3(), glm::vec4()},
	});
}

void assignSurfaceNormal(Triangle &triangle, glm::vec3 normal) {
	triangle.a.normal = normal;
	triangle.b.normal = normal;
	triangle.c.normal = normal;
}

void addTriangleVertices(std::vector<Vertex>& vertices, const Triangle& triangle) {
	vertices.push_back(triangle.a);
	vertices.push_back(triangle.b);
	vertices.push_back(triangle.c);
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
		assignSurfaceNormal(*it, surface_normal);

		addTriangleVertices(vertices, *it);
	}


	// Left side

	const glm::vec3 reverse_x(-1.0, 1.0, 1.0);

	for(auto it = triangles.begin(); it != triangles.end(); it++) {
		// Reverse the positions
		glm::vec3 p0 = it->a.position * reverse_x;
		glm::vec3 p1 = it->b.position * reverse_x;
		glm::vec3 p2 = it->c.position * reverse_x;

		glm::vec3 surface_normal = glm::normalize(glm::cross(p2 - p0, p1 - p0));
		assignSurfaceNormal(*it, surface_normal);

		// Reorder the positions so the triangles are drawn in the right order
		it->a.position = p1;
		it->b.position = p0;
		it->c.position = p2;

		addTriangleVertices(vertices, *it);
	}

	return vertices;
}
