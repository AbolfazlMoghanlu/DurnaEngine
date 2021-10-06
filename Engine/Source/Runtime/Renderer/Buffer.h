#pragma once

namespace Durna
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<float>& VertexPosition, const std::vector<float>& VertexColor);
		
		~VertexBuffer();

		bool GenerateVertexBuffer(const std::vector<float>& VertexPosition, const std::vector<float>& VertexColor);

		void Bind();

		void UnBind();

	private:
		unsigned int ID;

		std::vector<float> VertexBufferData;
	};
}

