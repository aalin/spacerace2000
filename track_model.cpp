#include "track_model.hpp"
#include "splines.hpp"

const float WIDTH = 10.0f;
const float HEIGHT = 5.0f;

TrackModel::TrackModel(std::vector<glm::vec3> key_points) {
	_points = Splines(key_points).generate(15);
}

std::vector<glm::vec3> TrackModel::generateVertices() const {
	std::vector<glm::vec3> vertices;

	for(unsigned int i = 0; i < _points.size(); i++) {
		LeftRight lr0 = pointVertices(i);
		LeftRight lr1 = pointVertices(i + 1);

		Triangle top0 = { lr0.right, lr1.right, lr0.left };
		Triangle top1 = { lr0.left, lr1.right, lr1.left };

		pushTriangle(vertices, top0);
		pushTriangle(vertices, top1);
	}

	return vertices;
}

void TrackModel::pushTriangle(std::vector<glm::vec3>& vertices, const Triangle& t) const {
	vertices.push_back(t.a);
	vertices.push_back(t.b);
	vertices.push_back(t.c);
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
