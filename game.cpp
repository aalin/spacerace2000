#include <iostream>
#include "game.hpp"
#include "gameplay.hpp"

Game::Game(int width, int height, Game::WindowMode::Mode window_mode) {

	if(!glfwInit())
		throw "GLFW could not be initialized.";

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	if(!glfwOpenWindow(width, height, 0, 0, 0, 0, 16, 0, window_mode))
		throw "GLFW window could not be opened.";

	glPrintErrors();
	glewExperimental = GL_TRUE;
	int glew_status = glewInit();
	glPrintErrors();
	if(glew_status != GLEW_OK) {
		std::cerr << "GLEW error: " << glewGetErrorString(glew_status) << std::endl;
		throw("GLEW could not be initialized.");
	}
}

Game::~Game() {
	std::cout << "Game::~Game();" << std::endl;
	glfwTerminate();
}

void Game::run() {
	_running = true;

	double last_time = glfwGetTime();

	pushState(new Gameplay);

	while(_running) {
		double current_time = glfwGetTime();

		if(glfwGetKey(GLFW_KEY_SPACE))
			update(0.0);
		else
			update(current_time - last_time);
		draw();

		last_time = current_time;

		glfwSleep(0.001);
	}
}

void Game::update(double s) {
	if(!_states.empty())
		_states.top()->update(s);
}

void Game::draw() {
	if(!_states.empty())
		_states.top()->draw();
	glfwSwapBuffers();
}

void Game::pushState(GameState* state) {
	if(!_states.empty())
		_states.top()->pause();
	_states.push(state);
	state->setup();
}
