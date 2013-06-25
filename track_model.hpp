#ifndef TRACK_MODEL
#define TRACK_MODEL

#include <vector>
#include "vertex_array.hpp"
#include "triangle.hpp"
#include "track_loader.hpp"

class TrackModel {
	public:
		struct LeftRight {
			glm::vec3 left;
			glm::vec3 right;
		};

		TrackModel(std::vector<glm::vec3> key_points, float width, float height);
		~TrackModel();

		void draw() const {
			_vertex_array->draw();
		}

	private:
		VertexArray* _vertex_array;

		std::vector<Vertex> generateVertices(const TrackLoader&) const;

		std::vector<glm::vec3> _points;

		glm::vec3 getPoint(unsigned int i) const {
			return _points[i % _points.size()];
		}

		LeftRight pointVertices(unsigned int i) const;

		void pushTriangle(std::vector<Vertex>& vertices, const Triangle& t) const;

		glm::vec4 colorAt(float index) const;
		glm::vec3 surfaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c) const;
		glm::vec3 vertexNormal(const std::vector<glm::vec3>& surface_normals, unsigned int index) const;
};

#endif
