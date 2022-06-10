#pragma once

#if WITH_EDITOR

#include "Editor/DetailsPanel/DetailPanelInterface.h"

namespace Durna
{
	class DirectionalLightComponent;

	class DirectionalLightComponentPanel : public DetailPanelInterface
	{
	public:
		DirectionalLightComponentPanel(DirectionalLightComponent* InTarget);

		virtual void DrawPanel() override;

	private:
		DirectionalLightComponent* Target;

		bool bChachedCastShadow = false;
		int32 CachedShadowResolution = 0;
	};
}

#endif