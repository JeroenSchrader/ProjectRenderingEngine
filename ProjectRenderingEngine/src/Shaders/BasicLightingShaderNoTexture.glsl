#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

out vec3 fragmentColor;
out vec3 fragmentPosition;
out vec3 normal;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main() {
	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(aPosition, 1.0);
	fragmentColor = vec3(1.0, 1.0, 1.0);
	fragmentPosition = vec3(u_transformationMatrix * vec4(aPosition, 1.0));
	normal = aNormal;
}

#shader fragment
#version 330 core

in vec3 fragmentColor;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 color;

uniform vec3 u_ambientLightColor;
uniform float u_ambientLightStrength;
uniform vec3 u_diffuseLightColor;
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_specularLightColor;
uniform float u_specularLightStrength;

void main() {
	//Ambient
	vec3 ambient = u_ambientLightStrength * u_ambientLightColor;

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(u_lightPosition - fragmentPosition);
	float lightToFragAngle = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = lightToFragAngle * u_diffuseLightColor;

	//Specular
	vec3 viewDirection = normalize(u_cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 128); //the higher the last value, the more reflective the surface.
	vec3 specular = u_specularLightStrength * spec * u_specularLightColor;

	vec3 finalColor = (ambient + diffuse + specular) * fragmentColor;

	color = vec4(finalColor, 1.0);
}