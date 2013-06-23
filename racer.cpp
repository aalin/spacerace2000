#include "racer.hpp"
#include "racer_model.hpp"

Racer::Racer() {
	_direction = 0.0;
}

Racer::~Racer() {
}

void Racer::update(double s) {
}

void Racer::draw() const {
	_model.draw();
}
