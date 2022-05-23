#pragma once

#if WITH_EDITOR

namespace Durna
{
	class OutputLogGuiLayer;

	class OutputLog
	{
	public:
		OutputLog();
		~OutputLog();

		void Init();
		void Tick(float DeltaTime);

		static OutputLog* Get();

		std::vector<std::string> Logs;

	protected:
		std::unique_ptr<OutputLogGuiLayer> OutputLogLayer;

	private:
		static std::unique_ptr<OutputLog> SingletonInstance;

	};
}

#endif