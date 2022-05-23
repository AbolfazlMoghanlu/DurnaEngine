#pragma once

namespace Durna
{
	enum class FrameBufferAttachmentType : uint32
	{
		Color_0				= 0x8CE0, //GL_COLOR_ATTACHMENT0
		Color_1				= 0x8CE1, //GL_COLOR_ATTACHMENT1
		Color_2				= 0x8CE2, //GL_COLOR_ATTACHMENT2
		Color_3				= 0x8CE3, //GL_COLOR_ATTACHMENT3
		Depth				= 0x8D00, //GL_DEPTH_ATTACHMENT
		Stencil				= 0x8D20, //GL_STENCIL_ATTACHMENT
		Depth_Stencil		= 0x821A  //GL_DEPTH_STENCIL_ATTACHMENT
	};

	enum class FrameBufferAttachmentFormat : uint32
	{
		Depth				= 0x1902, //GL_DEPTH_COMPONENT
		Stencil				= 0x1901, //GL_STENCIL_INDEX
		Stencil_8			= 0x8D48, //GL_STENCIL_INDEX8
		Depth24_Stencil8	= 0x88F0, //GL_DEPTH24_STENCIL8
		Depth_Stencil		= 0x84F9, //GL_DEPTH_STENCIL
		RGB					= 0x1907, //GL_RGB 
		RGBA				= 0x1908, // GL_RGBA
		RGB32f				= 0x8815, //GL_RGB32F
		RGBA32f				= 0x8814  //GL_RGBA32F
	};

	enum class FrameBufferAttachmentDataType : uint32
	{
		uByte				= 0x1401, //GL_UNSIGNED_BYTE
		uInt_24_8			= 0x84FA, //GL_UNSIGNED_INT_24_8
		Float				= 0x1406  //GL_FLOAT
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
	
	class FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();

		static std::shared_ptr<FrameBuffer> Create();

		void Bind();
		void Unbind();

		void BindDrawBuffers();
		void UnbindDrawBuffers();

		virtual void BindTextures(uint32 ShaderID);

		void ClearAttachments();
		void AddAttachment(const std::string& TextureUniformName, FrameBufferAttachmentType InType,
			FrameBufferAttachmentFormat InFormat, FrameBufferAttachmentFormat InInternFormat, FrameBufferAttachmentDataType InDataType);
	
		void SetSize(uint32 InSizeX, uint32 InSizeY, bool bRebuild = true);
		virtual void RebuildBuffer();

		std::vector<FrameBufferAttachment*> Attachments;

	protected:
		uint32 ID;

		uint32 SizeX = 800;
		uint32 SizeY = 600;

	private:
		friend class RenderCommands;
	};
}