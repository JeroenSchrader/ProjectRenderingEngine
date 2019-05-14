#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexColor;
layout(location = 2) in vec3 normals;

out vec4 fragmentColor;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main() {
	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(position, 1.0);
	fragmentColor = vec4(vertexColor.x, vertexColor.y, 0.5, 1.0);
}

#shader fragment
#version 330 core

in vec4 fragmentColor;

out vec4 color;

uniform vec4 u_Color;

void main() {
	color = fragmentColor;
}