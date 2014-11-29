#ifndef TRACK_HPP
#define TRACK_HPP

#include "track_model.hpp"
#include "track_info.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Track {
	public:
		Track(std::string filename);
		Track(std::vector<glm::vec3> points);

		void draw() const;

		glm::vec3 betterPositionAt(float distance, glm::vec3 position) const { return _track_info.betterPositionAt(distance, position); }
		glm::vec3 positionAt(float distance) const { return _track_info.positionAt(distance); }
		float distanceNear(float distance, glm::vec3 position) const { return _track_info.distanceNear(distance, position); }

	private:
		TrackModel _track_model;
		TrackInfo _track_info;
};

#endif
