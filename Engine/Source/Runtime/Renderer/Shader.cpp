#include "DurnaPCH.h"
#include "Shader.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

LOG_DEFINE_CATEGORY(LogShader, "Shader");

namespace Durna
{

	Shader::Shader(const char* VertexShaderSource, const char* FragmentShaderSource)
	{
		CompileShader(VertexShaderSource, FragmentShaderSource);
	}

	Shader::Shader(const char* FilePath)
	{
		LOG(LogShader, Info, "Compiling shader from file \"%s\"", FilePath);
		std::string VertexShaderSource;
		std::string FragmentShaderSource;

		if (ReadShaderSourceFromFile(FilePath, VertexShaderSource, FragmentShaderSource))
		{
			if (CompileShader(VertexShaderSource.c_str(), FragmentShaderSource.c_str()))
			{
				LOG(LogShader, Info, "Shader compiled successfuly \"%s\".", FilePath);
			}
		}
	}
	
	Shader::Shader(const std::string& FilePath) : Shader(FilePath.c_str())
	{
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

	void Shader::SetUniformVec3f(char* UniformName, Vector3f Vec3)
	{
		int UniformLocation = glGetUniformLocation(ID, UniformName);
		glUniform3f(UniformLocation, Vec3.X, Vec3.Y, Vec3.Z);
	}

	void Shader::SetUniform1i(const std::string& UniformName, int32 Value)
	{
		int UniformLocation = glGetUniformLocation(ID, UniformName.c_str());
		glUniform1i(UniformLocation, Value);
	}

	bool Shader::CompileVertexShader(const char* VertexShaderSource, unsigned int& ID)
	{
		ID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(ID, 1, &VertexShaderSource, nullptr);
		glCompileShader(ID);
	
		int Success;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &Success);

		if (!Success)
		{
#ifndef DRN_DIST
			char InfoLog[512];
			glGetShaderInfoLog(ID, 512, NULL, InfoLog);

			LOG(LogShader, Error, "Vertex shader complation failed:\n%s", InfoLog);
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

#ifndef DRN_DIST
			char InfoLog[512];
			glGetShaderInfoLog(ID, 512, NULL, InfoLog);

			LOG(LogShader, Error, "Fragment shader complation failed:\n%s", InfoLog);
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
#ifndef DRN_DIST
			char InfoLog[512];
			glGetProgramInfoLog(ID, 512, NULL, InfoLog);

			LOG(LogShader, Error, "Shader program linkage failed:\n%s", InfoLog)
#endif
			return false;
		}
		return true;
	}

	bool Shader::ReadShaderSourceFromFile(const char* FilePath, std::string& VertexShaderSource, std::string& FragmentShaderSource)
	{
		std::string Source;
		if (!FileHelper::ReadStringFromTextFile(FilePath, Source))
		{
			LOG(LogShader, Error, "Shader compilation failed to bad file \"%s\".", FilePath);

			return false;
		}

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
				LOG(LogShader, Error, "Syntax error in shader file \"%s\"", FilePath);
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
					LOG(LogShader, Error, "There is already a vertex shader defined in shader file \"%s\".", FilePath);
					return false;
				}
				VertexShaderSource = TokenisedSource;
				FoundVertexShader = true;
			}

			else if (Type == "fragment")
			{
				if (FoundFragmentShader)
				{
					LOG(LogShader, Error, "There is already a fragment shader defined in shader file \"%s\".", FilePath);
					return false;
				}
				FragmentShaderSource = TokenisedSource;
				FoundFragmentShader = true;
			}

			else
			{
				LOG(LogShader, Error, "Invalid shader type \"%s\" in shader file \"%s\".", Type.c_str(), FilePath);
				return false;
			}

		}

		return true;
	}

}