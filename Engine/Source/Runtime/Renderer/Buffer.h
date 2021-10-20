#pragma once

namespace Durna
{
	struct VertexBufferLayout
	{
	public:
		VertexBufferLayout(std::vector<float>* InData, bool InbNormalized, unsigned int InCount);

		~VertexBufferLayout();

		std::vector<float>* Data;
		int Offset;
		bool bNormalized;
		int Count;
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
		ElementBuffer();
		ElementBuffer(const std::vector<int>& Elements);

		~ElementBuffer();

		void Bind();

		void Unbind();

	private:
		void UpdateBuffer(const std::vector<int>& Elements) const;

		unsigned int ID;

		bool bDynamic = false;
	};
}

