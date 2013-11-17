#include <iostream>
#include <chrono>
#include <thread>
#include "game.hpp"
#include "gameplay.hpp"
#include "menu.hpp"
#include "screen_renderer.hpp"

Game* Game::INSTANCE = 0;

void Game::glfwErrorCallback(int error, const char* description) {
	std::cerr << "\e[33mGLFW: " << error << ": " << description << "\e[0m" << std::endl;
}

Game::Game(int width, int height, Game::WindowMode mode) {
	Game::INSTANCE = this;
	glfwSetErrorCallback(&Game::glfwErrorCallback);

	if(!glfwInit())
		throw "GLFW could not be initialized.";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	_window = glfwCreateWindow(width, height, "Hello World", 0, 0);

	if(!_window)
		throw "GLFW window could not be opened.";

	glfwMakeContextCurrent(_window);

	glfwSetKeyCallback(_window, &Game::glfwKeyCallback);

	glewExperimental = GL_TRUE;
	int glew_status = glewInit();
	glPrintErrors();

	if(glew_status != GLEW_OK) {
		std::cerr << "GLEW error: " << glewGetErrorString(glew_status) << std::endl;
		throw("GLEW could not be initialized.");
	}

	_screen_renderer = new ScreenRenderer();
}

Game::~Game() {
	while(!_states.empty())
		popState();

	delete _screen_renderer;

	std::cout << "Game::~Game();" << std::endl;
	glfwTerminate();
}

void Game::run() {
	_running = true;

	double last_time = glfwGetTime();

	pushState(new Gameplay(*this));

	while(_running) {
		double current_time = glfwGetTime();

		if(glfwGetKey(_window, GLFW_KEY_SPACE))
			update(0.0);
		else
			update(current_time - last_time);
		draw();

		last_time = current_time;

		//std::chrono::milliseconds duration(10);
		//std::this_thread::sleep_for(duration);
	}
}

void Game::quit() {
	_running = false;
}

void Game::update(double s) {
	if(!_states.empty())
		_states.top()->update(s);
}

void Game::draw() {
	if(!_states.empty()) {
		_states.top()->draw();
		_screen_renderer->draw();
	}

	std::cout << "drawing" << std::endl;
	glfwSwapBuffers(_window);
}

void Game::pushState(GameState* state) {
	if(!_states.empty())
		_states.top()->pause();
	_states.push(state);
	state->setup();
}

void Game::popState() {
	_states.pop();

	if(_states.empty())
		quit();
}

void Game::keyboard(int key, int action) {
	if(_states.empty())
		return;

	if(action == GLFW_PRESS)
		_states.top()->keyPress(key);
	else if(action == GLFW_RELEASE)
		_states.top()->keyRelease(key);
}
