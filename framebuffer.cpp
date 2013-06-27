#include "framebuffer.hpp"
#include "opengl.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) {
	// Setup texture
	glGenTextures(1, &_texture_id);
	glPrintErrors();
	bindTexture();

	glPrintErrors();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	glPrintErrors();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPrintErrors();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPrintErrors();

	// Setup renderbuffer
	glGenRenderbuffers(1, &_renderbuffer_id);
	glPrintErrors();
	glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer_id);
	glPrintErrors();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glPrintErrors();

	// Setup framebuffer
	glGenFramebuffers(1, &_framebuffer_id);
	glPrintErrors();
	bindFramebuffer();

	glPrintErrors();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture_id, 0);
	glPrintErrors();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer_id);

	glPrintErrors();

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw "NOT COMPLETE";

	glPrintErrors();

	// Unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glPrintErrors();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glPrintErrors();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glPrintErrors();
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &_framebuffer_id);
	glDeleteTextures(1, &_texture_id);
	glDeleteRenderbuffers(1, &_renderbuffer_id);
}

void Framebuffer::bindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);
}

void Framebuffer::unbindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindTexture() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_id);
}
