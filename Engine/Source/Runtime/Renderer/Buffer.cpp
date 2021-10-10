#include "DurnaPCH.h"
#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

LOG_DEFINE_CATEGORY(LogBuffer, "Buffer");

namespace Durna
{
	VertexBuffer::VertexBuffer(const std::vector<float>& VertexPosition, const std::vector<float>& VertexColor)
	{
		glGenBuffers(1, &ID);

		GenerateVertexBuffer(VertexPosition, VertexColor);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	bool VertexBuffer::GenerateVertexBuffer(const std::vector<float>& VertexPosition, const std::vector<float>& VertexColor)
	{
		if (VertexPosition.size() % 3 != 0 || VertexColor.size() % 4 != 0 
			|| VertexPosition.size() / 3 != VertexColor.size() / 4)
		{
			LOG(LogBuffer, Error, "Couldn't generate vertexbuffer because of bad vertexposition and vertexcolor size");
			return false;
		}

		VertexBufferData.clear();
		VertexBufferData.reserve(VertexPosition.size() + VertexColor.size());

 		for (int i = 0; i * 3 < VertexPosition.size() ; i++)
 		{
			for (int j = 0; j < 3; j++)
			{
				VertexBufferData.push_back(VertexPosition[(i * 3) + j]);
			}

			for (int j = 0; j < 4; j++)
			{
				VertexBufferData.push_back(VertexColor[(i * 4) + j]);
			}
 		}

		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferData) * sizeof(float), &VertexBufferData[0], GL_STATIC_DRAW);

		return true;
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}