#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "opengl.hpp"

class Framebuffer {
	public:
		Framebuffer(unsigned int width, unsigned int height);
		~Framebuffer();

		void bindFramebuffer() const;
		void unbindFramebuffer() const;
		void bindTexture() const;

	private:
		GLuint _texture_id;
		GLuint _renderbuffer_id;
		GLuint _framebuffer_id;
};

#endif
