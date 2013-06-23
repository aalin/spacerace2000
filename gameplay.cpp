#include "opengl.hpp"
#include "gameplay.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"
#include "track.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

Gameplay::Gameplay() : _shader(0) {
}

Gameplay::~Gameplay() {
	delete _shader;
	delete _track;
}

void Gameplay::setup() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// glEnable(GL_DEPTH_TEST);

	_shader = new Shader("shaders/lighting");
	_shader->use();
	_mvp_location = _shader->uniformLocation("MVP");

	std::vector<glm::vec3> track_points;
	track_points.push_back(glm::vec3(-783.13, 0.00, 0.00));
	track_points.push_back(glm::vec3(-686.75, 48.19, 0.00));
	track_points.push_back(glm::vec3(-554.22, 72.29, 0.00));
	track_points.push_back(glm::vec3(-397.59, 60.24, 15.00));
	track_points.push_back(glm::vec3(-240.96, 0.00, 30.00));
	track_points.push_back(glm::vec3(-120.48, -108.43, 15.00));
	track_points.push_back(glm::vec3(-48.19, -216.87, 0.00));
	track_points.push_back(glm::vec3(12.05, -313.25, 0.00));
	track_points.push_back(glm::vec3(48.19, -445.78, 0.00));
	track_points.push_back(glm::vec3(108.43, -638.55, 0.00));
	track_points.push_back(glm::vec3(108.43, -710.84, 0.00));
	track_points.push_back(glm::vec3(72.29, -783.13, 0.00));
	track_points.push_back(glm::vec3(0.00, -867.47, 0.00));
	track_points.push_back(glm::vec3(-72.29, -915.66, 0.00));
	track_points.push_back(glm::vec3(-192.77, -927.71, 40.00));
	track_points.push_back(glm::vec3(-277.11, -891.57, 40.00));
	track_points.push_back(glm::vec3(-277.11, -795.18, 80.00));
	track_points.push_back(glm::vec3(-228.92, -734.94, 80.00));
	track_points.push_back(glm::vec3(-144.58, -710.84, 80.00));
	track_points.push_back(glm::vec3(-48.19, -674.70, 80.00));
	track_points.push_back(glm::vec3(24.10, -638.55, 80.00));
	track_points.push_back(glm::vec3(72.29, -566.27, 80.00));
	track_points.push_back(glm::vec3(120.48, -433.73, 80.00));
	track_points.push_back(glm::vec3(132.53, -289.16, 80.00));
	track_points.push_back(glm::vec3(108.43, -144.58, 40.00));
	track_points.push_back(glm::vec3(60.24, -24.10, 0.00));
	track_points.push_back(glm::vec3(-72.29, 12.05, -20.00));
	track_points.push_back(glm::vec3(-192.77, -60.24, -40.00));
	track_points.push_back(glm::vec3(-228.92, -180.72, -20.00));
	track_points.push_back(glm::vec3(-168.67, -301.20, 0.00));
	track_points.push_back(glm::vec3(-156.63, -469.88, 0.00));
	track_points.push_back(glm::vec3(-192.77, -566.27, 0.00));
	track_points.push_back(glm::vec3(-265.06, -650.60, 0.00));
	track_points.push_back(glm::vec3(-385.54, -662.65, 0.00));
	track_points.push_back(glm::vec3(-481.93, -614.46, -40.00));
	track_points.push_back(glm::vec3(-542.17, -493.98, -40.00));
	track_points.push_back(glm::vec3(-481.93, -373.49, -40.00));
	track_points.push_back(glm::vec3(-349.40, -337.35, -40.00));
	track_points.push_back(glm::vec3(-216.87, -373.49, -80.00));
	track_points.push_back(glm::vec3(-132.53, -481.93, -80.00));
	track_points.push_back(glm::vec3(-120.48, -626.51, -40.00));
	track_points.push_back(glm::vec3(-168.67, -771.08, 0.00));
	track_points.push_back(glm::vec3(-253.01, -855.42, 0.00));
	track_points.push_back(glm::vec3(-397.59, -891.57, 0.00));
	track_points.push_back(glm::vec3(-590.36, -855.42, 0.00));
	track_points.push_back(glm::vec3(-734.94, -759.04, 0.00));
	track_points.push_back(glm::vec3(-771.08, -626.51, 0.00));
	track_points.push_back(glm::vec3(-734.94, -469.88, 0.00));
	track_points.push_back(glm::vec3(-855.42, -301.20, 0.00));
	track_points.push_back(glm::vec3(-855.42, -84.34, 0.00));

	_track = new Track(track_points);
}

void Gameplay::pause() {
}

void Gameplay::update(double s) {
}

#include <iostream>

void Gameplay::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->use();

	glm::mat4 projection_matrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 5000.0f);

	glm::mat4 view_matrix = glm::lookAt(
		glm::vec3(400.0, 400.0, 300.0), // Camera position
		glm::vec3(0.0, 0.0, 100.0), // Look at
		glm::vec3(0.0, 0.0, 1.0)
	);

	glm::mat4 model_matrix(1.0);

	glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

	glUniformMatrix4fv(_mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

	_track->draw();
}
