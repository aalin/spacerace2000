#include "menu.hpp"

#include "gameplay.hpp"

struct StartGameMenuItem : public Menu::MenuItem {
	std::string name() const { return "Start game"; }
	void call(Game& game) const { game.pushState(new Gameplay(game)); }
};

struct HelpMenuItem : public Menu::MenuItem {
	std::string name() const { return "Help"; }
	void call(Game& game) const { };
};

struct ExitGameMenuItem : public Menu::MenuItem {
	std::string name() const { return "Exit game"; }
	void call(Game& game) const { game.quit(); }
};

Menu::Menu(Game& game) : GameState(game) {
	_current_menu_item = 0;

	_menu_items.push_back(new StartGameMenuItem);
	_menu_items.push_back(new HelpMenuItem);
	_menu_items.push_back(new ExitGameMenuItem);
}

Menu::~Menu() {
	// TODO: Delete everything in _menu_items...
}

void Menu::setup() {
	printToTerminal();
}

void Menu::pause() {
}

void Menu::update(double s) {
}

void Menu::draw() {
}

#include <iostream>

void Menu::printToTerminal() {
	std::cout << "\e[2J\e[H";

	// Print empty lines some times because of the horrible OS X menu
	for(int i = 0; i < 5; i++)
		std::cout << std::endl;

	std::cout << "== GAME MENU ==" << std::endl;

	for(unsigned int i = 0; i < _menu_items.size(); i++) {
		if(static_cast<int>(i) == _current_menu_item)
			std::cout << "\e[" << 32 << "m"; // Green
		else
			std::cout << "\e[" << 33 << "m"; // Yellow

		std::cout << _menu_items[i]->name();
		std::cout << "\e[0m" << std::endl;
	}
}

void Menu::keyPress(int key) {
	if(key == GLFW_KEY_UP)
		_current_menu_item--;
	else if(key == GLFW_KEY_DOWN)
		_current_menu_item++;
	else if(key == GLFW_KEY_ENTER) {
		makeChoice();
		return;
	}

	if(_current_menu_item < 0)
		_current_menu_item = _menu_items.size() - 1;
	if(_current_menu_item >= _menu_items.size())
		_current_menu_item = 0;

	printToTerminal();
}

void Menu::keyRelease(int key) {
}

void Menu::makeChoice() {
	_menu_items[_current_menu_item]->call(getGame());
}
