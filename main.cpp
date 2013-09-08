#include <iostream>
#include "game.hpp"

int main() {

	try {
		Game game(1024, 768, Game::WindowMode::WINDOW);
		game.run();
	} catch(const char* msg) {
		std::cerr << "Exception: " << msg << std::endl;
		return 1;
	}
}
