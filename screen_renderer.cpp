#include "screen_renderer.hpp"
#include "shader.hpp"

#include <iostream>

const float vertices[] = {
	 1.0, 1.0, 0.0,		1.0, 1.0,
	-1.0, 1.0, 0.0,		0.0, 1.0,
	 1.0,-1.0, 0.0,		1.0, 0.0,
	-1.0,-1.0, 0.0,		0.0, 0.0,
};

ScreenRenderer::ScreenRenderer() {
	_shader = new Shader("shaders/game");

	glGenVertexArrays(1, &_vertex_array_id);
	glBindVertexArray(_vertex_array_id);
	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

ScreenRenderer::~ScreenRenderer() {
	delete _shader;
	glDeleteBuffers(1, &_vertex_buffer_id);
	glDeleteVertexArrays(1, &_vertex_array_id);
}

void ScreenRenderer::draw() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->use();

	glUniform1i(_shader->uniformLocation("Texture"), 0);

	glBindVertexArray(_vertex_array_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	const float size = sizeof(float) * 5;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, reinterpret_cast<void*>(sizeof(float) * 0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size, reinterpret_cast<void*>(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
