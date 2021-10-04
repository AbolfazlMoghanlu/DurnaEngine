#include "DurnaPCH.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Window/Window.h"

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

	void Renderer::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		MainWindow = new Window("DurnaEngine", 800, 600);
		MainWindow->Init();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	void Renderer::Shutdown()
	{
		delete MainWindow;
	}

}