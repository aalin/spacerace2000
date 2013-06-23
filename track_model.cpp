#include "track_model.hpp"
#include "splines.hpp"

#include <glm/gtx/random.hpp>

const float WIDTH = 10.0f;
const float HEIGHT = 5.0f;

TrackModel::TrackModel(std::vector<glm::vec3> key_points) {
	_points = Splines(key_points).generate(15);
}

std::vector<glm::vec3> TrackModel::generateVertices() const {
	std::vector<glm::vec3> vertices;

	std::vector<glm::vec3> top_surface_normals;
	std::vector<glm::vec3> right_surface_normals;

	for(unsigned int i = 0; i < _points.size(); i++) {
		LeftRight lr0 = pointVertices(i);
		LeftRight lr1 = pointVertices(i + 1);

		top_surface_normals.push_back(glm::normalize(
			Triangle{ lr0.right, lr1.right, lr0.left }.surfaceNormal() +
			Triangle{ lr0.left, lr1.right, lr1.left }.surfaceNormal()
		));

		right_surface_normals.push_back(glm::normalize(
			Triangle{ lr1.right, lr0.right, bottomOf(lr0.left) }.surfaceNormal() +
			Triangle{ lr1.right, bottomOf(lr0.right), bottomOf(lr1.right) }.surfaceNormal()
		));
	}

	for(unsigned int i = 0; i < _points.size(); i++) {
		LeftRight lr0 = pointVertices(i);
		LeftRight lr1 = pointVertices(i + 1);

		// Top
		glm::vec3 top_normal0 = vertexNormal(top_surface_normals, i);
		glm::vec3 top_normal1 = vertexNormal(top_surface_normals, i + 1);

		pushTriangle(vertices, { lr0.right, lr1.right, lr0.left }, { top_normal0, top_normal1, top_normal0 });
		pushTriangle(vertices, { lr0.left, lr1.right, lr1.left }, { top_normal0, top_normal1, top_normal1 });

		// Left
		//pushTriangle(vertices, { lr0.right, lr1.right, lr0.left });
		//pushTriangle(vertices, { lr0.left, lr1.right, lr1.left });
	}

	return vertices;
}

void TrackModel::pushTriangle(std::vector<glm::vec3>& vertices, const Triangle& t, const Triangle& n) const {
	glm::vec3 color(1.0, 0.0, 0.0);

	vertices.push_back(t.a);
	vertices.push_back(n.a);
	vertices.push_back(color);
	vertices.push_back(t.b);
	vertices.push_back(n.b);
	vertices.push_back(color);
	vertices.push_back(t.c);
	vertices.push_back(n.c);
	vertices.push_back(color);
}

TrackModel::LeftRight TrackModel::pointVertices(unsigned int i) const {
	glm::vec3 p0(getPoint(i));
	glm::vec3 p1(getPoint(i + 1));

	glm::vec3 delta(p0 - p1);

	glm::vec3 outwards(glm::normalize(glm::vec3(delta.y, -delta.x, 0)));

	glm::vec3 left(p0 + outwards * -WIDTH);
	glm::vec3 right(p0 + outwards * WIDTH);

	return { left, right };
}

glm::vec3 TrackModel::bottomOf(glm::vec3 v) const {
	return v - glm::vec3(0.0f, 0.0f, HEIGHT);
}

glm::vec3 TrackModel::vertexNormal(const std::vector<glm::vec3>& surface_normals, unsigned int index) const {
	float radius = 10;
	glm::vec3 normal(0.0);

	for(int x = -radius; x < radius; x++) {
		float value = std::cos(std::fabs(x) / 2.0 / radius * 3.14159);
		normal += surface_normals[(index - x) % surface_normals.size()] * value;
	}

	return glm::normalize(normal);
}
