#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in vec3 aNormal;

out vec3 fragmentColor;
out vec3 fragmentPosition;
out vec2 textureCoordinate;
out vec3 normal;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main() {
	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(aPosition, 1.0);
	textureCoordinate = aTextureCoords;
	fragmentColor = vec3(1.0, 1.0, 1.0);
	fragmentPosition = vec3(u_transformationMatrix * vec4(aPosition, 1.0));
	normal = aNormal;
}

#shader fragment
#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 fragmentColor;
in vec3 fragmentPosition;
in vec2 textureCoordinate;
in vec3 normal;

out vec4 color;

uniform vec3 u_ambientLightColor;
uniform float u_ambientLightStrength;
uniform vec3 u_diffuseLightColor;
uniform float u_diffuseLightStrength;
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_specularLightColor;
uniform float u_specularLightStrength;
uniform Material u_Material;

uniform sampler2D u_TextureMap;

void main() {
	vec4 texSample = texture(u_TextureMap, textureCoordinate);

	//Ambient
	vec3 ambient = u_ambientLightStrength * (u_ambientLightColor * u_Material.ambient);

	//Calculate normals of normal map
	vec3 norm = normalize(normal);

	//Diffuse
	vec3 lightDirection = normalize(u_lightPosition - fragmentPosition);
	float lightToFragAngle = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = u_diffuseLightStrength * u_diffuseLightColor * (lightToFragAngle * u_Material.diffuse);

	//Specular
	vec3 viewDirection = normalize(u_cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess); //the higher the last value, the more reflective the surface.
	vec3 specular = u_specularLightColor * u_specularLightStrength * (spec * u_Material.specular);

	vec4 finalColor = (vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * texSample;

	color = finalColor;
}