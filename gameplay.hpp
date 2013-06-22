#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "game_state.hpp"

class Shader;

class Gameplay : public GameState {
	public:
		Gameplay();
		~Gameplay();

		void setup();
		void pause();
		void update(double s);
		void draw();

	private:
		Shader* _lighting_shader;
		GLint _mpv_location;
		GLuint _vertex_buffer;
};

#endif
