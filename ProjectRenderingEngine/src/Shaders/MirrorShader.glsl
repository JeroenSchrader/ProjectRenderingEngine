#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out VS_OUT {
	vec3 fragmentPosition;
	vec3 fragmentColor;
	vec2 uv;
	vec3 normal;
} vs_out;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main() {
	vs_out.fragmentPosition = vec3(u_transformationMatrix * vec4(aPosition, 1.0));
	vs_out.fragmentColor = vec3(1.0);
	vs_out.uv = aUV;

    mat3 normalMatrix = transpose(inverse(mat3(u_transformationMatrix)));
	vs_out.normal = normalMatrix * aNormal;

	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in VS_OUT {
	vec3 fragmentPosition;
	vec3 fragmentColor;
	vec2 uv;
	vec3 normal;
} fs_in;

out vec4 color;

uniform vec3 u_ambientLightColor;
uniform float u_ambientLightStrength;
uniform vec3 u_diffuseLightColor;
uniform float u_diffuseLightStrength;
uniform vec3 u_specularLightColor;
uniform float u_specularLightStrength;
uniform Material u_Material;

uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

uniform samplerCube u_Skybox;

void main() {

	vec3 I = normalize(fs_in.fragmentPosition - u_cameraPosition);
	vec3 R = reflect(I, normalize(fs_in.normal));
	//Get texture from Skybox cubemap
	vec4 texColor = vec4(texture(u_Skybox, -R).rgb, 1.0);

	vec3 norm = normalize(fs_in.normal);
	
	//Ambient
	vec3 ambient = u_ambientLightStrength * (vec3(texColor) * u_ambientLightColor * u_Material.ambient);

	//Diffuse
	vec3 lightDirection = normalize(u_lightPosition - fs_in.fragmentPosition);
	float lightToFragAngle = max(dot(lightDirection, norm), 0.0);
	vec3 diffuse = u_diffuseLightStrength * u_diffuseLightColor * (vec3(texColor) * lightToFragAngle * u_Material.diffuse);

	//Specular
	vec3 viewDirection = normalize(u_cameraPosition - fs_in.fragmentPosition); 
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess); //the higher the last value, the more reflective the surface.
	vec3 specular = u_specularLightColor * u_specularLightStrength * (spec * u_Material.specular);

	//Final Pixel Color
	vec3 finalColor = (ambient + diffuse + specular) * fs_in.fragmentColor;
	color = vec4(finalColor, 0.0);
}