#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "game_state.hpp"

class Shader;
class Track;

class Gameplay : public GameState {
	public:
		Gameplay();
		~Gameplay();

		void setup();
		void pause();
		void update(double s);
		void draw();

	private:
		Shader* _shader;
		Track* _track;
		GLuint _mvp_location;
};

#endif
