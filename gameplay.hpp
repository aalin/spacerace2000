#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "game_state.hpp"
#include <glm/glm.hpp>
#include <functional>
#include <algorithm>

#include "change_model_matrix.hpp"
class Shader;
class Track;
class Racer;
class Framebuffer;

class Gameplay : public GameState {
	public:
		Gameplay(Game& game);
		~Gameplay();

		void setup();
		void pause();
		void update(double s);
		void draw();

		void keyPress(int key) {
			if(key == GLFW_KEY_ESC)
				getGame().popState();
		}

		void keyRelease(int key) {
		}

	private:
		Framebuffer* _framebuffer;
		Shader* _shader;
		Track* _track;
		Racer* _racer;

		GLuint _model_view_projection_matrix_location;
		GLuint _model_view_matrix_location;
		GLuint _normal_matrix_location;

		glm::mat4 setupCamera() const;
		void setupMatrices();
		void uploadMvpMatrix();

		void changeModelMatrix(std::function<void(ChangeModelMatrix&)>);

		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 model_matrix;
};

#endif
