#ifndef GAME_HPP
#define GAME_HPP

#include "opengl.hpp"
#include <stack>
#include <iostream>

class GameState;
class ScreenRenderer;

class Game {
	public:
		enum struct WindowMode {
			WINDOW,
			FULLSCREEN
		};

		Game(int width, int height, WindowMode mode);
		~Game();

		void run();
		void quit();

		void pushState(GameState* state);
		void popState();

		static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			getInstance().keyboard(key, action);
		}

		static void glfwErrorCallback(int error, const char* description);

		void keyboard(int key, int action);

		bool isKeyPressed(int key) const { bool asd = glfwGetKey(_window, key) == GLFW_PRESS;std::cout << asd<<std::endl; return asd; }

	private:
		bool _running;
		std::stack<GameState*> _states;

		void update(double s);
		void draw();

		static Game* INSTANCE;

		static Game& getInstance() {
			return *INSTANCE;
		}

		ScreenRenderer* _screen_renderer;
		GLFWwindow* _window;
};

#endif
