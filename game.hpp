#ifndef GAME_HPP
#define GAME_HPP

#include "opengl.hpp"
#include <stack>

class GameState;

class Game {
	public:
		enum struct WindowMode {
			WINDOW = GLFW_WINDOW,
			FULLSCREEN = GLFW_FULLSCREEN
		};

		Game(int width, int height, WindowMode);
		~Game();

		void run();
		void quit();

		void pushState(GameState* state);

		static void glfwKeyCallback(int key, int action) {
			getInstance().keyboard(key, action);
		}

		void keyboard(int key, int action);

	private:
		bool _running;
		std::stack<GameState*> _states;

		void update(double s);
		void draw();

		static Game* INSTANCE;

		static Game& getInstance() {
			return *INSTANCE;
		}
};

#endif
