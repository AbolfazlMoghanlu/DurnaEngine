#pragma once

namespace Durna
{
	class Image;

	enum class ETextureSlot : uint32
	{
		Texture0	= 0x84C0,
		Texture1	= 0x84C1,
		Texture2	= 0x84C2,
		Texture3	= 0x84C3,
		Texture4	= 0x84C4,
		Texture5	= 0x84C5,
		Texture6	= 0x84C6,
		Texture7	= 0x84C7,
		Texture8	= 0x84C8,
		Texture9	= 0x84C9,
		Texture10	= 0x84CA,
		Texture11	= 0x84CB,
		Texture12	= 0x84CC,
		Texture13	= 0x84CD,
		Texture14	= 0x84CE,
		Texture15	= 0x84CF,
		Texture16	= 0x84D0
	};

	
	class Texture
	{
	public:
		Texture();
		Texture(Image* Img);
		~Texture();

		void Bind() const;
		void UnBind() const;
		void UpdateTexture();

		void SetSource(Image* Img);
		Image* GetSource() const;

		bool IsDirty() const;
		void MarkDirty();

	private:
		unsigned int ID;
		Image* SourceImage;
		bool bDirtyFlag;
	};
}

