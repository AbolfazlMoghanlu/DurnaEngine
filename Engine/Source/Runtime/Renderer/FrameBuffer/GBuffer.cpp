#include "DurnaPCH.h"
#include "GBuffer.h"
#include "Runtime/Renderer/Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Durna
{
	GBuffer::GBuffer() : FrameBuffer()
	{
		glGenTextures(1, &DepthStencilTextureID);
		glGenTextures(1, &DepthTextureID);
		glGenTextures(1, &StencilTextureID);

		AddAttachment("Buffer_Position", FrameBufferAttachmentType::Color_0,
			FrameBufferAttachmentFormat::RGB, FrameBufferAttachmentFormat::RGB32f,
			FrameBufferAttachmentDataType::Float);

 		AddAttachment("Buffer_Color", FrameBufferAttachmentType::Color_1,
 			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA,
 			FrameBufferAttachmentDataType::uByte);

		AddAttachment("Buffer_Normal", FrameBufferAttachmentType::Color_2,
			FrameBufferAttachmentFormat::RGB, FrameBufferAttachmentFormat::RGB32f,
			FrameBufferAttachmentDataType::Float);

		AddAttachment("Buffer_Specular_Roughness_Metalic_AO", FrameBufferAttachmentType::Color_3,
			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA32f,
			FrameBufferAttachmentDataType::Float);

		AddAttachment("Buffer_ShadingModel", FrameBufferAttachmentType::Color_4,
			FrameBufferAttachmentFormat::Red_Int, FrameBufferAttachmentFormat::R8UI,
			FrameBufferAttachmentDataType::uByte);
		
		AddAttachment("Buffer_FinalColor", FrameBufferAttachmentType::Color_5,
			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA,
			FrameBufferAttachmentDataType::uByte);

		AddAttachment("Buffer_Postproccess", FrameBufferAttachmentType::Color_6,
			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA,
			FrameBufferAttachmentDataType::uByte);

		RebuildBuffer();
	}

	GBuffer::~GBuffer()
	{
		
		glDeleteTextures(1, &DepthStencilTextureID);
		glDeleteTextures(1, &DepthTextureID);
		glDeleteTextures(1, &StencilTextureID);
		
	}

	std::shared_ptr<GBuffer> GBuffer::Create()
	{
		return std::make_shared<GBuffer>();
	}

	void GBuffer::BindTextures(uint32 ShaderID)
	{
		FrameBuffer::BindTextures(ShaderID);
		
		uint32 i = (uint32)Attachments.size();
		uint32 UniformLocation = 0;

		Texture::ActivateTexture(i);
		glBindTexture(GL_TEXTURE_2D, DepthTextureID);
		UniformLocation = glGetUniformLocation(ShaderID, "Buffer_Depth");
		glUniform1i(UniformLocation, i);
		
		i++;

		Texture::ActivateTexture(i);
		glBindTexture(GL_TEXTURE_2D, StencilTextureID);
		UniformLocation = glGetUniformLocation(ShaderID, "Buffer_Stencil");
		glUniform1i(UniformLocation, i);
	}

	void GBuffer::RebuildBuffer()
	{
		FrameBuffer::RebuildBuffer();
		
		glBindFramebuffer(GL_FRAMEBUFFER, ID);

		glGenTextures(1, &DepthStencilTextureID);
		glBindTexture(GL_TEXTURE_2D, DepthStencilTextureID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, SizeX, SizeY);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthStencilTextureID, 0);

		
		glGenTextures(1, &DepthTextureID);
		glTextureView(DepthTextureID, GL_TEXTURE_2D, DepthStencilTextureID,
			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, DepthTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);

		glGenTextures(1, &StencilTextureID);
		glTextureView(StencilTextureID, GL_TEXTURE_2D, DepthStencilTextureID,
			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, StencilTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		CheckForComplationError();
	}
}