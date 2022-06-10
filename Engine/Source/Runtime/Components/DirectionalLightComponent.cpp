#include "DurnaPCH.h"
#include "DirectionalLightComponent.h"
#include "Runtime/Math/ViewMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

#if WITH_EDITOR
#include "Editor/DetailsPanel/DirectionalLightComponentPanel.h"
#endif

namespace Durna
{
	DirectionalLightComponent::DirectionalLightComponent(const std::string& InLabel)
		: LightComponent(InLabel)
	{
#if WITH_EDITOR
		Panel = new DirectionalLightComponentPanel(this);
#endif
	}

	DirectionalLightComponent::~DirectionalLightComponent()
	{ 
#if WITH_EDITOR
		delete Panel;
#endif
	}

	void DirectionalLightComponent::Tick(float DateTime)
	{
		LightComponent::Tick(DateTime);


	}

	void DirectionalLightComponent::UpdateViewMatrix()
	{
		Rotatorf ComponentWorldRotation = GetWorldRotation();
		Vector3f ComponentWorldLocation = GetWorldLocation();

		Vector3f ForwardVector = ComponentWorldRotation.GetForwardVector();
		Vector3f RightVector = Vector3f::CrossProduct(Vector3f::UpVector, ForwardVector).Normalize();
		Vector3f UpVector = Vector3f::CrossProduct(ForwardVector, RightVector).Normalize();

		LightViewMatrix = ViewMatrix<float>(ComponentWorldLocation,
			ForwardVector, RightVector, UpVector);
	}

	void DirectionalLightComponent::UpdateProjectionMatrix()
	{
		float MaxDistance = MaxDrawDistance + MaxFadeRange;
		//LightProjectionMatrix = OrthoMatrix<float>(MaxDistance, -MaxDistance, MaxDistance, -MaxDistance,
		//	0.2f, 2.5f);

		LightProjectionMatrix = OrthoMatrix<float>(2.0f, -2.0f, 2.0f, -2.0f,
			0.2f, 2.5f);
	}
}