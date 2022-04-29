#include "DurnaPCH.h"
#include "RenderCommands.h"

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Math/TranslationMatrix.h"
#include "Runtime/Renderer/Renderer.h"

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

		TranslationMatrix<float> Translation = TranslationMatrix<float>(Comp.WorldLocation);

		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Translation", Translation.M[0]);

		Comp.SourceMaterial->GetShader()->SetUniform1f("time", Renderer::Time);
		
		glDrawElements(GL_TRIANGLES, Comp.EB->GetCount(), GL_UNSIGNED_INT, 0);
	}
}