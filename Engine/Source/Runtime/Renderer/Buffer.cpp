#include "DurnaPCH.h"
#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

LOG_DEFINE_CATEGORY(LogBuffer, "Buffer");

namespace Durna
{
	VertexBuffer::VertexBuffer()
		: VertexElementCount(0) , VertexCount(0)
	{
		glGenBuffers(1, &ID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::AddLayout(const VertexBufferLayout& Layout)
	{
		ensure(Layout.Data->size() == (size_t)VertexCount * (size_t)Layout.Count,
			"Bad vertex layout data size.");
		Layouts.push_back(Layout);
		VertexElementCount += Layout.Count;
	}

	void VertexBuffer::SetVertexCount(int32 InCount)
	{
		VertexCount = InCount;
	}

	void VertexBuffer::UpdateLayout()
	{
		Buffer.clear();

		Buffer.resize((size_t)VertexElementCount * (size_t)VertexCount);

		uint32 Offset = 0;

		for (uint32 i = 0; i < Layouts.size(); i++)
		{
			for (uint32 j = 0; j < VertexCount; j++)
			{
				for (uint32 k = 0; k < Layouts[i].Count; k++)
				{
					Buffer[(size_t)j * VertexElementCount + k + Offset] = Layouts[i].Data->at((size_t)j * Layouts[i].Count + k);
				}
			}

			Offset += Layouts[i].Count;
		}
	}

	void VertexBuffer::UpdateAttributes()
	{
		glBufferData(GL_ARRAY_BUFFER, (size_t)VertexElementCount * (size_t)VertexCount * sizeof(float), &Buffer[0], GL_STATIC_DRAW);

		uint32 Offset = 0;
		for (uint32 i = 0; i < Layouts.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Layouts[i].Count, GL_FLOAT, Layouts[i].bNormalized
				, VertexElementCount * sizeof(float), (void*)(size_t)Offset);
		
			Offset += Layouts[i].Count * sizeof(float);
		}
	}

	void VertexBuffer::Clear()
	{
		SetVertexCount(0);
		Layouts.clear();
		Buffer.clear();
	}

	VertexElementBuffer::VertexElementBuffer()
	{
		glGenBuffers(1, &ID);
	}

	VertexElementBuffer::~VertexElementBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void VertexElementBuffer::SetIndices(std::vector<uint32>* InIndices)
	{
		Indices = InIndices;
	}

	uint32 VertexElementBuffer::GetCount() const
	{
		return static_cast<uint32>(Indices->size());
	}

	void VertexElementBuffer::UpdateBuffer() const
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices->size() * sizeof(float), &Indices->at(0), GL_STATIC_DRAW);
	}

	void VertexElementBuffer::Clear()
	{
		Indices = nullptr;
	}
}