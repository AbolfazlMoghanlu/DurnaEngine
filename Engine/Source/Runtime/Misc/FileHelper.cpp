#include "DurnaPCH.h"
#include "FileHelper.h"

LOG_DEFINE_CATEGORY(LogFileHelper, "FileHelper")

namespace Durna
{
	bool FileHelper::ReadStringFromTextFile(const char* FilePath, std::string& Str)
	{
		std::ifstream in(FilePath, std::ios::in | std::ios::binary);
		if (!in)
		{
			LOG(LogFileHelper, Warning, "Could not open file \"%s\"", FilePath);

			in.close();
			return false;
		}

		in.seekg(0, std::ios::end);
		Str.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&Str[0], Str.size());
		in.close();

		return true;
	}

}