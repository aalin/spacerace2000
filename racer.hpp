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
		float getDirection() const { return _direction; }
		float getTurnRatio() const { return _turning / TURN_LIMIT; }

	private:
		RacerModel _model;

		glm::vec3 _position;
		float _direction;
		float _speed;
		float _turning;

		static const float TURN_SPEED;
		static const float TURN_LIMIT;
};

#endif
