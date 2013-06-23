#version 330 core

uniform vec4 ambientMat;
uniform vec4 diffuseMat;
uniform vec4 specMat;
uniform float specPow;
uniform vec3 lightPosition;

in vec3 N;
in vec3 v;
in vec3 Color;

out vec4 FragColor;

void main() {
	vec3 L = normalize(lightPosition.xyz - v);
	vec3 E = normalize(-v);
	vec3 R = normalize(reflect(-L, N));

	vec4 ambient = ambientMat;
	vec4 diffuse = clamp(diffuseMat * max(dot(N, L), 0.0), 0.0, 1.0);
	vec4 spec = clamp (specMat * pow(max(dot(R, E),0.0), 0.3 * specPow), 0.0, 1.0);

	FragColor = vec4(Color, 1.0) * (ambient + diffuse + spec);
}
