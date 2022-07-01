#pragma once

namespace Durna
{
	enum class ETextureSlot : uint32
	{
		Texture0 = 0x84C0,
		Texture1 = 0x84C1,
		Texture2 = 0x84C2,
		Texture3 = 0x84C3,
		Texture4 = 0x84C4,
		Texture5 = 0x84C5,
		Texture6 = 0x84C6,
		Texture7 = 0x84C7,
		Texture8 = 0x84C8,
		Texture9 = 0x84C9,
		Texture10 = 0x84CA,
		Texture11 = 0x84CB,
		Texture12 = 0x84CC,
		Texture13 = 0x84CD,
		Texture14 = 0x84CE,
		Texture15 = 0x84CF,
		Texture16 = 0x84D0
	};

	enum class ECubemapFace : uint32
	{
		Top		= 0x8517, // GL_TEXTURE_CUBE_MAP_POSITIVE_Y
		Bottom	= 0x8518, // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
		Right	= 0x8515, // GL_TEXTURE_CUBE_MAP_POSITIVE_X
		Left	= 0x8516, // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
		Front	= 0x8519, // GL_TEXTURE_CUBE_MAP_POSITIVE_Z
		Back	= 0x851A  // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	enum class StencilMaskBitfield : uint32
	{
		Bit_None	= 0,
		Bit_1		= 1,
		Bit_2		= 2,
		Bit_3		= 4,
		Bit_4		= 8,
		Bit_5		= 16,
		Bit_6		= 32,
		Bit_7		= 64,
		Bit_8		= 128,
		Bit_All		= 255
	};

	enum class DisplayBuffer : int32
	{
		FinalColor		 = 0,
		SceneColor			,
		BaseColor			,
		WorldNormal			,
		SceneDepth			,
		Stencil				,
		Specular			,
		Roughness			,
		Metallic			,
		AO					,
		ShadingModel		,
		Max
	};

	enum class EShadingModel : int32
	{
		DefaultLit		= 0,
		Unlit			
	};

	std::string DisplayBufferToString(int32 InDisplayBuffer);

	enum class EWindowMode : uint8
	{
		FullScreen = 0,
		Windowed,
		BorderlessFullscreen
	};
}