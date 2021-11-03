#include "DurnaPCH.h"
#include "RenderCommands.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Runtime/Engine/BaseShapes.h"

namespace Durna
{
	RenderCommands::RenderCommands()
	{

	}

	RenderCommands::~RenderCommands()
	{

	}

	void RenderCommands::DrawPrimitive(PrimitiveComponent& Comp)
	{
		Comp.VB->Bind();
		
		if(Comp.bDirtyBuffer)
		{
			Comp.VB->UpdateVertexData();
			Comp.bDirtyBuffer = false;
		}

		Comp.VB->UpdateVertexAttributes();
		Comp.EB->Bind();
		
		Comp.MeshShader->Use();
		
		glDrawElements(GL_TRIANGLES, (int)Comp.Mesh->VertexIndices.size(), GL_UNSIGNED_INT, 0);
	}

}