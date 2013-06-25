#include "track.hpp"
#include <iostream>

const float WIDTH = 10.0f;
const float HEIGHT = 4.0f;

Track::Track(std::vector<glm::vec3> key_points)
	:
	_track_model(TrackModel(key_points, WIDTH, HEIGHT)),
	_track_info(key_points, WIDTH)
{ }

void Track::draw() const {
	_track_model.draw();
}
