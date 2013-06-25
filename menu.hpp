#ifndef MENU_HPP
#define MENU_HPP

#include "game_state.hpp"

class Menu : public GameState {
	public:
		Menu();
		~Menu();

		void setup();
		void pause();
		void update(double s);
		void draw();
};

#endif
