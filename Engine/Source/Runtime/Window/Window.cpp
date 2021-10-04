#include "DurnaPCH.h"
#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Durna
{
	void Window::Init()
	{
		window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(window);
	}
}


