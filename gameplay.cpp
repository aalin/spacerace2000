#include "opengl.hpp"
#include "gameplay.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

static const GLfloat vertices[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

Gameplay::Gameplay() : _shader(0) {
}

Gameplay::~Gameplay() {
	delete _shader;
}

void Gameplay::setup() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	_shader = new Shader("shaders/lighting");

	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);

	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Gameplay::pause() {
}

void Gameplay::update(double s) {
}

#include <iostream>

void Gameplay::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->use();

	glm::mat4 projection_matrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 view_matrix = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)
	);

	glm::mat4 model_matrix(1.0);

	glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

	_mpv_location = _shader->uniformLocation("MVP");
	glUniformMatrix4fv(_mpv_location, 1, GL_FALSE, glm::value_ptr(mvp));

	int pos_attrib = _shader->attribLocation("vertex_position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
