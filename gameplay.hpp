#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "game_state.hpp"

class Gameplay : public GameState {
	public:
		Gameplay();
		~Gameplay();

		void setup();
		void pause();
		void update(double s);
		void draw();
};

#endif
