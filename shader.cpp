#include "shader.hpp"

#include <iostream>
#include <fstream>

struct SourceResult {
	bool success;
	std::string source;
};

SourceResult readSource(std::string filename) {
	std::ifstream is(filename.c_str());

	if(is.fail()) {
		std::cout << "\e[31m" << "Could not load shader file: " << filename << "\e[0m" << std::endl;
		return { false, "" };
	}

	is.seekg (0, std::ios::end);
	unsigned int length = is.tellg();
	is.seekg (0, std::ios::beg);

	std::string source(length, '\0');
	is.read(&source[0], length);
	is.close();

	return { true, source };
}

struct CompilationResult {
	bool success;
	GLuint shader;
};


CompilationResult createShader(GLenum shader_type, std::string filename) {
	GLuint shader = glCreateShader(shader_type);
	std::cout << "\e[33mCompiling shader: " << filename << "\e[0m" << std::endl;

	SourceResult source_result(readSource(filename));

	if(!source_result.success)
		return { false, 0 };

	const char* data = source_result.source.c_str();
	glShaderSource(shader, 1, &data, 0);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status == GL_FALSE) {
		GLint log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *info = new GLchar[log_length + 1];
		glGetShaderInfoLog(shader, log_length, NULL, info);

		std::cerr << "\e[31mErrors compiling " << filename << "\e[0m" << std::endl;
		std::cerr << info << std::endl;

		delete[] info;

		throw;
	}

	std::cout << "\e[32m" << "Success!" << "\e[0m" << std::endl;

	return { true, shader };
}

Shader::Shader(std::string basename) {
	CompilationResult geometry_shader = createShader(GL_GEOMETRY_SHADER, basename + ".geom.glsl");
	CompilationResult vertex_shader = createShader(GL_VERTEX_SHADER, basename + ".vert.glsl");
	CompilationResult fragment_shader = createShader(GL_FRAGMENT_SHADER, basename + ".frag.glsl");

	_program = glCreateProgram();

	if(geometry_shader.success)
		glAttachShader(_program, geometry_shader.shader);
	if(vertex_shader.success)
		glAttachShader(_program, vertex_shader.shader);
	if(fragment_shader.success)
		glAttachShader(_program, fragment_shader.shader);

	glLinkProgram(_program);

	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint log_length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *info_log = new GLchar[log_length + 1];
		glGetProgramInfoLog(_program, log_length, NULL, info_log);
		std::cerr << "Linker failure: " << info_log << std::endl;
		delete[] info_log;
	}
}
