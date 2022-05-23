#include "DurnaPCH.h"
#include "ResolveDefferedBuffer.h"

namespace Durna
{
	
	ResolveDefferedBuffer::ResolveDefferedBuffer()
	{
		AddAttachment("Buffer_Color", FrameBufferAttachmentType::Color_0,
			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA,
			FrameBufferAttachmentDataType::uByte);

		RebuildBuffer();

		TextureID = Attachments[0]->TextureID;
	}

	ResolveDefferedBuffer::~ResolveDefferedBuffer()
	{

	}

	std::shared_ptr<ResolveDefferedBuffer> ResolveDefferedBuffer::Create()
	{
		return std::make_shared<ResolveDefferedBuffer>();
	}

	uint32 ResolveDefferedBuffer::GetTextureID() const
	{
		return TextureID;
	}

}