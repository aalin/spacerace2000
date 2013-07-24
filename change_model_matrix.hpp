#ifndef CHANGE_MODEL_MATRIX_HPP
#define CHANGE_MODEL_MATRIX_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ChangeModelMatrix {
	public:
		ChangeModelMatrix(const glm::mat4 &projection_matrix, const glm::mat4 &view_matrix, const glm::mat4 &model_matrix, unsigned int mvp_location) :
			_projection_matrix(projection_matrix),
			_view_matrix(view_matrix),
			_model_matrix(model_matrix),
			_mvp_location(mvp_location)
		{}

		~ChangeModelMatrix() {
			glm::mat4 mvp_matrix = _projection_matrix * _view_matrix * _model_matrix;
			glUniformMatrix4fv(_mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
		}

		void translate(const glm::vec3 &v) {
			_model_matrix = glm::translate(_model_matrix, v);
		}

		void rotate(float angle, const glm::vec3 &v) {
			_model_matrix = glm::rotate(_model_matrix, angle, v);
		}

	private:
		glm::mat4 _projection_matrix;
		glm::mat4 _view_matrix;
		glm::mat4 _model_matrix;
		unsigned int _mvp_location;
};

#endif
