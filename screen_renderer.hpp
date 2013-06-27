#ifndef SCREEN_RENDERER_HPP
#define SCREEN_RENDERER_HPP

#include "opengl.hpp"

class Shader;

class ScreenRenderer {
	public:
		ScreenRenderer();
		~ScreenRenderer();

		void draw() const;

	private:
		Shader* _shader;
		GLuint _vertex_buffer_id;
		GLuint _vertex_array_id;
};

#endif
