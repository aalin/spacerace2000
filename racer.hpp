#ifndef RACER_HPP
#define RACER_HPP

#include "racer_model.hpp"
#include "track.hpp"

class Racer {
	public:
		Racer(glm::vec3 position);
		~Racer();

		void update(double s, const Track& track);
		void draw() const;

		void setPosition(glm::vec3 position) { _position = position; }
		const glm::vec3 getPosition() const { return _position; }

		void setDirection(float direction) { _direction = direction; }
		float getDirection() const { return _direction; }
		float getTurnRatio() const { return _turning / TURN_LIMIT; }
		float getDistance() const  { return _distance; }

	private:
		RacerModel _model;

		glm::vec3 _position;
		float _direction;
		float _speed;
		float _turning;
		float _distance;

		static const float TURN_SPEED;
		static const float TURN_LIMIT;
};

#endif
