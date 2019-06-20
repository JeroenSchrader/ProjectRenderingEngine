#pragma once

class FrameBuffer;
class Shader;
class OpenGLMesh;

#include <vector>

struct Effects {
	Effects(bool* greyscale, bool* inverseColor) {
		GreyScale = greyscale;
		InverseColor = inverseColor;
	}

	bool* GreyScale;
	bool* InverseColor;
};

class PostProcessing {
public:
	PostProcessing(FrameBuffer* fbo, Shader* shader, OpenGLMesh* quad);
	~PostProcessing() = default;

	void InitializeFirstPass();
	void InitializeSecondPass(Effects* effects);

private:
	FrameBuffer* m_FBO;
	Shader* m_ScreenShader;
	OpenGLMesh* m_ScreenQuad;
};

static std::vector<float> quadVertices = {
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,	//0
	-1.0f, -1.0f,  0.0f, 0.0f,	//1
	 1.0f, -1.0f,  1.0f, 0.0f,	//2
	 1.0f,  1.0f,  1.0f, 1.0f	//3
};

static std::vector<unsigned int> quadIndices = {
	0, 1, 2,
	0, 2, 3
};