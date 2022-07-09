#pragma once

#include "Runtime/Components/LightComponent.h"

namespace Durna
{
	class PointLightComponent : public LightComponent
	{
	public:
		PointLightComponent(const std::string& InLabel);
		virtual ~PointLightComponent();

		virtual void Tick(float DeltaTime) override;

		virtual void UpdateProjectionMatrix() override;
		virtual void UpdateViewMatrix() override;

	protected:

	private:
		friend class PointLightComponentPanel;
	};
}

