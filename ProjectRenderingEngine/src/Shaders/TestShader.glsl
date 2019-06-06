#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out VS_OUT {
	vec3 fragmentPosition;
	vec2 textureCoordinate;
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
} vs_out;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

void main() {
	vs_out.fragmentPosition = vec3(u_transformationMatrix * vec4(aPosition, 1.0));
	vs_out.textureCoordinate = aTextureCoords;

	//Calculate TBN matrix (Tangent, Bitangent, Normal) using the Gram-Schmidt process
    mat3 normalMatrix = transpose(inverse(mat3(u_transformationMatrix)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));
	vs_out.tangentLightPos = TBN * u_lightPosition;
	vs_out.tangentViewPos = TBN * u_cameraPosition;
	vs_out.tangentFragPos = TBN * vs_out.fragmentPosition;

	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragColor;

in VS_OUT {
	vec3 fragmentPosition; //Unused at the moment
	vec2 textureCoordinate;
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
} fs_in;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform sampler2D u_TextureMap;
uniform sampler2D u_NormalMap;

uniform vec3 u_ambientLightColor;
uniform float u_ambientLightStrength;
uniform vec3 u_diffuseLightColor;
uniform float u_diffuseLightStrength;
uniform vec3 u_specularLightColor;
uniform float u_specularLightStrength;
uniform Material u_Material;

void main() {
	//Calculate normals of normal map
	vec3 norm = texture(u_NormalMap, fs_in.textureCoordinate).rgb;
	norm = normalize(norm * 2.0 - 1.0);

	//Get diffuse color
	vec3 color = texture(u_TextureMap, fs_in.textureCoordinate).rgb;

	//Ambient
	vec3 ambient = u_ambientLightStrength * (u_ambientLightColor * u_Material.ambient * color);

	//Diffuse
	vec3 lightDirection = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
	float lightToFragAngle = max(dot(lightDirection, norm), 0.0);
	//vec3 diffuse = u_diffuseLightStrength * u_diffuseLightColor * (lightToFragAngle * u_Material.diffuse * color);
	vec3 diffuse = lightToFragAngle * color;

	//Specular
	vec3 viewDirection = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	vec3 halfwayDir = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Material.shininess); //the higher the last value, the more reflective the surface.
	//vec3 specular = u_specularLightStrength * u_specularLightColor * (spec * u_Material.specular);
	vec3 specular = vec3(0.2) * spec;

	vec4 finalColor = vec4(ambient + diffuse + specular, 1.0);

	fragColor = finalColor;
}