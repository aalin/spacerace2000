#ifndef TRACK_HPP
#define TRACK_HPP

#include "opengl.hpp"
#include <glm/glm.hpp>
#include <vector>

class Track {
	public:
		Track(std::vector<glm::vec3> points);

		void draw() const;

	private:
		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;

		unsigned int _size;
};

#endif
