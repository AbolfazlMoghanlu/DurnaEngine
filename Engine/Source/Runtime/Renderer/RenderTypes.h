#pragma once

namespace Durna
{
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
		FinalColor		= 0,
		BaseColor		= 1,
		WorldNormal		= 2,
		SceneDepth		= 3,
		Stencil			= 4
	};
}