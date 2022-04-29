#pragma once

#ifndef DRN_DIST

#define LOG_DECLARE_CATEGORY(Category)																		\
extern LogCategory Category;

#define LOG_DEFINE_CATEGORY(Category , Name)																\
LogCategory Category(Name);

#define LOG(Category , Verbose , Format , ...)																\
if (!Category.Suppressed && Verbosity::##Verbose <= Log::VerboseLevel)													\
{																											\
	std::unordered_map<const Verbosity, int>::const_iterator f = Log::ColorCodes.find(Verbosity::##Verbose);\
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);																\
	SetConsoleTextAttribute(h, f->second);																	\
	auto now = std::chrono::system_clock::now();															\
	auto Ttime = std::chrono::system_clock::to_time_t(now);													\
	std::cout << std::put_time(std::localtime(&Ttime), "[%d/%m/%Y_%X]");									\
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


#else
#define LOG_DECLARE_CATEGORY(Category)	
#define DEFINE_LOG_CATEGORY(Category)
#define LOG(Category , Verbose , Format , ...)
#define LOG_VERBOSE_LEVEL(Verbose)
#define LOG_ENABLE_CATEGORY(Category)
#define LOG_DISABLE_CATEGORY(Category)
#endif 


