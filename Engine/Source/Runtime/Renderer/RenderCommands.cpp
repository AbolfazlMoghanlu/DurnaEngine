#include "DurnaPCH.h"
#include "RenderCommands.h"

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Math/TranslationMatrix.h"
#include "Runtime/Math/RotationMatrix.h"
#include "Runtime/Math/ScaleMatrix.h"
#include "Runtime/Math/ScaleRotationTranslationMatrix.h"
#include "Runtime/Math/PrespectiveMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Engine/Camera/CameraManager.h"

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

		//  ---------------- Matrices --------------------------
		ScaleRotationTranslationMatrix<float> Transform(Comp.GetWorldScale(), Comp.GetWorldRotation(), Comp.GetWorldLocation());
		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Transform", Transform.M[0]);

		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("View", CameraManager::GetCameraViewMatrix());

		Comp.SourceMaterial->GetShader()->SetUniformMatrix4f("Projection", CameraManager::GetProjectionMatrix());
		Comp.SourceMaterial->GetShader()->SetUniform1f("WFactor", CameraManager::GetWFactor());
		// -----------------------------------------------------

		if (Comp.PreDrawFunc != nullptr)
		{
			Comp.PreDrawFunc(Comp.SourceMaterial->GetShader());
		}

		glDrawElements(GL_TRIANGLES, Comp.EB->GetCount(), GL_UNSIGNED_INT, 0);
	}

	
}