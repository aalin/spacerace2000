#ifndef RACER_HPP
#define RACER_HPP

#include "racer_model.hpp"

class Racer {
	public:
		Racer();
		~Racer();

		void update(double s);
		void draw() const;

		void setPosition(glm::vec3 position) { _position = position; }
		const glm::vec3 getPosition() const { return _position; }

		void setDirection(float direction) { _direction = direction; }
		const float getDirection() const { return _direction; }

	private:
		RacerModel _model;

		glm::vec3 _position;
		float _direction;
};

#endif
