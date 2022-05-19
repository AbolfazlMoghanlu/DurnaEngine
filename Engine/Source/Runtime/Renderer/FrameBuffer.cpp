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
		for (int32 i = 0; i < Attachments.size() ; i++)
		{
			Texture::ActivateTexture(i);
			glBindTexture(GL_TEXTURE_2D, Attachments[i]->TextureID);

			int UniformLocation = glGetUniformLocation(ShaderID, Attachments[i]->TextureUniformName.c_str());
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

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}