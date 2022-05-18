#pragma once

namespace Durna
{
	enum class FrameBufferAttachmentType : uint32
	{
		Color_0 = 0x8CE0, //GL_COLOR_ATTACHMENT0
		Depth = 0x8D00, //GL_DEPTH_ATTACHMENT
		Depth24_Stencil8 = 0x88F0 //GL_DEPTH24_STENCIL8
	};

	enum class FrameBufferAttachmentFormat : uint32
	{
		RGBA = 0x1908, //GL_RGBA
		Depth = 0x1902, //GL_DEPTH_COMPONENT
	};
	
	class FrameBufferAttachment
	{
	public:
		FrameBufferAttachment();
		virtual ~FrameBufferAttachment();
		
		std::string TextureUniformName = "InvalidTexture";
		FrameBufferAttachmentType Type = FrameBufferAttachmentType::Color_0;
		FrameBufferAttachmentFormat Format = FrameBufferAttachmentFormat::RGBA;
		FrameBufferAttachmentFormat InternalFormat = FrameBufferAttachmentFormat::RGBA;

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

		void BindTextures(uint32 ShaderID);

		void ClearAttachments();
		void AddAttachment(const std::string& TextureUniformName, FrameBufferAttachmentType InType,
			FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat);

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

