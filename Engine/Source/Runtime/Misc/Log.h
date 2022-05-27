#pragma once

#ifndef DRN_DIST

//#include "Editor/OutputLog/OutputLog.h"

#define LOG_DECLARE_CATEGORY(Category)																		\
extern LogCategory Category;

#define LOG_DEFINE_CATEGORY(Category , Name)																\
LogCategory Category(Name);

#define LOG(Category , Verbose , Format , ...)																\
if (!Category.Suppressed && Verbosity::##Verbose <= Log::VerboseLevel)										\
{\
	Verbosity VerbosityLevel = Verbosity::##Verbose;														\
	std::unordered_map<const Verbosity, int>::const_iterator f = Log::ColorCodes.find(VerbosityLevel);		\
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);																\
	SetConsoleTextAttribute(h, f->second);																	\
	std::cout << Durna::DateTime::Now().ToString();																						\
	printf("%s: "##Format##"\n", Category.Name, __VA_ARGS__);												\
	SetConsoleTextAttribute(h, 15);																			\
}

#define LOG_VERBOSE_LEVEL(Verbose)																			\
Log::VerboseLevel = Verbosity::##Verbose;

#define LOG_ENABLE_CATEGORY(Category)																		\
Category.Suppressed = false;

#define LOG_DISABLE_CATEGORY(Category)																		\
Category.Suppressed = true;

enum class Verbosity : unsigned short int
{
	Error = 0,
	Warning,
	Info
};

class Log
{
public:
	static Verbosity VerboseLevel;
	static std::unordered_map<Verbosity, int> ColorCodes;
};

struct LogCategory
{
	LogCategory(char* InName)
	{
		Name = InName;
	}
	char* Name;
	bool Suppressed = false;
};

struct LogMessage
{
	LogMessage(LogCategory* InCategory, Verbosity InVerboseLevel, const std::string& InTime, const std::string& InMessage)
		: Category(InCategory), VerboseLevel(InVerboseLevel), Time(InTime), Message(InMessage)
	{ }

	LogCategory* Category;
	Verbosity VerboseLevel;

	//TODO: use time class
	std::string Time;
	std::string Message;
};

#else
#define LOG_DECLARE_CATEGORY(Category)	
#define DEFINE_LOG_CATEGORY(Category)
#define LOG(Category , Verbose , Format , ...)
#define LOG_VERBOSE_LEVEL(Verbose)
#define LOG_ENABLE_CATEGORY(Category)
#define LOG_DISABLE_CATEGORY(Category)
#endif 