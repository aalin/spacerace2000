#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "opengl.hpp"
#include "vertex.hpp"
#include <vector>

class VertexArray {
	public:
		enum struct PrimitiveType {
			POINTS = GL_POINTS,
			LINE_STRIP = GL_LINES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			TRIANGLES = GL_TRIANGLES
		};

		VertexArray(const std::vector<Vertex>& vertices, PrimitiveType primitive_type);
		~VertexArray();

		void draw();

	private:
		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;
		GLenum _mode;
		unsigned int _size;
};

#endif
