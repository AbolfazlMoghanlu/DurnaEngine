#include "DurnaPCH.h"
#include "RenderCommands.h"

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Math/TranslationMatrix.h"
#include "Runtime/Math/RotationMatrix.h"
#include "Runtime/Math/ScaleMatrix.h"
#include "Runtime/Renderer/Renderer.h"

#include "Runtime/Engine/Actor.h"

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

		TranslationMatrix<float> Translation = TranslationMatrix<float>(Comp.GetWorldLocation());
		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Translation", Translation.M[0]);

		RotationMatrix<float> Rotation = RotationMatrix<float>(Comp.GetWorldRotation());
		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Rotation", Rotation.M[0]);

		ScaleMatrix<float> Scale = ScaleMatrix<float>(Comp.GetWorldScale());
		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Scale", Scale.M[0]);

		Comp.SourceMaterial->GetShader()->SetUniform1f("time", Renderer::Time);
		
		glDrawElements(GL_TRIANGLES, Comp.EB->GetCount(), GL_UNSIGNED_INT, 0);
	}
}