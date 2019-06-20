#include "PostProcessing.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "OpenGLMesh.h"

PostProcessing::PostProcessing(FrameBuffer* fbo, Shader* shader, OpenGLMesh* quad)
	: m_FBO(fbo), m_ScreenShader(shader), m_ScreenQuad(quad)
{
}

void PostProcessing::InitializeFirstPass()
{
	m_FBO->Bind();
}

void PostProcessing::InitializeSecondPass(Effects* effects)
{
	m_FBO->Unbind();
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ScreenShader->Bind();
	m_ScreenShader->SetUniform1i("u_GreyScale", (int)*effects->GreyScale);
	m_ScreenShader->SetUniform1i("u_InverseColor", (int)*effects->InverseColor);
	m_ScreenQuad->GetVao()->Bind();
	glBindTexture(GL_TEXTURE_2D, m_FBO->GetColorBufferID());
}

