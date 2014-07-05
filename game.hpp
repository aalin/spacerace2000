#ifndef GAME_HPP
#define GAME_HPP

#include "opengl.hpp"
#include "key_state.hpp"
#include <stack>

class GameState;
class ScreenRenderer;

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
		void popState();

		static void glfwKeyCallback(int key, int action) {
			getInstance().keyboard(key, action);
		}

		void keyboard(int key, int action);

	private:
		bool _running;
		bool _paused;
		float _game_speed;

		KeyState _space_key_state;
		KeyState _z_key_state, _x_key_state;
		std::stack<GameState*> _states;

		void update(double s);
		void draw();

		static Game* INSTANCE;

		static Game& getInstance() {
			return *INSTANCE;
		}

		ScreenRenderer* _screen_renderer;
};

#endif
