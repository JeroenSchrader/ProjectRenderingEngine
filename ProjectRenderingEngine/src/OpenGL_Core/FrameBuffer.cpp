#include "FrameBuffer.h"
#include "Renderer.h"
#include "DisplayManager.h"
#include <iostream>

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	DisplayManager* dpm = DisplayManager::GetInstance();

	// generate texture
	glGenTextures(1, &m_ColorBufferID);
	glBindTexture(GL_TEXTURE_2D, m_ColorBufferID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dpm->GetWindowWidth(), dpm->GetWindowHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferID, 0);

	glGenRenderbuffers(1, &m_RenderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, dpm->GetWindowWidth(), dpm->GetWindowHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// attach renderbuffer to currently bound framebuffer object
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_ID);
}

void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
