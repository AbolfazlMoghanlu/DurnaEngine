#include "DurnaPCH.h"
#include "Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"

#include "Runtime/Math/Math.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


LOG_DEFINE_CATEGORY(LogWindow, "Window");

namespace Durna
{
	float Window::MouseLastX = 0.0f;
	float Window::MouseLastY = 0.0f;

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

		MouseLastX = (float)Width / 2;
		MouseLastY = (float)Height / 2;

		glfwSetScrollCallback(window, OnScroll);
		glfwSetCursorPosCallback(window, OnMouseMove);

		// TODO: Move somewhere more suitable
		CameraManager::SetActiveCamera(new Camera);
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	

	void Window::Tick(float DeltaTime)
	{
		glfwSwapBuffers(window);
		ProcessInput(DeltaTime);
	}

	void Window::ProcessInput(float DeltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (glfwGetKey(window, GLFW_KEY_D) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraManager::MoveRight(DeltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_A) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraManager::MoveRight(-DeltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_W) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraManager::MoveForward(DeltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_S) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraManager::MoveForward(-DeltaTime);
		}
	}

	void Window::OnScroll(GLFWwindow* InWindow, double XOffset, double YOffset)
	{
		float ClampedFOV = Math::Clamp<float>(CameraManager::GetActiveCamera()->GetFOV() + (float)YOffset * 5.0f, 1.0f, 90.0f);
		CameraManager::GetActiveCamera()->SetFOV(ClampedFOV);
	}

	void Window::OnMouseMove(GLFWwindow* InWindow, double XPos, double YPos)
	{
		float XOffset = (float)XPos - MouseLastX;
		float YOffset = (float)YPos - MouseLastY;

		MouseLastX = (float)XPos;
		MouseLastY = (float)YPos;

		if (glfwGetMouseButton(InWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			glfwSetInputMode(InWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			CameraManager::AddActiveCameraWorldRotation(Rotatorf(-YOffset, XOffset, 0.0f));
		}
		else
		{
			glfwSetInputMode(InWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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


