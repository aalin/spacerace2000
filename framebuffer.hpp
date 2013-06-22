#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

class Framebuffer {
	public:
		Framebuffer(unsigned int width, unsigned int height);

	private:
		unsigned int _texture_id;
		unsigned int _renderbuffer_id;
		unsigned int _framebuffer_id;
};

#endif
