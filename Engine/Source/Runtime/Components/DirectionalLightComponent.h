#pragma once

#include "Runtime/Components/LightComponent.h"

namespace Durna
{
	class DirectionalLightComponent : public LightComponent
	{
	public:
		DirectionalLightComponent(const std::string& InLabel);
		virtual ~DirectionalLightComponent();

		virtual void Tick(float DateTime) override;

	protected:
		virtual void UpdateViewMatrix() override;
		virtual void UpdateProjectionMatrix() override;


	private:
	};
}

