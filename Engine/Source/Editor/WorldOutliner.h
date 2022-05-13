#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"
#endif

namespace Durna
{
#if WITH_EDITOR

	class WorldOutlinerGuiLayer;

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

	class WorldOutlinerGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;

		
	};

#endif
}

