#include "framebuffer.hpp"
#include "opengl.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) {
	// Setup texture
	glGenTextures(1, &_texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Setup renderbuffer
	glGenRenderbuffers(1, &_renderbuffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer_id);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);

	// Setup framebuffer
	glGenFramebuffers(1, &_framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);

	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _texture_id, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _renderbuffer_id);

	// Unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &_framebuffer_id);
	glDeleteTextures(1, &_texture_id);
	glDeleteRenderbuffers(1, &_renderbuffer_id);
}
