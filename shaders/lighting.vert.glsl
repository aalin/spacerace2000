#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_color;

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;

out vec3 N;
out vec3 v;
out vec3 Color;

void main() {
  N = normalize(NormalMatrix * vertex_normal);
	v = vec3(ModelViewMatrix * vec4(vertex_normal, 1.0));

	gl_Position = ModelViewProjectionMatrix * vec4(vertex_position, 1.0);
	Color = vertex_color;
}
