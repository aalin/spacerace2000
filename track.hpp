#ifndef TRACK_HPP
#define TRACK_HPP

#include "opengl.hpp"
#include "track_info.hpp"
#include <glm/glm.hpp>
#include <vector>

class Track {
	public:
		Track(std::vector<glm::vec3> points);
		~Track();

		void draw() const;

		glm::vec3 positionAt(float distance) const { return _track_info.positionAt(distance); }
		float distanceNear(float distance, glm::vec3 position) const { return _track_info.distanceNear(distance, position); }

	private:
		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;

		TrackInfo _track_info;

		unsigned int _size;
};

#endif
