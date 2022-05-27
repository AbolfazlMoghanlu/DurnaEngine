#pragma once

#ifndef DRN_DIST

#define LOG_DECLARE_CATEGORY(Category)													\
extern LogCategory Category;

#define LOG_DEFINE_CATEGORY(Category , Name)											\
LogCategory Category(Name);

#define LOG(Category , Verbose , Format , ...)											\
{																						\
	Verbosity VerbosityLevel = Verbosity::##Verbose;									\
	Durna::DateTime DTime = Durna::DateTime::Now();										\
	char MsgText[500];																	\
	std::snprintf(MsgText, 500, Format##"\n", __VA_ARGS__);								\
	LogMessage LogMsg(&Category, VerbosityLevel, DTime, MsgText);						\
	PrintLogToConsole(LogMsg);															\
}


#define LOG_VERBOSE_LEVEL(Verbose)														\
Log::VerboseLevel = Verbosity::##Verbose;

#define LOG_ENABLE_CATEGORY(Category)													\
Category.Suppressed = false;

#define LOG_DISABLE_CATEGORY(Category)													\
Category.Suppressed = true;

#else
#define LOG_DECLARE_CATEGORY(Category)	
#define LOG_DEFINE_CATEGORY(Category , Name)
#define LOG(Category , Verbose , Format , ...)
#define LOG_VERBOSE_LEVEL(Verbose)
#define LOG_ENABLE_CATEGORY(Category)
#define LOG_DISABLE_CATEGORY(Category)
#endif 


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
	LogMessage(LogCategory* InCategory, Verbosity InVerboseLevel, const Durna::DateTime& InTime, const std::string& InMessage)
		: Category(InCategory), VerboseLevel(InVerboseLevel), Time(InTime), Message(InMessage)
	{ }

	LogCategory* Category;
	Verbosity VerboseLevel;

	Durna::DateTime Time;
	std::string Message;
};

void PrintLogToConsole(const LogMessage& InLogMessage);