#pragma once

LOG_DECLARE_CATEGORY(LogAssert);

#define ensure(x, Format , ...)					\
if (!(x))													\
{															\
LOG(LogAssert, Error, Format, __VA_ARGS__);					\
std::abort();												\
}										