#ifndef RACER_MODEL_HPP
#define RACER_MODEL_HPP

#include "opengl.hpp"
#include "vertex.hpp"
#include <vector>

class RacerModel {
	public:
		struct Triangle {
			Vertex a;
			Vertex b;
			Vertex c;
		};

		RacerModel();
		~RacerModel();

		void draw() const;

	private:
		std::vector<Vertex> generateVertices() const;

		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;

		unsigned int _size;
};

#endif
