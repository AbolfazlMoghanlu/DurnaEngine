#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

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

		float FOV		= 45.0f;
		float Width		= 800.0f;
		float Heigth	= 600.0f;
		float MinZ		= 2.0f;
		float MaxZ		= 5.0f;
	};

	struct OrthographicProjectionData
	{
		OrthographicProjectionData(float InWidth, float InHeight, float InZScale, float InZOffset)
			: Width(InWidth), Heigth(InHeight), ZScale(InZScale), ZOffset(InZOffset)
		{}

		OrthographicProjectionData()
			: OrthographicProjectionData(800.0f, 600.0f, 0.01f, 2.0f)
		{}

		float Width = 800.0f;
		float Heigth = 600.0f;
		float ZScale = 0.01f;
		float ZOffset = 2.0f;
	};

	class Camera
	{
	public:
		Camera();

		Vector3f GetCameraPosition() const;
		void AddCameraWorldOffset(const Vector3f& PositionOffset);

		Rotatorf GetCameraRotation() const;
		void AddCameraWorldRotation(const Rotatorf& RotationOffset);

		void SetProjectionMode(EProjectionMode InProjectionMode);
		EProjectionMode GetProjectionMode() const;

		void SetFOV(float InFOV);
		float GetFOV() const;

		void SetPerspectiveWidth(float InWidth);
		float GetPerspectiveWidth() const;

		void SetPerspectiveHeight(float InHeight);
		float GetPerspectiveHeight() const;

		void SetPerspectiveMinZ(float InMinZ);
		float GetPerspectiveMinZ() const;

		void SetPerspectiveMaxZ(float InMaxZ);
		float GetPerspectiveMaxZ() const;

	private:
		Vector3f Position = Vector3f::ZeroVector;
		Rotatorf Rotation = Rotatorf::ZeroRotator;

		EProjectionMode ProjectionMode = EProjectionMode::Perspective;
		PerspectiveProjectionData PerspectiveData;
		OrthographicProjectionData OrthographicData;
		

	};
}

