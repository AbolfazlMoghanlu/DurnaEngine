#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Vector2.h"
#include "Runtime/Math/Color.h"
#include "Runtime/Math/LinearColor.h"

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

		void SetUniform1i(const std::string& UniformName, int32 Value);
		void SetUniform1f(const std::string& UniformName, float Value);
		void SetUniform2f(const std::string& UniformName, Vector2f Value);
		void SetUniformVec3f(char* UniformName, const Vector3f& Vec3);
		void SetUniformVec3f(char* UniformName, const Color& InColor);
		void SetUniformVec3f(char* UniformName, const LinearColor& InColor);
		void SetUniformMatrix4f(const std::string& UniformName, float* Value);

		unsigned int ID;

	private:

		bool CompileVertexShader(const char* VertexShaderSource, unsigned int &ID);
		bool CompileFragmentShader(const char* FragmentShaderSource, unsigned int &ID);

		bool LinkShaders(unsigned int VertexShader, unsigned int FragmentShader);

		bool ReadShaderSourceFromFile(const char* FilePath, std::string& VertexShaderSource, std::string& FragmentShaderSource);
		
		friend class RenderCommands;
	};
}
