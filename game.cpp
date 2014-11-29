#include <iostream>
#include "game.hpp"
#include "gameplay.hpp"
#include "menu.hpp"
#include "screen_renderer.hpp"

Game* Game::INSTANCE = 0;

Game::Game(int width, int height, Game::WindowMode window_mode) {
	Game::INSTANCE = this;

	if(!glfwInit())
		throw "GLFW could not be initialized.";

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	if(!glfwOpenWindow(width, height, 0, 0, 0, 0, 16, 0, static_cast<int>(window_mode)))
		throw "GLFW window could not be opened.";

	glfwSetKeyCallback(&Game::glfwKeyCallback);

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
	_paused = false;
	_game_speed = 1.0;

	double last_time = glfwGetTime();

	pushState(new Gameplay(*this));

	while(_running) {
		double current_time = glfwGetTime();

		double s = current_time - last_time * _game_speed;

		if(_paused)
			s = 0.0;

		update(s);

		draw();

		last_time = current_time;

		glfwSleep(0.001);
	}
}

void Game::quit() {
	_running = false;
}

void Game::update(double s) {
	_space_key_state.update(glfwGetKey(GLFW_KEY_SPACE));
	_z_key_state.update(glfwGetKey('Z'));
	_x_key_state.update(glfwGetKey('X'));

	// Toggle pause when space is pressed.
	if(_space_key_state.getState() == KeyState::State::PRESSED)
		_paused = !_paused;

	if(_z_key_state.getState() == KeyState::State::PRESSED)
		_game_speed /= 2.0;
	if(_x_key_state.getState() == KeyState::State::PRESSED)
		_game_speed *= 2.0;

	if(!_states.empty())
		_states.top()->update(s);
}

void Game::draw() {
	if(!_states.empty()) {
		_states.top()->draw();
		_screen_renderer->draw();
	}

	glfwSwapBuffers();
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
