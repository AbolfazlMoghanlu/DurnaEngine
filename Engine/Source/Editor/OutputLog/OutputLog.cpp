#include "DurnaPCH.h"
#include "OutputLog.h"

#if WITH_EDITOR
#include "Editor/OutputLog/OutputLogGuiLayer.h"

namespace Durna
{
	std::unique_ptr<OutputLog> OutputLog::SingletonInstance;

	OutputLog::OutputLog()
	{ }

	OutputLog::~OutputLog()
	{ }

	void OutputLog::Init()
	{
		OutputLogLayer = std::make_unique<OutputLogGuiLayer>();
		OutputLogLayer->Attach();

		Logs.push_back("Log1");
		Logs.push_back("Log2");
		Logs.push_back("Log3");
		Logs.push_back("Log4");
		Logs.push_back("Log5");
		Logs.push_back("Log6");
		Logs.push_back("Log7");
		Logs.push_back("Log8");

	}

	void OutputLog::Tick(float DeltaTime)
	{

	}

	OutputLog* OutputLog::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<OutputLog>();
		}

		return SingletonInstance.get();
	}
}

#endif