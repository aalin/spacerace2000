#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glfw.h>
#include <stack>

#include "game_state.hpp"

class Game {
	public:
		struct WindowMode {
			enum Mode {
				Window = GLFW_WINDOW,
				Fullscreen = GLFW_FULLSCREEN
			};
		};

		Game(int width, int height, WindowMode::Mode);
		~Game();

		int run();

		void pushState(GameState* state);

	private:
		bool _running;
		std::stack<GameState*> _states;

		void update(double s);
		void draw();
};

#endif
