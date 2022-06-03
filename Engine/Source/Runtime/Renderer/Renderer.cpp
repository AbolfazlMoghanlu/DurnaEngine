#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Engine/BaseShapes.h"

#include "runtime/Engine/GameFramwork/StaticMeshActor.h"
#include "Runtime/renderer/RenderCommands.h"
#include "runtime/Components/PrimitiveComponent.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

#include "Runtime/Math/LinearColor.h"

#include "Runtime/renderer/FrameBuffer/FrameBuffer.h"
#include "Runtime/Renderer/RenderQueue.h"

#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Renderer/FrameBuffer/GBuffer.h"
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

#include "Runtime/Engine/GameFramwork/GameSettings.h"
#include "Runtime/Math/ViewMatrix.h"

#if WITH_EDITOR
	#include "Editor/Settings/Settings.h"
#endif


LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::shared_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	std::shared_ptr<GBuffer> Renderer::Gbuffer = nullptr;
	std::shared_ptr<ResolveDefferedBuffer> Renderer::ResolvedBuffer = nullptr;
	std::shared_ptr<FrameBuffer> Renderer::ShadowFBO = nullptr;

	RenderQueue Renderer::RenderQue;

	Material Renderer::PostProccessMaterial;
	Material Renderer::ResolvedMaterial;

	PostProcessSetting Renderer::PPSetting;

	
	LinearColor Renderer::AmbientLightColor = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	float Renderer::AmbientLightIntensity = 1.0f;

	LinearColor Renderer::DiffuseLightColor = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	float Renderer::DiffuseLightIntensity = 0.3f;
	Rotatorf Renderer::DiffuseLightRation = Rotatorf(270.0f, 180.0f, 0.0f);

	void Renderer::UpdatePostProcessUniforms()
	{
		if (PostProccessMaterial.GetShader())
		{
			PostProccessMaterial.Use();
			
#if WITH_EDITOR

			// Display buffer
			PostProccessMaterial.GetShader()->SetUniform1i("DisplayBufer",
				static_cast<int32>(Settings::Get()->GetDisplayBuffer()));
#endif

			// Fog
			PostProccessMaterial.GetShader()->SetUniformVec3f("FogColor", PPSetting.FogColor);
			PostProccessMaterial.GetShader()->SetUniform1f("FogAmount", PPSetting.FogAmount);
			PostProccessMaterial.GetShader()->SetUniform1f("FogOffset", PPSetting.FogOffset);
			PostProccessMaterial.GetShader()->SetUniform1f("FogLength", PPSetting.FogLength);

			//Blur
			PostProccessMaterial.GetShader()->SetUniform1f("BlurStepSize", PPSetting.BlurStepSize);
			PostProccessMaterial.GetShader()->SetUniform1i("BlurStepNumber", PPSetting.BlurStepNumber);

			// Light
			PostProccessMaterial.GetShader()->SetUniformVec3f("AmbientLightColor", AmbientLightColor);
			PostProccessMaterial.GetShader()->SetUniform1f("AmbientLightIntensity", AmbientLightIntensity);

			PostProccessMaterial.GetShader()->SetUniformVec3f("DiffuseLightColor", DiffuseLightColor);
			PostProccessMaterial.GetShader()->SetUniform1f("DiffuseLightIntensity", DiffuseLightIntensity);
			PostProccessMaterial.GetShader()->SetUniformVec3f("DiffuseLightDirection", DiffuseLightRation.GetForwardVector());
		}
	}

	Renderer::Renderer()
	{ }

	Renderer::~Renderer()
	{ }

	void Renderer::Init()
	{
		LOG(LogRenderer, Info, "Initializing.");

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		MainWindow = Window::Create("DurnaEngine", 800, 600);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG(LogRenderer, Error, "Failed to initialize GLAD");
			return;
		}

		ImGuiRenderer::Get()->Init();

		AssetLibrary::Init();

		RenderCommands::SetClearColor(LinearColor(0.2f, 0.2f, 0.3f, 1.0f));
		RenderCommands::EnableBackFaceCulling();

		RenderCommands::SetStencilOperationReplace();

		Gbuffer = GBuffer::Create();
		ResolvedBuffer = ResolveDefferedBuffer::Create();
		ShadowFBO = FrameBuffer::Create();
		ShadowFBO->AddAttachment("Buffer_ShadowMap", FrameBufferAttachmentType::Depth,
			FrameBufferAttachmentFormat::Depth, FrameBufferAttachmentFormat::Depth,
			FrameBufferAttachmentDataType::Float);
		ShadowFBO->SetSize(1024, 1024);

		PostProccessMaterial.SetShader(AssetLibrary::PostProcessShader);
		UpdatePostProcessUniforms();

		ResolvedMaterial.SetShader(AssetLibrary::ResolvedShader);
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		RenderCommands::SetViewportSize(IntPoint(1024, 1024));
		ShadowFBO->Bind();
