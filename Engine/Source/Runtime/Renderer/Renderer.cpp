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

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::unique_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	unsigned int Renderer::framebuffer;

	unsigned int Renderer::textureColorbuffer;

	unsigned int Renderer::rbo;

	StaticMeshActor* Renderer::PlaneActor;

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


		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		//glEnable(GL_STENCIL_TEST);
		//glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		ImGuiRenderer::Get()->Init();

		glGenFramebuffers(1, &framebuffer);
		glGenTextures(1, &textureColorbuffer);
		glGenRenderbuffers(1, &rbo);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);


		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		PlaneActor = new StaticMeshActor;

		PlaneActor->GetMeshComponent()->SetStaticMesh(&BaseShapes::Plane, 1);
		PlaneActor->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::PP);
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
		glClear(GL_COLOR_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		RenderCommands::DrawPrimitive(PlaneActor->GetMeshComponent());


		ImGuiRenderer::Get()->Tick(DeltaTime);

		glfwPollEvents();
		glfwSwapBuffers(MainWindow->GetGLFWWindow());

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
}