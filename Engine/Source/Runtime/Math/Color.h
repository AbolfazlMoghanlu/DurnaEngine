#pragma once

#include "Durna.h"

namespace Durna
{
	struct Color
	{
		uint8 R, G, B, A;

		Color() : R(0), G(0), B(0), A(255) {};
		Color(uint8 InInt) : R(InInt), G(InInt), B(InInt), A(255) {};
		Color(uint8 InR, uint8 InG, uint8 InB, uint8 InA) : R(InR), G(InG), B(InB), A(InA) {};

		static Color const Black;
		static Color const White;
	};
}
