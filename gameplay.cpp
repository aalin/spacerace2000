#include "gameplay.hpp"
#include "framebuffer.hpp"

#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Gameplay::Gameplay() {
}

Gameplay::~Gameplay() {
}

void Gameplay::setup() {
}

void Gameplay::pause() {
}

void Gameplay::update(double s) {
}

void Gameplay::draw() {
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 1)
	);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();
}
