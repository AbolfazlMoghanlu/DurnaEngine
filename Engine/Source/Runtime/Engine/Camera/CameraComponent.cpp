#include "DurnaPCH.h"
#include "CameraComponent.h"
#include "Runtime/Engine/Camera/CameraManager.h"

#include "Runtime/Core/Application.h"

namespace Durna
{
	void CameraComponent::Tick(float DeltaTime)
	{
		SceneComponent::Tick(DeltaTime);


	}

	void CameraComponent::Activate()
	{
		CameraManager::Get()->SetActiveCamera(this);
	}

	void CameraComponent::SetProjectionMode(EProjectionMode InProjectionMode)
	{
		ProjectionMode = InProjectionMode;
		CameraManager::Get()->MarkDirtyProjection();
	}

	EProjectionMode CameraComponent::GetProjectionMode() const
	{
		return ProjectionMode;
	}

	void CameraComponent::SetFOV(float InFOV)
	{
		PerspectiveData.FOV = InFOV;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetFOV() const
	{
		return PerspectiveData.FOV;
	}

	void CameraComponent::SetPerspectiveWidth(float InWidth)
	{
		PerspectiveData.Width = InWidth;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetPerspectiveWidth() const
	{
		return PerspectiveData.Width;
	}

	void CameraComponent::SetPerspectiveHeight(float InHeight)
	{
		PerspectiveData.Heigth = InHeight;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetPerspectiveHeight() const
	{
		return PerspectiveData.Heigth;
	}

	void CameraComponent::SetPerspectiveMinZ(float InMinZ)
	{
		PerspectiveData.MinZ = InMinZ;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetPerspectiveMinZ() const
	{
		return PerspectiveData.MinZ;
	}

	void CameraComponent::SetPerspectiveMaxZ(float InMaxZ)
	{
		PerspectiveData.MaxZ = InMaxZ;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetPerspectiveMaxZ() const
	{
		return PerspectiveData.MaxZ;
	}

	void CameraComponent::SetOrthographicWidth(float InWidth)
	{
		OrthographicData.Width = InWidth;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetOrthographicWidth() const
	{
		return OrthographicData.Width;
	}

	void CameraComponent::SetOrthographicHeight(float InHeight)
	{
		OrthographicData.Heigth = InHeight;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetOrthographicHeight() const
	{
		return OrthographicData.Heigth;
	}

	void CameraComponent::SetOrthographicZScale(float InZScale)
	{
		OrthographicData.ZScale = InZScale;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetOrthographicZScale() const
	{
		return OrthographicData.ZScale;
	}

	void CameraComponent::SetOrthographicZOffset(float InZOffset)
	{
		OrthographicData.ZOffset = InZOffset;
		CameraManager::Get()->MarkDirtyProjection();
	}

	float CameraComponent::GetOrthographicZOffset() const
	{
		return OrthographicData.ZOffset;
	}
}