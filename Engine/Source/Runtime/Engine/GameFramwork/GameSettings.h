#pragma once

namespace Durna
{
	class GameSettings
	{
	public:
		GameSettings();
		virtual ~GameSettings();

		static GameSettings* Get();

		EWindowMode GetWindowMode() const;
		void SetWindowMode(EWindowMode InWindowMode);

		IntPoint GetResolution() const;
		void SetResolution(const IntPoint& InSize);

		void ApplySettings();

	protected:
		EWindowMode WindowMode = EWindowMode::BorderlessWindowed;
		IntPoint Resolution = IntPoint(1440, 900);
		
	private:
		static std::unique_ptr<GameSettings> SingletonInstance; 

		void ApplyResolutionSetting();
	};
}