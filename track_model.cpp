#include "track_model.hpp"
#include "splines.hpp"
#include "vertex.hpp"

#include <glm/gtc/constants.hpp>

TrackModel::TrackModel(std::vector<glm::vec3> key_points, float width, float height)
	: _width(width), _height(height) {
	_points = Splines(key_points).generate(30);
	_vertex_array = new VertexArray(generateVertices(), VertexArray::PrimitiveType::TRIANGLES);
}

TrackModel::~TrackModel() {
	delete _vertex_array;
}

std::vector<Vertex> TrackModel::generateVertices() const {
	std::vector<Vertex> vertices;

	std::vector<glm::vec3> top_surface_normals;
	std::vector<glm::vec3> right_surface_normals;

	for(unsigned int i = 0; i < _points.size(); i++) {
		LeftRight lr0 = pointVertices(i);
		LeftRight lr1 = pointVertices(i + 1);

		top_surface_normals.push_back(glm::normalize(
			surfaceNormal(lr0.right, lr1.right, lr0.left) +
			surfaceNormal(lr0.left, lr1.right, lr1.left)
		));

		right_surface_normals.push_back(glm::normalize(
			surfaceNormal(lr1.right, lr0.right, bottomOf(lr0.right)) +
			surfaceNormal(lr1.right, bottomOf(lr0.right), bottomOf(lr1.right))
		));
	}

	for(unsigned int i = 0; i < _points.size(); i++) {
		LeftRight lr0 = pointVertices(i);
		LeftRight lr1 = pointVertices(i + 1);

		glm::vec4 color0 = colorAt(i / static_cast<float>(_points.size()));
		glm::vec4 color1 = colorAt((i + 1) / static_cast<float>(_points.size()));

		// Top
		glm::vec3 top_normal0 = vertexNormal(top_surface_normals, i);
		glm::vec3 top_normal1 = vertexNormal(top_surface_normals, i + 1);

		pushTriangle(vertices, {
			Vertex{ lr1.right, top_normal1, color1 },
			Vertex{ lr0.right, top_normal0, color0 },
			Vertex{ lr0.left, top_normal0, color1 },
		});

		pushTriangle(vertices, {
			Vertex{ lr1.right, top_normal1, color1 },
			Vertex{ lr0.left, top_normal0, color0 },
			Vertex{ lr1.left, top_normal1, color1 }
		});

		// Bottom

		glm::vec3 bottom_normal0 = glm::vec3(0.0) - top_normal0;
		glm::vec3 bottom_normal1 = glm::vec3(0.0) - top_normal1;

		pushTriangle(vertices, {
			Vertex { bottomOf(lr0.right), bottom_normal0, color0 },
			Vertex { bottomOf(lr1.right), bottom_normal1, color1 },
			Vertex { bottomOf(lr0.left), bottom_normal0, color0 },
		});

		pushTriangle(vertices, {
			Vertex { bottomOf(lr0.left), bottom_normal0, color0 },
			Vertex { bottomOf(lr1.right), bottom_normal1, color1 },
			Vertex { bottomOf(lr1.left), bottom_normal1, color1 },
		});


		// Right
		glm::vec3 right_normal0 = vertexNormal(right_surface_normals, i);
		glm::vec3 right_normal1 = vertexNormal(right_surface_normals, i + 1);

		pushTriangle(vertices, {
			Vertex { lr1.right, right_normal1, color1 },
			Vertex { bottomOf(lr0.right), right_normal0, color0 },
			Vertex { lr0.right, right_normal0, color0 },
		});

		pushTriangle(vertices, {
			Vertex { bottomOf(lr0.right), right_normal0, color0 },
			Vertex { lr1.right, right_normal1, color1 },
			Vertex { bottomOf(lr1.right), right_normal1, color1 },
		});

		// Left
		glm::vec3 left_normal0 = glm::vec3(0.0) - right_normal0;
		glm::vec3 left_normal1 = glm::vec3(0.0) - right_normal1;

		pushTriangle(vertices, {
			Vertex { lr1.left, left_normal1, color1 },
			Vertex { lr0.left, left_normal0, color0 },
			Vertex { bottomOf(lr1.left), left_normal1, color1 },
		});

		pushTriangle(vertices, {
			Vertex { bottomOf(lr1.left), left_normal1, color1 },
			Vertex { lr0.left, left_normal0, color0 },
			Vertex { bottomOf(lr0.left), left_normal0, color0 },
		});
	}

	return vertices;
}

void TrackModel::pushTriangle(std::vector<Vertex>& vertices, const Triangle& t) const {
	vertices.push_back(t.a);
	vertices.push_back(t.b);
	vertices.push_back(t.c);
}

TrackModel::LeftRight TrackModel::pointVertices(unsigned int i) const {
	glm::vec3 p0(getPoint(i));;
	glm::vec3 p1(getPoint(i + 1));

	glm::vec3 delta(p0 - p1);

	glm::vec3 outwards(glm::normalize(glm::vec3(delta.y, -delta.x, 0)));

	glm::vec3 left(p0 + outwards * -_width);
	glm::vec3 right(p0 + outwards * _width);

	return { left, right };
}

glm::vec3 TrackModel::bottomOf(glm::vec3 v) const {
	return v - glm::vec3(0.0f, 0.0f, _height);
}

glm::vec3 TrackModel::surfaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c) const {
	return glm::normalize(glm::cross(c - a, b - a));
}

glm::vec3 TrackModel::vertexNormal(const std::vector<glm::vec3>& surface_normals, unsigned int index) const {
	float radius = 10;
	glm::vec3 normal(0.0);

	for(int x = -radius; x < radius; x++) {
		float value = std::cos(std::fabs(x) / radius * glm::half_pi<float>());
		normal += surface_normals[(surface_normals.size() + index - x) % surface_normals.size()] * value;
	}

	return glm::normalize(normal);
}

glm::vec4 TrackModel::colorAt(float x) const {
	return glm::vec4(
		std::pow(std::sin((x + 0) * glm::pi<float>() + 0 / 3.0 * glm::pi<float>()), 2),
		std::pow(std::sin((x + 1) * glm::pi<float>() + 1 / 3.0 * glm::pi<float>()), 2),
		std::pow(std::sin((x + 2) * glm::pi<float>() + 2 / 3.0 * glm::pi<float>()), 2),
		1.0
	);
}
