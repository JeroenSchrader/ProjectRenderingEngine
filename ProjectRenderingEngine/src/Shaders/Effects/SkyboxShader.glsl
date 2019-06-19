#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main()
{
    TexCoords = aPos;
	vec4 pos = u_projectionMatrix * mat4(mat3(u_viewMatrix)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}