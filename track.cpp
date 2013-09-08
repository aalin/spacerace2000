#include "track.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

const float WIDTH = 10.0f;
const float HEIGHT = 4.0f;

std::vector<glm::vec3> loadPointsFromFile(std::string filename) {
	std::vector<glm::vec3> points;

	std::ifstream file(filename.c_str());
	std::string line;

	while(std::getline(file, line))
	{
		std::istringstream iss(line);

		glm::vec3 point;
		iss >> point.x >> point.y >> point.z;
		points.push_back(point);
	}

	return points;
}

Track::Track(std::string filename) : Track(loadPointsFromFile(filename))
{ }

Track::Track(std::vector<glm::vec3> key_points)
	:
	_track_model(TrackModel(key_points, WIDTH, HEIGHT)),
	_track_info(key_points, WIDTH)
{ }

void Track::draw() const {
	_track_model.draw();
}
