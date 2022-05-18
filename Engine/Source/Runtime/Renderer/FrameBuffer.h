#pragma once

namespace Durna
{
	enum class FrameBufferAttachmentType : uint32
	{
		Color_0 = 0x8CE0, //GL_COLOR_ATTACHMENT0
		Depth24_Stencil8 = 0x88F0 //GL_DEPTH24_STENCIL8
	};
	
	class FrameBufferAttachment
	{
	public:
		FrameBufferAttachment();
		virtual ~FrameBufferAttachment();
		
		FrameBufferAttachmentType Type = FrameBufferAttachmentType::Color_0;
		uint32 TextureID;
	};
	
	class FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();

		static std::shared_ptr<FrameBuffer> Create();

		void Bind();
		void Unbind();

		void ClearAttachments();
		void AddAttachment(FrameBufferAttachmentType InType);

		void SetSize(uint32 InSizeX, uint32 InSizeY, bool bRebuild = true);
		void RebuildBuffer();

		std::vector<FrameBufferAttachment*> Attachments;
	protected:
	
		uint32 ID;


		uint32 SizeX = 800;
		uint32 SizeY = 600;

	private:
	};
}

