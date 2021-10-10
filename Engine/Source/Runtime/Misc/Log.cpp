#include "DurnaPCH.h"
#include "Log.h"

#if defined(DRN_DEBUG) || defined(DRN_RELEASE)

Verbosity Log::VerboseLevel = Verbosity::Info;

std::unordered_map<Verbosity, int> Log::ColorCodes = 
{
	{Verbosity::Info, 15},
	{Verbosity::Warning, 9},
	{Verbosity::Error, 4}
};

#endif