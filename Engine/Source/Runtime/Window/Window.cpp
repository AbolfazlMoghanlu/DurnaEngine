#include "DurnaPCH.h"
#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

LOG_DEFINE_CATEGORY(LogWindow, "Window");

namespace Durna
{
	Window::Window(std::string InTitle, int InWidth, int InHeight)
		: Title(InTitle)
		, Width(InWidth)
		, Height(InHeight)
		, window(nullptr)
	{
		Init();
	}

	Window::~Window()
	{
		LOG(LogWindow, Info, "Destroying \"%s\" window.", Title.c_str());
		glfwDestroyWindow(window);
	}

	void Window::Init()
	{
		LOG(LogWindow, Info, "Initializing \"%s\" window in %i * %i.", Title.c_str(), Width, Height);
		window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(window);
		
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* InWindow, int InWidth, int InHeight)
			{
				LOG(LogWindow, Info, "Changed window size to %i * %i.",  InWidth, InHeight);
				glViewport(0, 0, InWidth, InHeight);
			});
	}

	

	void Window::Tick(float DeltaTime)
	{
		glfwSwapBuffers(window);
		ProcessInput();
	}

	void Window::ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}

	bool Window::IsClosing() const
	{
		if (window)
		{
			return glfwWindowShouldClose(window);
		}
		return true;
	}

}


