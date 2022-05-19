#pragma once

#if WITH_EDITOR

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

	protected:
		std::unique_ptr<PostProcessSettingGuiLayer> OutlinerGui;

	private:
		static std::unique_ptr<Settings> SingletonInstance;
	};
}

#endif