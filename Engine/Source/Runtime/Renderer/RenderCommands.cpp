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
#include "Runtime/Renderer/FrameBuffer/FrameBuffer.h"
#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Renderer/CommonRenderUniforms.h"
#include "Runtime/Window/Window.h"

#include "Runtime/Engine/Actor.h"

#include "Editor/Editor.h"

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

	void RenderCommands::DrawPrimitive(PrimitiveComponent* Comp)
	{
		Comp->VA->Bind();
		Comp->SourceMaterial->Use();

		//  ---------------- Matrices --------------------------
		ScaleRotationTranslationMatrix<float> Transform(Comp->GetWorldScale(), Comp->GetWorldRotation(), Comp->GetWorldLocation());
		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("Transform", Transform.M[0]);

		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("View", CameraManager::Get()->GetCameraViewMatrix());

		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("Projection", CameraManager::Get()->GetProjectionMatrix());
		Comp->SourceMaterial->GetShader()->SetUniform1f("WFactor", CameraManager::Get()->GetWFactor());
		// -----------------------------------------------------

		if (Comp->PreDrawFunc != nullptr)
		{
			Comp->PreDrawFunc(Comp, Comp->SourceMaterial->GetShader());
		}

		uint32 StencilValue = Comp->StencilValue;
		uint32 StencilMask = static_cast<uint32>(Comp->StencilValue);

#if WITH_EDITOR
		if (Editor::Get()->IsOwningActorSelected(Comp) & 
			(!Editor::Get()->bIsAnyComponentSelected() || Editor::Get()->IsComponentSelected(Comp)))
		{
			StencilValue |= 128;
			StencilMask |= 128;
		}
#endif

		glStencilFunc(GL_ALWAYS, StencilValue, 0xFF);
		glStencilMask(StencilMask);

		Comp->GetMaterial()->GetShader()->SetUniform1i("ShadingModel",
			static_cast<int32>(Comp->GetMaterial()->GetShadingModel()));
		
		glDrawElements(GL_TRIANGLES, Comp->EB->GetCount(), GL_UNSIGNED_INT, 0);
	}


	void RenderCommands::DrawPrimitive(PrimitiveComponent* Comp, const Matrix<float>& InViewMatrix, const Matrix<float>& InOrthu)
	{
		Comp->VA->Bind();
		Comp->SourceMaterial->Use();

		//  ---------------- Matrices --------------------------
		ScaleRotationTranslationMatrix<float> Transform(Comp->GetWorldScale(), Comp->GetWorldRotation(), Comp->GetWorldLocation());
		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("Transform", Transform.M[0]);

		Matrix V = InViewMatrix;
		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("View", V.M[0]);

		Matrix O = InOrthu;
		Comp->SourceMaterial->GetShader()->SetUniformMatrix4f("Projection", O.M[0]);
		Comp->SourceMaterial->GetShader()->SetUniform1f("WFactor", CameraManager::Get()->GetWFactor());
		// -----------------------------------------------------

 		if (Comp->PreDrawFunc != nullptr)
 		{
 			Comp->PreDrawFunc(Comp, Comp->SourceMaterial->GetShader());
 		}

		uint32 StencilValue = Comp->StencilValue;
		uint32 StencilMask = static_cast<uint32>(Comp->StencilValue);

#if WITH_EDITOR
		if (Editor::Get()->IsOwningActorSelected(Comp) &
			(!Editor::Get()->bIsAnyComponentSelected() || Editor::Get()->IsComponentSelected(Comp)))
		{
			StencilValue |= 128;
			StencilMask |= 128;
		}
#endif

		glStencilFunc(GL_ALWAYS, StencilValue, 0xFF);
		glStencilMask(StencilMask);

		glDrawElements(GL_TRIANGLES, Comp->EB->GetCount(), GL_UNSIGNED_INT, 0);
	}

	void RenderCommands::DrawFrameBufferToScreen(FrameBuffer* InFrameBuffer, Material* InMaterial)
	{
		if (InFrameBuffer && InMaterial && InMaterial->GetShader())
		{
			InMaterial->GetShader()->Use();
			InFrameBuffer->BindTextures(InMaterial->GetShader()->ID);

			CommonRenderUniforms::UploadCameraLocation(InMaterial->GetShader());

			AssetLibrary::ScreenQuad->VA->Bind();
			glDrawElements(GL_TRIANGLES, AssetLibrary::ScreenQuad->EB->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}

	void RenderCommands::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void RenderCommands::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void RenderCommands::SetClearColor(const LinearColor& ClearColor)
	{
		glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
	}

	void RenderCommands::EnableBackFaceCulling()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
	}

	void RenderCommands::DisableBackFaceCulling()
	{
		glDisable(GL_CULL_FACE);
	}

	void RenderCommands::EnableStencilTest()
	{
		glEnable(GL_STENCIL_TEST);
	}

	void RenderCommands::DisableStencilTest()
	{
		glDisable(GL_STENCIL_TEST);
	}

	void RenderCommands::SetStencilOperationReplace()
	{
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	}

	void RenderCommands::ClearColorBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommands::ClearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommands::ClearStencilBuffer()
	{
		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	void RenderCommands::SetDrawWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void RenderCommands::SetViewportSize(const IntPoint& Size, const IntPoint& Offset)
	{
		glViewport(Offset.X, Offset.Y, Size.X, Size.Y);
	}

}