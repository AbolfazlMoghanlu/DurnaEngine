#pragma once

namespace Durna
{
	class ImGuiLayer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		virtual void Init();
		virtual void Tick(float DeltaTime);

		static ImGuiLayer* Get();

		float SkyLightIntensity = 0.5;

	protected:

	private:
		static std::unique_ptr<ImGuiLayer> SingletonInstance;
	};
}

