#include "racer.hpp"
#include "racer_model.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

const float Racer::TURN_SPEED = 250.0;
const float Racer::TURN_LIMIT = 250.0;

Racer::Racer(glm::vec3 position) {
	_direction = 120.0;
	_speed = 1.0;
	_turning = 0.0;
	_distance = 0.0;
	_position = position;
}

Racer::~Racer() {
}

void Racer::update(double s, const Track& track) {
	int turn = 0;
	if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
		turn -= 1;
	if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
		turn += 1;

	if(turn == 0) {
		_turning -= _turning * s * 5.0;
	} else {
		_turning += turn * s * TURN_SPEED * _speed;
		if(_turning < -TURN_LIMIT) _turning = -TURN_LIMIT;
		if(_turning > TURN_LIMIT) _turning = TURN_LIMIT;
	}

	_direction -= _turning * s;

	_distance = track.distanceNear(_distance, _position);
	glm::vec3 track_position = track.positionAt(_distance);

	_position += glm::rotateZ(glm::vec3(1.0, 1.0, 0.0), _direction + 90.0f + 45.0f) * _speed;
	_position.z = track_position.z + 2.0;
}

void Racer::draw() const {
	_model.draw();
}
