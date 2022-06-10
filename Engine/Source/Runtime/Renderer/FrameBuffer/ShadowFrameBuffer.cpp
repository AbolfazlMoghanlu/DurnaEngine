#include "DurnaPCH.h"
#include "ShadowFrameBuffer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Durna
{
	ShadowFrameBuffer::ShadowFrameBuffer()
	{
		AddAttachment("Buffer_Shadow", FrameBufferAttachmentType::Depth,
			FrameBufferAttachmentFormat::Depth, FrameBufferAttachmentFormat::Depth,
			FrameBufferAttachmentDataType::Float);

		RebuildBuffer();
		TextureID = Attachments[0]->TextureID;

		Bind();

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	ShadowFrameBuffer::~ShadowFrameBuffer()
	{ 
		
	}

	std::shared_ptr<ShadowFrameBuffer> ShadowFrameBuffer::Create()
	{
		return std::make_shared<ShadowFrameBuffer>();
	}

	uint32 ShadowFrameBuffer::GetTextureID() const
	{
		return TextureID;
	}
}