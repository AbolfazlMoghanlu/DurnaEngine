#include "DurnaPCH.h"
#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

LOG_DEFINE_CATEGORY(LogBuffer, "Buffer");

namespace Durna
{
	VertexBufferLayout::VertexBufferLayout(std::vector<float>* InData, bool InbNormalized, unsigned int InCount)
		: Data(InData)
		, bNormalized(InbNormalized)
		, Count(InCount)
	{
		
	}

	VertexBufferLayout::~VertexBufferLayout()
	{
		
	}

	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &ID);
	}

	VertexBuffer::VertexBuffer(const std::vector<VertexBufferLayout>& Layouts)
	{
		for (const VertexBufferLayout& Layout : Layouts)
		{
			AddLayout(Layout);
		}
		UpdateVertexData();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexBuffer::UpdateVertexData()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);

		int VertexCount = Layouts[0].Data->size() / 3;

		LOG(LogBuffer, Info, "VertexCount: %i", VertexCount);

		// TODO: only in debug 
		for (const VertexBufferLayout Layout : Layouts)
		{
			ensure(Layout.Data->size() / Layout.Count == VertexCount 
				&& Layout.Data->size() % Layout.Count == 0,
				"VertexBuffer data size is invalid");
		}

		std::vector<float> VertexData;
		VertexData.resize(Stride * VertexCount);

		int Offset = 0;

		for (int i = 0; i < Layouts.size(); i++)
		{
			for (int j = 0; j < Layouts[i].Count; j++)
			{
				for (int k = 0; k < VertexCount; k++)
				{
					int VertexDataIndex = (k * Stride / sizeof(float)) + Offset + j;
					VertexData[VertexDataIndex] = Layouts[i].Data->at((Layouts[i].Count * k) + j);
				}
			}

			Offset += Layouts[i].Count;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * sizeof(float), &VertexData[0], bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	void VertexBuffer::UpdateVertexAttributes()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		
		for (int i = 0; i < Layouts.size(); i++)
		{
			//TODO: support primary types
			const VertexBufferLayout& Layout = Layouts[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Layouts[i].Count, GL_FLOAT, Layouts[i].bNormalized, Stride, (void*)Layouts[i].Offset);
		}
	}

	void VertexBuffer::AddLayout(VertexBufferLayout Layout)
	{
		Layout.Offset = Stride;
		Layouts.push_back(Layout);
		
		//TODO: support primary types 
		Stride += Layout.Count * sizeof(float);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);

		UpdateVertexAttributes();
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}