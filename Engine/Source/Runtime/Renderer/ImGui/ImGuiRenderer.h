#pragma once

#include "Runtime/Containers/List.h"

namespace Durna
{
	class ImGuiLayer;

	class ImGuiRenderer
	{
	public:
		ImGuiRenderer();
		virtual ~ImGuiRenderer();

		virtual void Init();
		virtual void Tick(float DeltaTime);

		void AttachLayer(ImGuiLayer* InLayer);

		static ImGuiRenderer* Get();

		float SkyLightIntensity = 1.0f;

	protected:
		virtual void BeginDraw();
		virtual void Draw();
		virtual void EndDraw();

	private:
		static std::unique_ptr<ImGuiRenderer> SingletonInstance;
		LinkedList<ImGuiLayer> Layers;
	};
}