#version 330
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_color;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertex_position, 1.0);
}
