#pragma once

#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	struct PostProcessSetting
	{
		// Fog
		LinearColor FogColor = LinearColor(0.82f, 0.84f, 1.0f, 1.0f);
		float FogAmount = 0.0f;
		float FogOffset = 0.6f;
		float FogLength = 2.0f;

		// Blur
		float BlurStepSize = 0.0f;
		int32 BlurStepNumber = 0;
	};
}