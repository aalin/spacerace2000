#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "game_state.hpp"

class Shader;
class Track;
class Racer;

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
		Racer* _racer;

		GLuint _model_view_projection_matrix_location;
		GLuint _model_view_matrix_location;
		GLuint _normal_matrix_location;
};

#endif
