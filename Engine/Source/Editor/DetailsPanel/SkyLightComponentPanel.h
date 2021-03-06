#pragma once

#if WITH_EDITOR

#include "Editor/DetailsPanel/DetailPanelInterface.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class SkyLightComponent;

	class SkyLightComponentPanel : public DetailPanelInterface
	{
	public:
		SkyLightComponentPanel(SkyLightComponent* InTarget);

		virtual void DrawPanel() override;

	protected:
		SkyLightComponent* Target;
	};
}

#endif
