#pragma once

namespace Durna
{
	struct VertexBufferLayout
	{
	public:
		VertexBufferLayout(std::vector<float>* InData, bool InbNormalized, unsigned int InCount);

		~VertexBufferLayout();

		std::vector<float>* Data;
		unsigned int Offset;
		bool bNormalized;
		unsigned int Count;
	};

	class VertexBuffer
	{
	public:
		
		VertexBuffer();
		VertexBuffer(const std::vector<VertexBufferLayout>& Layouts);

		~VertexBuffer();

		void UpdateVertexData();

		void UpdateVertexAttributes();

		void AddLayout(VertexBufferLayout Layout);

		void Bind();

		void UnBind();

	private:

		unsigned int ID;
	
		std::vector<VertexBufferLayout>	Layouts;

		unsigned int Stride = 0;

		bool bDynamic = false;
	};

	class ElementBuffer
	{
	public:
		ElementBuffer(const std::vector<float>& Elements);

		~ElementBuffer();

		void Bind();

		void Unbind();

	private:
		void UpdateBuffer(const std::vector<float>& Elements) const;

		unsigned int ID;

	};
}

