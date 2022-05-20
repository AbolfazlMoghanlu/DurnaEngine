#pragma once

namespace Durna
{
	enum class FrameBufferAttachmentType : uint32
	{
		Color_0				= 0x8CE0, //GL_COLOR_ATTACHMENT0
		Depth				= 0x8D00, //GL_DEPTH_ATTACHMENT
		Stencil				= 0x8D20, //GL_STENCIL_ATTACHMENT
		Depth_Stencil		= 0x821A  //GL_DEPTH_STENCIL_ATTACHMENT
	};

	enum class FrameBufferAttachmentFormat : uint32
	{
		RGBA				= 0x1908, //GL_RGBA
		Depth				= 0x1902, //GL_DEPTH_COMPONENT
		Stencil				= 0x1901, //GL_STENCIL_INDEX
		Stencil_8			= 0x8D48, //GL_STENCIL_INDEX8
		Depth24_Stencil8	= 0x88F0, //GL_DEPTH24_STENCIL8
		Depth_Stencil		= 0x84F9, //GL_DEPTH_STENCIL
	};

	enum class FrameBufferAttachmentDataType : uint32
	{
		uByte				= 0x1401, //GL_UNSIGNED_BYTE
		uInt_24_8			= 0x84FA  //GL_UNSIGNED_INT_24_8
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
		FrameBufferAttachmentDataType DataType = FrameBufferAttachmentDataType::uByte;

		uint32 TextureID;
	};

	class FrameBufferDepthStencilAttachment
	{
	public:
		FrameBufferDepthStencilAttachment();

		virtual ~FrameBufferDepthStencilAttachment();

		std::string DepthTextureUniformName = "InvalidTexture";
		std::string StencilTextureUniformName = "InvalidTexture";

		FrameBufferAttachmentType Type = FrameBufferAttachmentType::Depth_Stencil;
		FrameBufferAttachmentFormat Format = FrameBufferAttachmentFormat::RGBA;
		FrameBufferAttachmentFormat InternalFormat = FrameBufferAttachmentFormat::RGBA;
		FrameBufferAttachmentDataType DataType = FrameBufferAttachmentDataType::uByte;

		uint32 DepthStencilTextureID;
		uint32 DepthTextureID;
		uint32 StencilTextureID;
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
			FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat, FrameBufferAttachmentDataType InDataType);

		void SetDepthStencilAttachment(const std::string& DepthTextureName, const std::string& StencilTextureName, FrameBufferAttachmentType InType,
			FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat, FrameBufferAttachmentDataType InDataType);
		
		void SetSize(uint32 InSizeX, uint32 InSizeY, bool bRebuild = true);
		void RebuildBuffer();

		std::vector<FrameBufferAttachment*> Attachments;
		std::unique_ptr<FrameBufferDepthStencilAttachment> DepthStencilAttachment;

	protected:
		uint32 ID;

		uint32 SizeX = 800;
		uint32 SizeY = 600;

	private:
		friend class RenderCommands;
	};
}

