#include <iostream>
#include "game.hpp"
#include "gameplay.hpp"

Game::Game(int width, int height, Game::WindowMode::Mode window_mode) {
	if(!glfwInit())
		throw "GLFW could not be initialized.";

	if(!glfwOpenWindow(width, height, 0, 0, 0, 0, 16, 0, window_mode))
		throw "GLFW window could not be opened.";
}

Game::~Game() {
	std::cout << "Game::~Game();" << std::endl;
	glfwTerminate();
}

int Game::run() {
	_running = true;

	double last_time = glfwGetTime();

	pushState(new Gameplay);

	while(_running) {
		double current_time = glfwGetTime();

		update(current_time - last_time);
		draw();

		last_time = current_time;

		glfwSleep(100);
	}
}

void Game::update(double s) {
	if(!_states.empty())
		_states.top()->update(s);
}

void Game::draw() {
	if(!_states.empty())
		_states.top()->draw();
}

void Game::pushState(GameState* state) {
	if(!_states.empty())
		_states.top()->pause();
	_states.push(state);
	state->setup();
}
