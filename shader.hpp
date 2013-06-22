#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"
#include <string>

class Shader {
	public:
		Shader(std::string basename);

		void use() { glUseProgram(_program); }

		GLint numUniforms() const {
			GLint num_uniforms;
			glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &num_uniforms);
			return num_uniforms;
		}

		GLint uniformLocation(std::string name)
		{
			return glGetUniformLocation(_program, name.c_str());
		}

	private:
		GLuint _vertex_shader;
		GLuint _fragment_shader;
		GLuint _program;
};

#endif
