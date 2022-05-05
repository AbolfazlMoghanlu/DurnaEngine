#pragma once

namespace Durna
{
	// TODO: Support more data types, now only support float

	struct VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: Data(nullptr), Count(0), bNormalized(false)
		{}

		VertexBufferLayout(std::vector<float>* InData, uint32 InCount, bool InbNormalized)
			: Data(InData), Count(InCount), bNormalized(InbNormalized)
		{}

		std::vector<float>* Data;
		uint32 Count;
		bool bNormalized;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void Bind() const;
		void AddLayout(const VertexBufferLayout& Layout);
		void SetVertexCount(int32 InCount);
		void UpdateLayout();
		void UpdateAttributes();
		void Clear();

	private:
		uint32 VertexCount;
		uint32 VertexElementCount;
		std::vector<VertexBufferLayout> Layouts;
		std::vector<float> Buffer;
		uint32 ID;
	};

	class VertexElementBuffer
	{
	public:
		VertexElementBuffer();
		~VertexElementBuffer();

		void Bind() const;
		void SetIndices(std::vector<uint32>* InIndices);
		uint32 GetCount() const;
		void UpdateBuffer() const;
		void Clear();

	private:
		std::vector<uint32>* Indices = nullptr;
		uint32 ID;
	};
}

