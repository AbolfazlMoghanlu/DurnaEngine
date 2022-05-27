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

		const std::vector<LogMessage>& GetLogMessages() const;
		void AddLogMessage(const LogMessage& InLogMessage);
		void AddLogMessage(LogCategory* InLogCategory, Verbosity InVerbosity,
			const DateTime& InTime, const std::string& InMessage);

	protected:
		std::unique_ptr<OutputLogGuiLayer> OutputLogLayer;
		std::vector<LogMessage> LogMessages;

	private:
		static std::unique_ptr<OutputLog> SingletonInstance;
	};
}

#endif