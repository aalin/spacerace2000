#ifndef TRACK_MODEL
#define TRACK_MODEL

#include "triangle.hpp"
#include <vector>

class TrackModel {
	public:
		struct LeftRight {
			glm::vec3 left;
			glm::vec3 right;
		};

		TrackModel(std::vector<glm::vec3> key_points);
		std::vector<glm::vec3> generateVertices() const;

	private:
		std::vector<glm::vec3> _points;

		glm::vec3 getPoint(unsigned int i) const {
			return _points[i % _points.size()];
		}

		LeftRight pointVertices(unsigned int i) const;
		glm::vec3 bottomOf(glm::vec3) const;

		void pushTriangle(std::vector<glm::vec3>& vertices, const Triangle& t, const Triangle& n) const;

		glm::vec3 vertexNormal(const std::vector<glm::vec3>& surface_normals, unsigned int index) const;
};

#endif
