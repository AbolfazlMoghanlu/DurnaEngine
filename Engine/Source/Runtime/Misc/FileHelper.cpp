#include "DurnaPCH.h"
#include "FileHelper.h"

namespace Durna
{
	bool FileHelper::ReadStringFromTextFile(const char* FilePath, std::string& Str)
	{
		std::ifstream in(FilePath, std::ios::in | std::ios::binary);
		if (!in)
		{
#if DRN_DEBUG || DRN_RELEASE
			//TODO log calss
			std::cout << "Could not open file '" << FilePath << "'\n";
#endif
			
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