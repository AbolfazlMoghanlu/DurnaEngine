#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class WorldOutlinerGuiLayer;

	class Actor;

	class WorldOutliner
	{
	public:
		WorldOutliner();
		~WorldOutliner();

		void Init();
		void Tick(float DeltaTime);

		static WorldOutliner* Get();

	protected:
		std::unique_ptr<WorldOutlinerGuiLayer> OutlinerGui;

	private:
		static std::unique_ptr<WorldOutliner> SingletonInstance;
	};
}
#endif