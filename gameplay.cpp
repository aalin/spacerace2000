#include "opengl.hpp"
#include "gameplay.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

Gameplay::Gameplay() : _lighting_shader(0) {
}

Gameplay::~Gameplay() {
	delete _lighting_shader;
}

void Gameplay::setup() {
	_lighting_shader = new Shader("shaders/lighting");
	_mpv_location = _lighting_shader->uniformLocation("MPV");

	glGenBuffers(1, &_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Gameplay::pause() {
}

void Gameplay::update(double s) {
}

void Gameplay::draw() {
	glm::mat4 projection_matrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 view_matrix = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 1)
	);

	glm::mat4 model_matrix(1.0f); // Identity
	glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

	_lighting_shader->use();
	glUniformMatrix4fv(_mpv_location, 1, GL_FALSE, &mvp[0][0]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glVertexAttribPointer(
		0,         // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,         // size
		GL_FLOAT,  // type
		GL_FALSE,  // normalized?
		0,         // stride
		0          // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
