#pragma once

#if WITH_EDITOR

#include "Runtime/Renderer/RenderTypes.h"

namespace Durna
{
	class PostProcessSettingGuiLayer;

	class Settings
	{
	public:
		Settings();
		~Settings();

		void Init();
		void Tick(float DeltaTime);

		static Settings* Get();

		DisplayBuffer GetDisplayBuffer() const;

	protected:
		std::unique_ptr<PostProcessSettingGuiLayer> OutlinerGui;

	private:
		static std::unique_ptr<Settings> SingletonInstance;

		DisplayBuffer DisplayBufferMode = DisplayBuffer::FinalColor;

		friend class PostProcessSettingGuiLayer;
	};
}

#endif