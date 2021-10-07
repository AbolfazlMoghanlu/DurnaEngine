#include "DurnaPCH.h"
#include "Shader.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Durna
{

	Shader::Shader(const char* VertexShaderSource, const char* FragmentShaderSource)
	{
		CompileShader(VertexShaderSource, FragmentShaderSource);
	}

	Shader::Shader(const char* FilePath)
	{
		std::string VertexShaderSource;
		std::string FragmentShaderSource;

		if (ReadShaderSourceFromFile(FilePath, VertexShaderSource, FragmentShaderSource))
		{
			CompileShader(VertexShaderSource.c_str(), FragmentShaderSource.c_str());
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(ID);
	}

	bool Shader::CompileShader(const char* VertexShaderSource, const char* FragmentShaderSource)
	{
		unsigned int VS, FS;
		if (!CompileVertexShader(VertexShaderSource, VS) || !CompileFragmentShader(FragmentShaderSource, FS))
		{
			glDeleteShader(VS);
			glDeleteShader(FS);
			return false;
		}

		glDeleteProgram(ID);
		ID = glCreateProgram();

		if (!LinkShaders(VS, FS))
		{
			glDeleteProgram(ID);
			glDeleteShader(VS);
			glDeleteShader(FS);
			return false;
		}
		
		glDeleteShader(VS);
		glDeleteShader(FS);
		return true;
	}

	void Shader::Use()
	{
		glUseProgram(ID);
	}

	bool Shader::CompileVertexShader(const char* VertexShaderSource, unsigned int &ID)
	{
		ID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(ID, 1, &VertexShaderSource, nullptr);
		glCompileShader(ID);
	
		int Success;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &Success);

		if (!Success)
		{

#if DRN_DEBUG || DRN_RELEASE
			char InfoLog[512];
			glGetShaderInfoLog(ID, 512, NULL, InfoLog);

			//TODO: log class
			std::cout << "Vertex shader complation failed:\n" << InfoLog << std::endl;

#endif
			return false;
		}

		return true;
	}


	bool Shader::CompileFragmentShader(const char* FragmentShaderSource, unsigned int &ID)
	{
		ID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(ID, 1, &FragmentShaderSource, nullptr);
		glCompileShader(ID);

		int Success;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &Success);

		if (!Success)
		{

#if DRN_DEBUG || DRN_RELEASE
			char InfoLog[512];
			glGetShaderInfoLog(ID, 512, NULL, InfoLog);

			//TODO: log class
			std::cout << "Fragment shader complation failed:\n" << InfoLog << std::endl;

#endif
			return false;
		}

		return true;
	}

	bool Shader::LinkShaders(unsigned int VertexShader, unsigned int FragmentShader)
	{
		glAttachShader(ID, VertexShader);
		glAttachShader(ID, FragmentShader);

		glLinkProgram(ID);

		int Success;
		glGetProgramiv(ID, GL_LINK_STATUS, &Success);

		if (!Success)
		{
#if DRN_DEBUG || DRN_RELEASE
			char InfoLog[512];
			glGetProgramInfoLog(ID, 512, NULL, InfoLog);

			//TODO: log class
			std::cout << "Shader program linkage failed:\n" << InfoLog << std::endl;

#endif
			return false;
		}
		return true;
	}

	bool Shader::ReadShaderSourceFromFile(const char* FilePath, std::string& VertexShaderSource, std::string& FragmentShaderSource)
	{
		std::ifstream in(FilePath, std::ios::in | std::ios::binary);
		if (!in)
		{
			//TODO log calss
			std::cout << "Could not open file '" << FilePath << "'\n";

			in.close();
			return false;
		}

		std::string Source;
		in.seekg(0, std::ios::end);
		Source.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&Source[0], Source.size());
		in.close();

		// Readed whole file

		bool FoundVertexShader = false;
		bool FoundFragmentShader = false;

		const char* TypeToken = "#type";
		size_t TypeTokenLength = strlen(TypeToken);
		size_t Pos = Source.find(TypeToken, 0);
		while (Pos != std::string::npos)
		{
			size_t eol = Source.find_first_of("\r\n", Pos);

			if (eol == std::string::npos)
			{
				//TODO: log class
				std::cout << "Syntax error in'" << FilePath << "'\n";
				return false;
			}

			size_t Begin = Pos + TypeTokenLength + 1;
			std::string Type = Source.substr(Begin, eol - Begin);

			size_t NextLinePos = Source.find_first_of("\r\n", eol);
			Pos = Source.find(TypeToken, NextLinePos);
			std::string TokenisedSource = Source.substr(NextLinePos, Pos - (NextLinePos == std::string::npos ? Source.size() - 1 : NextLinePos));

			if (Type == "vertex")
			{
				if (FoundVertexShader)
				{
					//TODO: log class
					std::cout << "There is already a vertex shader defined in '" << FilePath << "'!\n";
					return false;
				}
				VertexShaderSource = TokenisedSource;
				FoundVertexShader = true;
			}

			else if (Type == "fragment")
			{
				if (FoundFragmentShader)
				{
					//TODO: log class
					std::cout << "There is already a fragment shader defined in '" << FilePath << "'!\n";
					return false;
				}
				FragmentShaderSource = TokenisedSource;
				FoundFragmentShader = true;
			}

			else
			{
				//TODO: log class
				std::cout << "Wrong shader type" << Type << "in '" << FilePath << "'!\n";
				return false;
			}

		}

		return true;
	}

}