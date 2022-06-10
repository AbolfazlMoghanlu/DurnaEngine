#pragma once

#include "Durna.h"

namespace Durna
{
	enum class EProjectionMode : uint8
	{
		Perspective, Orthographic
	};

	struct PerspectiveProjectionData
	{
		PerspectiveProjectionData(float InFOV, float InWidth, float InHeight, float InMinZ, float InMaxZ)
			: FOV(InFOV), Width(InWidth), Heigth(InHeight), MinZ(InMinZ), MaxZ(InMaxZ)
		{}

		PerspectiveProjectionData()
			: PerspectiveProjectionData(45.0f, 800.0f, 600.0f, 2.0f, 5.0f)
		{}

		float FOV = 45.0f;
		float Width = 800.0f;
		float Heigth = 600.0f;
		float MinZ = 2.0f;
		float MaxZ = 5.0f;
	};

	struct OrthographicProjectionData
	{
		OrthographicProjectionData(float InWidth, float InHeight, float InZScale, float InZOffset)
			: Width(InWidth), Heigth(InHeight), ZScale(InZScale), ZOffset(InZOffset)
		{}

		OrthographicProjectionData()
			: OrthographicProjectionData(800.0f, 600.0f, 0.005f, 150.0f)
		{}

		float Width = 800.0f;
		float Heigth = 600.0f;
		float ZScale = 0.005f;
		float ZOffset = 150.0f;
	};


	struct MinimalViewInfo
	{
		Vector3f Location;
		Rotatorf Rotation;
	};
}