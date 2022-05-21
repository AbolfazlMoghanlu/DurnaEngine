#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

//#include <imgui.h>

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

#include "Runtime/renderer/FrameBuffer.h"
#include "Runtime/Renderer/RenderQueue.h"

#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Renderer/GBuffer.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

#if WITH_EDITOR
	#include "Editor/Settings/Settings.h"
#endif


LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::unique_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	std::shared_ptr<GBuffer> Renderer::Gbuffer = nullptr;

	RenderQueue Renderer::RenderQue;

	Material Renderer::PostProccessMaterial;
	PostProcessSetting Renderer::PPSetting;

	
	LinearColor Renderer::AmbientLightColor = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	float Renderer::AmbientLightIntensity = 1.0f;

	LinearColor Renderer::DiffuseLightColor = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	float Renderer::DiffuseLightIntensity = 1.0f;
	Rotatorf Renderer::DiffuseLightRation = Rotatorf(50.0f, 180.0f, 0.0f);

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

		MainWindow = std::make_unique <Window>("DurnaEngine", 800, 600);

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

		PostProccessMaterial.SetShader(AssetLibrary::PostProcessShader);
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		Gbuffer->Bind();
		Gbuffer->BindDrawBuffers();

		RenderCommands::ClearColorBuffer();

		RenderCommands::EnableDepthTest();
		RenderCommands::ClearDepthBuffer();

		RenderCommands::EnableStencilTest();
		RenderCommands::ClearStencilBuffer();


		for (PrimitiveComponent* Pr : RenderQue.Queue)
		{
			if (Pr)
			{
				RenderCommands::DrawPrimitive(Pr);
			}
		}

		Gbuffer->Unbind();
		Gbuffer->UnbindDrawBuffers();

		RenderCommands::ClearColorBuffer();
		RenderCommands::DisableDepthTest();
		RenderCommands::DisableStencilTest();


		PostProccessMaterial.GetShader()->Use();
#if WITH_EDITOR
		UpdatePostProcessUniforms();
#endif
		
 		RenderCommands::DrawFrameBufferToScreen(Gbuffer.get(), &PostProccessMaterial);


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

	void Renderer::OnResizeWindow(int32 InWidth, int32 InHeight)
	{
		if (Gbuffer.get())
		{
			Gbuffer->SetSize(InWidth, InHeight);
		}

		if (CameraComponent* CameraComp = CameraManager::Get()->GetActiveCamera())
		{
			CameraComp->SetPerspectiveWidth((float)InWidth);
			CameraComp->SetPerspectiveHeight((float)InHeight);
			CameraManager::Get()->MarkDirtyProjection();
		}
	}

	void Renderer::RegisterToRenderQueue(PrimitiveComponent* Pr)
	{
		RenderQue.AddPrimitive(Pr);
	}

}