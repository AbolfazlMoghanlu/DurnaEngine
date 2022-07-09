#include "DurnaPCH.h"
#include "PointLightComponent.h"

#include "Runtime/Renderer/Renderer.h"

#if WITH_EDITOR
#include "Editor/DetailsPanel/PointLightComponentPanel.h"
#endif

namespace Durna
{
	PointLightComponent::PointLightComponent(const std::string& InLabel)
		: LightComponent(InLabel)
	{
#if WITH_EDITOR
		Panel = new PointLightComponentPanel(this);
#endif
	}

	PointLightComponent::~PointLightComponent()
	{ }

	void PointLightComponent::Tick(float DeltaTime)
	{
		LightComponent::Tick(DeltaTime);

		if (IsVisible())
		{
			Renderer::RegisterPointLight(this);
		}
	}

	void PointLightComponent::UpdateProjectionMatrix()
	{

	}

	void PointLightComponent::UpdateViewMatrix()
	{

	}
}