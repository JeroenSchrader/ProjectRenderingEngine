#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main() {
	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(position, 1.0);
}

#shader fragment
#version 330 core

out vec4 color;

void main() {
	color = vec4(1.0);
}