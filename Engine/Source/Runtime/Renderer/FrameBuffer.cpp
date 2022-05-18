#include "DurnaPCH.h"
#include "FrameBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	void FrameBuffer::ClearAttachments()
	{
		for (FrameBufferAttachment* Attachment : Attachments)
		{
			delete Attachment;
		}

		Attachments.clear();
	}

	void FrameBuffer::AddAttachment(FrameBufferAttachmentType InType)
	{
		FrameBufferAttachment* Attachment = new FrameBufferAttachment();
		Attachment->Type = InType;
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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SizeX, SizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
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