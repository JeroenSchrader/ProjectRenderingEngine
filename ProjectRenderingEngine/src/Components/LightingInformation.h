#pragma once

#include "GLM/vec3.hpp"

struct LightingInformation {
	glm::vec3 Position;
	//Ambient
	glm::vec3 AmbientColor;
	float AmbientStrength;
	//Diffuse
	glm::vec3 DiffuseColor;
	float DiffuseStrength;
	//Specular
	glm::vec3 SpecularColor;
	float SpecularStrength;
	glm::vec3 CameraPosition;
};