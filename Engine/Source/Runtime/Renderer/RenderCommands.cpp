#include "DurnaPCH.h"
#include "RenderCommands.h"

#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/BaseShapes.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
		Comp.VB->UpdateAttributes();

 		Comp.EB->Bind();
		Comp.EB->UpdateBuffer();
		
		Comp.SourceMaterial->Use();
		
		glDrawElements(GL_TRIANGLES, Comp.EB->GetCount(), GL_UNSIGNED_INT, 0);
	}
}