#pragma once

#if WITH_EDITOR

#include "Editor/DetailsPanel/DetailPanelInterface.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class PointLightComponent;

	class PointLightComponentPanel : public DetailPanelInterface
	{
	public:
		PointLightComponentPanel(PointLightComponent* InTarget);

		virtual void DrawPanel() override;

	protected:
		PointLightComponent* Target;
	};
}

#endif