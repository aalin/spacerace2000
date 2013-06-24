#ifndef TRACK_MODEL
#define TRACK_MODEL

#include <vector>
#include "vertex.hpp"

class TrackModel {
	public:
		struct Triangle {
			Vertex a;
			Vertex b;
			Vertex c;
		};

		struct LeftRight {
			glm::vec3 left;
			glm::vec3 right;
		};

		TrackModel(std::vector<glm::vec3> key_points, float width, float height);
		std::vector<Vertex> generateVertices() const;

	private:
		const float _width;
		const float _height;

		std::vector<glm::vec3> _points;

		glm::vec3 getPoint(unsigned int i) const {
			return _points[i % _points.size()];
		}

		LeftRight pointVertices(unsigned int i) const;
		glm::vec3 bottomOf(glm::vec3) const;

		void pushTriangle(std::vector<Vertex>& vertices, const Triangle& t) const;

		glm::vec4 colorAt(unsigned int index) const;
		glm::vec3 surfaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c) const;
		glm::vec3 vertexNormal(const std::vector<glm::vec3>& surface_normals, unsigned int index) const;
};

#endif
