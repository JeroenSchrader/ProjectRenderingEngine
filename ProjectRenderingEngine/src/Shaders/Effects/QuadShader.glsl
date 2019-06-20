#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
}  

#shader fragment
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D u_ScreenTexture;
uniform bool u_GreyScale;
uniform bool u_InverseColor;

void main()
{ 
    vec4 textureImage = texture(u_ScreenTexture, TexCoords);

	FragColor = textureImage;

	if(u_GreyScale){
		//Greyscale
		float average = 0.2126 * textureImage.r + 0.7152 * textureImage.g + 0.0722 * textureImage.b;
		FragColor = vec4(average, average, average, 1.0);
	}
	if(u_InverseColor){
		//Inverse color
		FragColor = vec4(vec3(1.0 - FragColor), 1.0);
	}
}