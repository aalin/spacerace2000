#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "opengl.hpp"
#include "vertex.hpp"
#include <vector>

class VertexArray {
	public:
		VertexArray(const std::vector<Vertex>& vertices);
		~VertexArray();

		void draw();

	private:
		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;
		unsigned int _size;
};

#endif
