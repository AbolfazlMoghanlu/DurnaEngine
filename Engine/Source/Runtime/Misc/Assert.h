#pragma once

LOG_DECLARE_CATEGORY(LogAssert);

#define ensure(x, ...)										\
if (!x)														\
{															\
LOG(LogAssert, Error, "Assertion failed: %s. "#__VA_ARGS__	\
"\nFile: %s, Line: %i."										\
, #x, FILE_NAME, __LINE__);									\
															\
std::abort();												\
}										
