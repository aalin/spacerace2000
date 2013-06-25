#ifndef GAME_HPP
#define GAME_HPP

#include "opengl.hpp"
#include <stack>
#include "game_state.hpp"

class Game {
	public:
		enum struct WindowMode {
			WINDOW = GLFW_WINDOW,
			FULLSCREEN = GLFW_FULLSCREEN
		};

		Game(int width, int height, WindowMode);
		~Game();

		void run();

		void pushState(GameState* state);

	private:
		bool _running;
		std::stack<GameState*> _states;

		void update(double s);
		void draw();
};

#endif
