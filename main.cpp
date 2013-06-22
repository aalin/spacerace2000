#include <iostream>
#include "game.hpp"

int main() {

	try {
		Game game(800, 600, Game::WindowMode::Window);
		game.run();
	} catch(const char* msg) {
		return 1;
	}
}
