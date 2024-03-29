#ifndef GLERROR_H
#define GLERROR_H

#include <GL/glew.h>
#include <GL/glfw.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

void _glPrintErrors(const char *file, int line);
#define glPrintErrors() _glPrintErrors(__FILE__, __LINE__)
#endif
