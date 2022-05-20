#include "DurnaPCH.h"
#include "FrameBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Renderer/Texture.h"

namespace Durna
{
	FrameBufferAttachment::FrameBufferAttachment()
	{
		glGenTextures(1, &TextureID);
	}

	FrameBufferAttachment::~FrameBufferAttachment()
	{
		glDeleteTextures(1, &TextureID);
	}

	FrameBufferDepthStencilAttachment::FrameBufferDepthStencilAttachment()
	{
		glGenTextures(1, &DepthStencilTextureID);
		glGenTextures(1, &DepthTextureID);
		glGenTextures(1, &StencilTextureID);
	}

	FrameBufferDepthStencilAttachment::~FrameBufferDepthStencilAttachment()
	{
		glDeleteTextures(1, &DepthStencilTextureID);
		glDeleteTextures(1, &DepthTextureID);
		glDeleteTextures(1, &StencilTextureID);
	}

	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &ID);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &ID);
	}

	std::shared_ptr<FrameBuffer> FrameBuffer::Create()
	{
		return std::make_shared<FrameBuffer>();
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ID);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::BindTextures(uint32 ShaderID)
	{
		int32 i = 0;
		//for (int32 i = 0; i < Attachments.size() ; i++)
		for (FrameBufferAttachment* Attachment : Attachments)
		{
			Texture::ActivateTexture(i);
			glBindTexture(GL_TEXTURE_2D, Attachments[i]->TextureID);

			int UniformLocation = glGetUniformLocation(ShaderID, Attachments[i]->TextureUniformName.c_str());
			glUniform1i(UniformLocation, i);

			i++;
		}

		if (DepthStencilAttachment.get())
		{
			Texture::ActivateTexture(i);
			glBindTexture(GL_TEXTURE_2D, DepthStencilAttachment->DepthTextureID);

			int UniformLocation = glGetUniformLocation(ShaderID, DepthStencilAttachment->DepthTextureUniformName.c_str());
			glUniform1i(UniformLocation, i);

			i++;

			Texture::ActivateTexture(i);
			glBindTexture(GL_TEXTURE_2D, DepthStencilAttachment->StencilTextureID);
		
			UniformLocation = glGetUniformLocation(ShaderID, DepthStencilAttachment->StencilTextureUniformName.c_str());
			glUniform1i(UniformLocation, i);
		}
	}

	void FrameBuffer::ClearAttachments()
	{
		for (FrameBufferAttachment* Attachment : Attachments)
		{
			delete Attachment;
		}

		Attachments.clear();
	}

	void FrameBuffer::AddAttachment(const std::string& TextureUniformName, FrameBufferAttachmentType InType,
		FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat, FrameBufferAttachmentDataType InDataType)
	{
		FrameBufferAttachment* Attachment = new FrameBufferAttachment();
		Attachment->TextureUniformName = TextureUniformName;
		Attachment->Type = InType;
		Attachment->Format = InFormat;
		Attachment->InternalFormat = InInternFormat;
		Attachment->DataType = InDataType;
		Attachments.push_back(Attachment);
	}

	void FrameBuffer::SetDepthStencilAttachment(const std::string& DepthTextureName, const std::string& StencilTextureName, FrameBufferAttachmentType InType, FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat, FrameBufferAttachmentDataType InDataType)
	{
		DepthStencilAttachment = std::make_unique<FrameBufferDepthStencilAttachment>();

		DepthStencilAttachment->DepthTextureUniformName = DepthTextureName;
		DepthStencilAttachment->StencilTextureUniformName = StencilTextureName;
		DepthStencilAttachment->Type = InType;
		DepthStencilAttachment->DataType = InDataType;
		DepthStencilAttachment->InternalFormat = InInternFormat;
		DepthStencilAttachment->Format = InFormat;
	}

	void FrameBuffer::SetSize(uint32 InSizeX, uint32 InSizeY, bool bRebuild /*= true*/)
	{
		SizeX = InSizeX;
		SizeY = InSizeY;

		if (bRebuild)
		{
			RebuildBuffer();
		}
	}

	void FrameBuffer::RebuildBuffer()
	{
		for (FrameBufferAttachment* Attachment : Attachments)
		{
			glBindTexture(GL_TEXTURE_2D, Attachment->TextureID);

			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<uint32>(Attachment->InternalFormat),SizeX, SizeY,
				0, static_cast<uint32>(Attachment->Format), static_cast<uint32>(Attachment->DataType), NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<uint32>(Attachment->Type),
				GL_TEXTURE_2D, Attachment->TextureID, 0);
		}

		if (DepthStencilAttachment.get())
		{
			glBindTexture(GL_TEXTURE_2D, DepthStencilAttachment->DepthStencilTextureID);
			
 			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<uint32>(DepthStencilAttachment->InternalFormat), SizeX, SizeY,
 				0, static_cast<uint32>(DepthStencilAttachment->Format), static_cast<uint32>(DepthStencilAttachment->DataType), NULL);

//			glTexStorage2D(GL_TEXTURE_2D, 0, static_cast<uint32>(DepthStencilAttachment->InternalFormat), SizeX, SizeY);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<uint32>(DepthStencilAttachment->Type),
				GL_TEXTURE_2D, DepthStencilAttachment->DepthStencilTextureID, 0);

// 			glBindTexture(GL_TEXTURE_2D, DepthStencilAttachment->StencilTextureID);
// 			glTextureView(DepthStencilAttachment->StencilTextureID, GL_TEXTURE_2D, DepthStencilAttachment->DepthStencilTextureID,
// 				GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
// 			glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);

			glBindTexture(GL_TEXTURE_2D, DepthStencilAttachment->DepthTextureID);
			glTextureView(DepthStencilAttachment->DepthTextureID, GL_TEXTURE_2D, DepthStencilAttachment->DepthStencilTextureID,
				GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);

		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}