//		ShadowFBO->BindDrawBuffers();
 		glDrawBuffer(GL_NONE);
 		glReadBuffer(GL_NONE);
 		glClear(GL_DEPTH_BUFFER_BIT);
 		glEnable(GL_DEPTH_TEST);


		Vector3f LightForwardVector = DiffuseLightRation.GetForwardVector();
		Vector3f LightRightVector = Vector3f::CrossProduct(Vector3f::UpVector, LightForwardVector).Normalize();
		Vector3f LightUpVector = Vector3f::CrossProduct(LightForwardVector, LightRightVector).Normalize();

		ViewMatrix<float> LightViewMatrix = ViewMatrix<float>(Vector3f(0.5f, 0, 1.0f),
			LightForwardVector, LightRightVector, LightUpVector);

		for (PrimitiveComponent* Pr : RenderQue.Queue)
		{
			if (Pr)
			{
				RenderCommands::DrawPrimitive(Pr, LightViewMatrix);
			}
		}


		Gbuffer->Bind();
		Gbuffer->BindDrawBuffers();

		RenderCommands::ClearColorBuffer();

		RenderCommands::EnableDepthTest();
		RenderCommands::ClearDepthBuffer();

		RenderCommands::EnableStencilTest();
		RenderCommands::ClearStencilBuffer();

		RenderCommands::SetViewportSize(MainWindow->Resolution);

		for (PrimitiveComponent* Pr : RenderQue.Queue)
		{
			if (Pr)
			{
				RenderCommands::DrawPrimitive(Pr);
				//RenderCommands::DrawPrimitive(Pr, LightViewMatrix);
			}
		}

		Gbuffer->Unbind();
		Gbuffer->UnbindDrawBuffers();

		RenderCommands::DisableDepthTest();
		RenderCommands::DisableStencilTest();

		ResolvedBuffer->Bind();
		ResolvedBuffer->BindDrawBuffers();
		RenderCommands::ClearColorBuffer();


		PostProccessMaterial.GetShader()->Use();
#if WITH_EDITOR
		// if there is editor keep uniforms in update with parameters in ui
		UpdatePostProcessUniforms();
#endif
		
		PostProccessMaterial.GetShader()->Use();
		Texture::ActivateTexture(6);
		glBindTexture(GL_TEXTURE_2D, ShadowFBO->Attachments[0]->TextureID);

		int UniformLocation = glGetUniformLocation(PostProccessMaterial.GetShader()->ID, "ShadowMap");
		glUniform1i(UniformLocation, 6);

		PostProccessMaterial.GetShader()->SetUniformMatrix4f("LightMatrix", LightViewMatrix.M[0]);

		PostProccessMaterial.GetShader()->SetUniformMatrix4f("View", CameraManager::Get()->GetCameraViewMatrix());
		PostProccessMaterial.GetShader()->SetUniformMatrix4f("Projection", CameraManager::Get()->GetProjectionMatrix());


 		RenderCommands::DrawFrameBufferToScreen(Gbuffer.get(), &PostProccessMaterial);

		ResolvedBuffer->Unbind();
		ResolvedBuffer->Unbind();
		RenderCommands::ClearColorBuffer();

#if !WITH_EDITOR	
		RenderCommands::SetViewportSize(MainWindow->ConstraintedResolution, MainWindow->ConstraintedOffset);

		// if editor is present, we draw resolved buffer to viewport so there is no need to draw resolved buffer to glfw window
		RenderCommands::DrawFrameBufferToScreen(ResolvedBuffer.get(), &ResolvedMaterial);
#endif

#if WITH_EDITOR
		ImGuiRenderer::Get()->Tick(DeltaTime);
#endif

		glfwPollEvents();
		glfwSwapBuffers(MainWindow->GetGLFWWindow());

		RenderQue.Clear();
	}

	void Renderer::Shutdown()
	{
		LOG(LogRenderer, Info, "Shutingdown");
		glfwTerminate();
	}

	Window* Renderer::GetWindow()
	{
		return MainWindow.get();
	}

	float Renderer::GetTime()
	{
		return Time;
	}

	void Renderer::OnResolutionChanged(const IntPoint& InResolution)
	{
		ResizeBuffers(InResolution);
	}

	void Renderer::ResizeBuffers(const IntPoint& InResolution)
	{
		if (Gbuffer.get())
		{
			Gbuffer->SetSize(InResolution.X, InResolution.Y);
		}
		if (ResolvedBuffer.get())
		{
			ResolvedBuffer->SetSize(InResolution.X, InResolution.Y);
		}
	}

	void Renderer::RegisterToRenderQueue(PrimitiveComponent* Pr)
	{
		RenderQue.AddPrimitive(Pr);
	}
}