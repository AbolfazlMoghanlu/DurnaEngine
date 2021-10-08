#pragma once

namespace Durna
{
	class Shader
	{
	public:
		Shader(const char* FilePath);
		Shader(const std::string& FilePath);
		Shader(const char* VertexShaderSource, const char* FragmentShaderSource);

		~Shader();

		bool CompileShader(const char* VertexShaderSource, const char* FragmentShaderSource);

		void Use();

	private:

		bool CompileVertexShader(const char* VertexShaderSource, unsigned int &ID);
		bool CompileFragmentShader(const char* FragmentShaderSource, unsigned int &ID);

		bool LinkShaders(unsigned int VertexShader, unsigned int FragmentShader);

		bool ReadShaderSourceFromFile(const char* FilePath, std::string& VertexShaderSource, std::string& FragmentShaderSource);

	private:
		unsigned int ID;
	};
}
