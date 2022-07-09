#include "DurnaPCH.h"
#include "LinearColor.h"

namespace Durna
{
	LinearColor LinearColor::operator*(float F)
	{
		R *= F; G *= F; B *= F; A *= F;
		return *this;
	}

	LinearColor const LinearColor::Black = LinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	LinearColor const LinearColor::White = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);
}