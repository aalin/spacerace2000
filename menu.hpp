#ifndef MENU_HPP
#define MENU_HPP

#include "game_state.hpp"

#include <string>
#include <vector>

class Menu : public GameState {
	public:
		struct MenuItem {
			virtual std::string name() const = 0;
			virtual void call(Game& game) const = 0;
		};

		Menu(Game& game);
		~Menu();

		void setup();
		void pause();
		void update(double s);
		void draw();

		void keyPress(int key);
		void keyRelease(int key);

	private:
		int _current_menu_item;

		std::vector<MenuItem*> _menu_items;

		void printToTerminal();
		void makeChoice();
};

#endif
