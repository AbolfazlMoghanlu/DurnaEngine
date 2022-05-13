#include "DurnaPCH.h"
#include "ImGuiLayer.h"

#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Durna
{
	std::unique_ptr<ImGuiLayer> ImGuiLayer::SingletonInstance = nullptr;

	ImGuiLayer::ImGuiLayer()
	{ }

	ImGuiLayer::~ImGuiLayer()
	{ }

	void ImGuiLayer::Init()
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
	}

	void ImGuiLayer::Tick(float DeltaTime)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

 		//bool show_demo_window = true;
 		//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("Demo window");
		ImGui::SliderFloat("Sky light Intensity ", &SkyLightIntensity, 0.0f, 1.0f, NULL, ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
		ImGui::End();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Rendering
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

	ImGuiLayer* ImGuiLayer::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<ImGuiLayer>();
		}

		return SingletonInstance.get();
	}
}