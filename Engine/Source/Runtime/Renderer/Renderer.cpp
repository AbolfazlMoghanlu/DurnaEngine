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

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::unique_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	StaticMeshActor* Renderer::PlaneActor;

	std::shared_ptr<Durna::FrameBuffer> Renderer::GBuffer = nullptr;

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

		AssetLibrary::Init();

		RenderCommands::EnableDepthTest();
		RenderCommands::SetClearColor(LinearColor(0.2f, 0.2f, 0.3f, 1.0f));

		RenderCommands::EnableBackFaceCulling();

		//glEnable(GL_STENCIL_TEST);
		//glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		ImGuiRenderer::Get()->Init();

		GBuffer = FrameBuffer::Create();
		GBuffer->Bind();
		GBuffer->AddAttachment("Buffer_Depth", FrameBufferAttachmentType::Depth, FrameBufferAttachmentFormat::Depth, FrameBufferAttachmentFormat::Depth);
		GBuffer->AddAttachment("Buffer_Color", FrameBufferAttachmentType::Color_0, FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA);
		GBuffer->SetSize(800, 600);

		PlaneActor = new StaticMeshActor;

		PlaneActor->GetMeshComponent()->SetStaticMesh(&BaseShapes::Plane, 1);
		PlaneActor->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::PP);
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		GBuffer->Unbind();

		RenderCommands::ClearColorBuffer();
		RenderCommands::DisableDepthTest();
		
		RenderCommands::DrawFrameBufferToScreen(GBuffer.get(), AssetLibrary::PP);

		ImGuiRenderer::Get()->Tick(DeltaTime);	

		glfwPollEvents();
		glfwSwapBuffers(MainWindow->GetGLFWWindow());

		GBuffer->Bind();
		RenderCommands::EnableDepthTest();

		RenderCommands::ClearColorBuffer();
		RenderCommands::ClearDepthBuffer();
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
		if (GBuffer.get())
		{
			GBuffer->SetSize(InWidth, InHeight);
		}
	}

}