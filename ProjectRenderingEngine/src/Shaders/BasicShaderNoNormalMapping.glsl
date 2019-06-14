#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out VS_OUT {
	vec3 fragmentPosition;
	vec3 fragmentColor;
	vec2 uv;
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
	vec3 normal;
	vec3 lightPos;
	vec3 viewPos;
} vs_out;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

void main() {
	gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * vec4(aPosition, 1.0);
	vs_out.fragmentPosition = vec3(u_transformationMatrix * vec4(aPosition, 1.0));
	vs_out.uv = aUV;
	vs_out.fragmentColor = vec3(1.0);

	//Calculate TBN matrix (Tangent, Bitangent, Normal) using the Gram-Schmidt process
    mat3 normalMatrix = transpose(inverse(mat3(u_transformationMatrix)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
	mat3 TBN = transpose(mat3(T, B, N));

	vs_out.lightPos = u_lightPosition;
	vs_out.viewPos = u_cameraPosition;

	vs_out.tangentLightPos = TBN * u_lightPosition;
	vs_out.tangentViewPos = TBN * u_cameraPosition;
	vs_out.tangentFragPos = TBN * vs_out.fragmentPosition;
	vs_out.normal = aNormal;
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
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
	vec3 normal;
	vec3 lightPos;
	vec3 viewPos;
} fs_in;

out vec4 color;

uniform vec3 u_ambientLightColor;
uniform float u_ambientLightStrength;
uniform vec3 u_diffuseLightColor;
uniform float u_diffuseLightStrength;
uniform vec3 u_specularLightColor;
uniform float u_specularLightStrength;
uniform Material u_Material;

uniform sampler2D u_TextureMap;
//uniform sampler2D u_NormalMap;

void main() {
	//Ambient
	vec3 texColor = texture(u_TextureMap, fs_in.uv).rgb;

	vec3 ambient = u_ambientLightStrength * (texColor * u_ambientLightColor * u_Material.ambient);

	//vec3 norm = texture(u_NormalMap, fs_in.uv).rgb;
	//norm = normalize(norm * 2.0 - 1.0);

	vec3 norm = normalize(fs_in.normal);
	//Diffuse
	vec3 lightDirection = normalize(fs_in.lightPos - fs_in.fragmentPosition); //Use fs_in.tangent.. for tangent space normal calculations
	float lightToFragAngle = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = u_diffuseLightStrength * u_diffuseLightColor * (texColor * lightToFragAngle * u_Material.diffuse);

	//Specular
	vec3 viewDirection = normalize(fs_in.viewPos - fs_in.fragmentPosition); //Use fs_in.tangent.. for tangent space normal calculations
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess); //the higher the last value, the more reflective the surface.
	vec3 specular = u_specularLightColor * u_specularLightStrength * (spec * u_Material.specular);

	vec3 finalColor = (ambient + diffuse + specular) * fs_in.fragmentColor;

	color = vec4(finalColor, 0.0);
}