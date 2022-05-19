#include "DurnaPCH.h"
#include "ImGuiRenderer.h"

#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Durna
{
	class TempLayer : public ImGuiLayer
	{
	public:
		void Draw() override
		{
#if WITH_EDITOR
			ImGui::Begin("Demo window");
			ImGui::SliderFloat("Sky light Intensity ", &ImGuiRenderer::Get()->SkyLightIntensity, 0.0f, 1.0f, NULL, ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
			ImGui::End();
#endif
		}
	};

	std::unique_ptr<ImGuiRenderer> ImGuiRenderer::SingletonInstance = nullptr;

	ImGuiRenderer::ImGuiRenderer()
	{ }

	ImGuiRenderer::~ImGuiRenderer()
	{ }

	void ImGuiRenderer::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(Renderer::GetWindow()->GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");

		AttachLayer(new TempLayer);
	}

	void ImGuiRenderer::Tick(float DeltaTime)
	{
		BeginDraw();
		Draw();
		EndDraw();
	}

	void ImGuiRenderer::AttachLayer(ImGuiLayer* InLayer)
	{
		Layers.AddFirst(InLayer);
	}

	void ImGuiRenderer::BeginDraw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiRenderer::Draw()
	{
#if WITH_EDITOR
		bool bShowDemo = true;
		ImGui::ShowDemoWindow(&bShowDemo);
#endif

		for (LinkedListIterator It(Layers); It; ++It)
		{
			if (It)
			{
				It->Draw();
			}
		}
	}

	void ImGuiRenderer::EndDraw()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(Renderer::GetWindow()->GetGLFWWindow(), &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	ImGuiRenderer* ImGuiRenderer::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<ImGuiRenderer>();
		}

		return SingletonInstance.get();
	}
}