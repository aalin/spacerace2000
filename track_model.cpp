#include "track_model.hpp"
#include "vertex.hpp"
#include "track_loader.hpp"

#include <glm/gtc/constants.hpp>

TrackModel::TrackModel(std::vector<glm::vec3> key_points, float width, float height) {
	_vertex_array = new VertexArray(
		generateVertices(TrackLoader(key_points, width, height)),
		VertexArray::PrimitiveType::TRIANGLES
	);
}

TrackModel::~TrackModel() {
	delete _vertex_array;
}

std::vector<Vertex> TrackModel::generateVertices(const TrackLoader& track_loader) const {
	std::vector<Vertex> vertices;

	std::vector<glm::vec3> top_surface_normals;
	std::vector<glm::vec3> right_surface_normals;

	for(unsigned int i = 0; i < track_loader.numSectionRects(); i++) {
		TrackLoader::SectionRect current = track_loader.getSectionRect(i);
		TrackLoader::SectionRect next = track_loader.getSectionRect(i + 1);

		top_surface_normals.push_back(glm::normalize(
			surfaceNormal(current.top_right, next.top_right, current.top_left) +
			surfaceNormal(current.top_left, next.top_right, next.top_left)
		));

		right_surface_normals.push_back(glm::normalize(
			surfaceNormal(next.top_right, current.top_right, current.bottom_right) +
			surfaceNormal(next.top_right, current.bottom_right, next.bottom_right)
		));
	}

	for(unsigned int i = 0; i < track_loader.numSectionRects(); i++) {
		TrackLoader::SectionRect current = track_loader.getSectionRect(i);
		TrackLoader::SectionRect next = track_loader.getSectionRect(i + 1);

		glm::vec4 color0 = colorAt(i / static_cast<float>(track_loader.numSectionRects()));
		glm::vec4 color1 = colorAt((i + 1) / static_cast<float>(track_loader.numSectionRects()));

		// Top
		glm::vec3 top_normal0 = vertexNormal(top_surface_normals, i);
		glm::vec3 top_normal1 = vertexNormal(top_surface_normals, i + 1);

		pushTriangle(vertices, {
			Vertex{ next.top_right, top_normal1, color1 },
			Vertex{ current.top_right, top_normal0, color0 },
			Vertex{ current.top_left, top_normal0, color1 },
		});

		pushTriangle(vertices, {
			Vertex{ next.top_right, top_normal1, color1 },
			Vertex{ current.top_left, top_normal0, color0 },
			Vertex{ next.top_left, top_normal1, color1 }
		});

		// Bottom

		glm::vec3 bottom_normal0 = glm::vec3(0.0) - top_normal0;
		glm::vec3 bottom_normal1 = glm::vec3(0.0) - top_normal1;

		pushTriangle(vertices, {
			Vertex { current.bottom_right, bottom_normal0, color0 },
			Vertex { next.bottom_right, bottom_normal1, color1 },
			Vertex { current.bottom_left, bottom_normal0, color0 },
		});

		pushTriangle(vertices, {
			Vertex { current.bottom_left, bottom_normal0, color0 },
			Vertex { next.bottom_right, bottom_normal1, color1 },
			Vertex { next.bottom_left, bottom_normal1, color1 },
		});


		// Right
		glm::vec3 right_normal0 = vertexNormal(right_surface_normals, i);
		glm::vec3 right_normal1 = vertexNormal(right_surface_normals, i + 1);

		pushTriangle(vertices, {
			Vertex { next.top_right, right_normal1, color1 },
			Vertex { current.bottom_right, right_normal0, color0 },
			Vertex { current.top_right, right_normal0, color0 },
		});

		pushTriangle(vertices, {
			Vertex { current.bottom_right, right_normal0, color0 },
			Vertex { next.top_right, right_normal1, color1 },
			Vertex { next.bottom_right, right_normal1, color1 },
		});

		// Left
		glm::vec3 left_normal0 = glm::vec3(0.0) - right_normal0;
		glm::vec3 left_normal1 = glm::vec3(0.0) - right_normal1;

		pushTriangle(vertices, {
			Vertex { next.top_left, left_normal1, color1 },
			Vertex { current.top_left, left_normal0, color0 },
			Vertex { next.bottom_left, left_normal1, color1 },
		});

		pushTriangle(vertices, {
			Vertex { next.bottom_left, left_normal1, color1 },
			Vertex { current.top_left, left_normal0, color0 },
			Vertex { current.bottom_left, left_normal0, color0 },
		});
	}

	return vertices;
}

void TrackModel::pushTriangle(std::vector<Vertex>& vertices, const Triangle& t) const {
	vertices.push_back(t.a);
	vertices.push_back(t.b);
	vertices.push_back(t.c);
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
