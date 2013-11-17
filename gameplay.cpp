#include "opengl.hpp"
#include "gameplay.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"
#include "track.hpp"
#include "racer.hpp"
#include "change_model_matrix.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>
#include <vector>

Gameplay::Gameplay(Game& game) : GameState(game), _shader(0) {
}

Gameplay::~Gameplay() {
	delete _shader;
	delete _track;
}

void Gameplay::setup() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	_framebuffer = new Framebuffer(1024, 768);

	_shader = new Shader("shaders/lighting");
	_shader->use();
	_model_view_projection_matrix_location = _shader->uniformLocation("ModelViewProjectionMatrix");
	_model_view_matrix_location = _shader->uniformLocation("ModelViewMatrix");
	_normal_matrix_location = _shader->uniformLocation("NormalMatrix");

	glUniform4f(_shader->uniformLocation("ambientMat"), 0.2, 0.2, 0.2, 1.0);
	glUniform4f(_shader->uniformLocation("diffuseMat"), 0.8, 0.8, 0.8, 1.0);
	glUniform4f(_shader->uniformLocation("specMat"), 0.8, 0.8, 0.8, 1.0);
	glUniform1f(_shader->uniformLocation("specPow"), 80.0);
	glUniform3f(_shader->uniformLocation("lightPosition"), 0.0, 0.0, 100.0);


	_track = new Track("tracks/track01");
	_racer = new Racer(_track->positionAt(0.0));
}

void Gameplay::pause() {
}

void Gameplay::update(double s) {
	_racer->update(s, *_track, getGame());
}

glm::mat4 Gameplay::setupCamera() const {
	const float dir = _racer->getDirection();
	const float camera_distance = 50.0f;

	const glm::vec3 camera_position(
		_racer->getPosition() +
		glm::rotateZ(glm::vec3(1.0, 1.0, 0.0), dir - 45.0f) * camera_distance +
		glm::vec3(0.0, 0.0, 3.0)
	);

	return glm::lookAt(
		camera_position,
		_racer->getPosition(),
		glm::vec3(0.0, 0.0, 1.0)
	);
}

void Gameplay::setupMatrices() {
	projection_matrix = glm::perspective(30.0f, 4.0f / 3.0f, 0.1f, 2000.0f);
	view_matrix = setupCamera();
	model_matrix = glm::mat4(1.0);

	glm::mat4 model_view_matrix = view_matrix * model_matrix;
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model_view_matrix)));

	glUniformMatrix4fv(_model_view_matrix_location, 1, GL_FALSE, glm::value_ptr(model_view_matrix));
	glUniformMatrix3fv(_normal_matrix_location, 1, GL_FALSE, glm::value_ptr(normal_matrix));

	uploadMvpMatrix();
}

template<typename F>
void Gameplay::changeModelMatrix(F &lambda) {
	ChangeModelMatrix change_matrix(projection_matrix, view_matrix, model_matrix, _model_view_projection_matrix_location);
	lambda(change_matrix);
}

void Gameplay::uploadMvpMatrix() {
	glm::mat4 model_view_projection_matrix = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(_model_view_projection_matrix_location, 1, GL_FALSE, glm::value_ptr(model_view_projection_matrix));
}

void Gameplay::draw() {
	_framebuffer->bindFramebuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->use();

	setupMatrices();

	_track->draw();

	{
		ChangeModelMatrix matrix(projection_matrix, view_matrix, model_matrix, _model_view_projection_matrix_location);
		matrix.translate(_racer->getPosition());
		matrix.rotate(_racer->getDirection() + 90.0f, glm::vec3(0.0, 0.0, 1.0));
		matrix.rotate(_racer->getTurnRatio() * 25.0f, glm::vec3(0.0, 1.0, 0.0));
	}

	_racer->draw();

	_framebuffer->unbindFramebuffer();
	_framebuffer->bindTexture();
}
