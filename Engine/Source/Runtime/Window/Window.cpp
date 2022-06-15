#include "DurnaPCH.h"
#include "Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

#include "Runtime/Core/Application.h"
#include "Runtime/Renderer/Renderer.h"

#include "Runtime/Math/Math.h"

#include "Runtime/Renderer/RenderCommands.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

#include "Editor/Editor.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


LOG_DEFINE_CATEGORY(LogWindow, "Window");

namespace Durna
{
	Window::Window(const std::string& InTitle, int InWidth, int InHeight)
		: Title(InTitle)
		, GlfwWindow(nullptr)
	{ 
		InitalizeWindow(InTitle, InWidth, InHeight);
		BindCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(GlfwWindow);
	}

	std::shared_ptr<Window> Window::Create(const std::string& InTitle, int32 Width, int32 Height)
	{
		return std::make_shared<Window>(InTitle, Width, Height);
	}

	void Window::InitalizeWindow(const std::string& InTitle, int32 InWidth, int32 InHeight)
	{
		LOG(LogWindow, Info, "Initializing \"%s\" GlfwWindow in %i * %i.", Title.c_str(), InWidth, InHeight);

		GlfwWindow = glfwCreateWindow(InWidth, InHeight, Title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(GlfwWindow, (void*) this);

		glfwMakeContextCurrent(GlfwWindow);
		glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		MouseLastX = (float)InWidth / 2;
		MouseLastY = (float)InHeight / 2;
	}

	void Window::Tick(float DeltaTime)
	{
		ProcessInput(DeltaTime);

		if (IsClosing())
		{
			Application::Get()->RequestExit();
		}
	}

	void Window::BindCallbacks()
	{
		glfwSetFramebufferSizeCallback(GlfwWindow, s_OnFrameBufferSizeChanged);
		glfwSetScrollCallback(GlfwWindow, s_OnScroll);
		glfwSetCursorPosCallback(GlfwWindow, s_OnMouseMove);
	}

	void Window::s_OnFrameBufferSizeChanged(GLFWwindow* InWindow, int InWidth, int InHeight)
	{
		if (Window* window = (Window*)glfwGetWindowUserPointer(InWindow))
		{
			window->OnFrameBufferSizeChanged(InWidth, InHeight);
		}
	}

	void Window::s_OnScroll(GLFWwindow* InWindow, double XOffset, double YOffset)
	{
		if (Window* window = (Window*)glfwGetWindowUserPointer(InWindow))
		{
			window->OnScroll(XOffset, YOffset);
		}
	}

	void Window::s_OnMouseMove(GLFWwindow* InWindow, double XPos, double YPos)
	{
		if (Window* window = (Window*)glfwGetWindowUserPointer(InWindow))
		{
			window->OnMouseMove(XPos, YPos);
		}
	}

	void Window::OnFrameBufferSizeChanged(int InWidth, int InHeight)
	{
		LOG(LogWindow, Info, "Changed GlfwWindow size to %i * %i.", InWidth, InHeight);
	}

	void Window::OnScroll(double XOffset, double YOffset)
	{
		float ClampedFOV = Math::Clamp<float>(CameraManager::Get()->GetActiveCamera()->GetFOV() + (float)YOffset * 5.0f, 1.0f, 90.0f);
		CameraManager::Get()->GetActiveCamera()->SetFOV(ClampedFOV);
	}

	void Window::OnMouseMove(double XPos, double YPos)
	{
		if (!GlfwWindow)
		{
			return;
		}
		
		float XOffset = (float)XPos - MouseLastX;
		float YOffset = (float)YPos - MouseLastY;

		MouseLastX = (float)XPos;
		MouseLastY = (float)YPos;		
		
		if (glfwGetMouseButton(GlfwWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			CameraComponent* ActiveCamera = CameraManager::Get()->GetActiveCamera();
			if (ActiveCamera)
			{
				ActiveCamera->SetRelativeRotation(
					Rotatorf(-YOffset * 0.2f, XOffset * 0.2f, 0.0f) + ActiveCamera->GetWorldRotation());
			}
		}
		else
		{
			glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::ProcessInput(float DeltaTime)
	{
		if (glfwGetKey(GlfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(GlfwWindow, true);
		}

		if (glfwGetKey(GlfwWindow, GLFW_KEY_D) && glfwGetMouseButton(GlfwWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraComponent* ActiveCamera = CameraManager::Get()->GetActiveCamera();
			if (ActiveCamera)
			{
				Vector3f CameraLcoation = ActiveCamera->GetWorldLocation();
				Rotatorf CameraRotation = ActiveCamera->GetWorldRotation();
				Vector3f MoveOffset = CameraRotation.GetRightVector() * 1.0f * DeltaTime;

#if WITH_EDITOR 
				MoveOffset *= Editor::Get()->CameraMoveSpeed;
#endif

				ActiveCamera->SetRelativeLocation(CameraLcoation + MoveOffset);
			}
		}

		if (glfwGetKey(GlfwWindow, GLFW_KEY_A) && glfwGetMouseButton(GlfwWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraComponent* ActiveCamera = CameraManager::Get()->GetActiveCamera();
			if (ActiveCamera)
			{
				Vector3f CameraLcoation = ActiveCamera->GetWorldLocation();
				Rotatorf CameraRotation = ActiveCamera->GetWorldRotation();
				Vector3f MoveOffset = CameraRotation.GetRightVector() * -1.0f * DeltaTime;

#if WITH_EDITOR 
				MoveOffset *= Editor::Get()->CameraMoveSpeed;
#endif

				ActiveCamera->SetRelativeLocation(CameraLcoation + MoveOffset);
			}
		}

		if (glfwGetKey(GlfwWindow, GLFW_KEY_W) && glfwGetMouseButton(GlfwWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraComponent* ActiveCamera = CameraManager::Get()->GetActiveCamera();
			if (ActiveCamera)
			{
				Vector3f CameraLcoation = ActiveCamera->GetWorldLocation();
				Rotatorf CameraRotation = ActiveCamera->GetWorldRotation();
				Vector3f MoveOffset = CameraRotation.GetForwardVector() * 1.0f * DeltaTime;

#if WITH_EDITOR 
				MoveOffset *= Editor::Get()->CameraMoveSpeed;
#endif

				ActiveCamera->SetRelativeLocation(CameraLcoation + MoveOffset);
			}
		}

		if (glfwGetKey(GlfwWindow, GLFW_KEY_S) && glfwGetMouseButton(GlfwWindow, GLFW_MOUSE_BUTTON_RIGHT))
		{
			CameraComponent* ActiveCamera = CameraManager::Get()->GetActiveCamera();
			if (ActiveCamera)
			{
				Vector3f CameraLcoation = ActiveCamera->GetWorldLocation();
				Rotatorf CameraRotation = ActiveCamera->GetWorldRotation();
				Vector3f MoveOffset = CameraRotation.GetForwardVector() * -1.0f * DeltaTime;

#if WITH_EDITOR 
				MoveOffset *= Editor::Get()->CameraMoveSpeed;
#endif

				ActiveCamera->SetRelativeLocation(CameraLcoation + MoveOffset);
			}
		}
	}

	bool Window::IsClosing() const
	{
		if (GlfwWindow)
		{
			return glfwWindowShouldClose(GlfwWindow);
		}
		return true;
	}

	GLFWwindow* Window::GetGLFWWindow() const
	{
		return GlfwWindow;
	}


	void Window::SetWindowSize(const IntPoint& Size)
	{
		glfwSetWindowSize(GlfwWindow, Size.X, Size.Y);
	}

	void Window::MaximaizeWindow()
	{
		glfwMaximizeWindow(GlfwWindow);
	}

	void Window::RestoreWindow()
	{
		glfwRestoreWindow(GlfwWindow);
	}

	IntPoint Window::GetWindowSize()
	{
		int SizeX = 0;
		int SizeY = 0;
		glfwGetWindowSize(GlfwWindow, &SizeX, &SizeY);
		return IntPoint(SizeX, SizeY);
	}

	void Window::SetWindowResolution(const IntPoint& Res)
	{
		Resolution = Res;
	}

	void Window::SetConstraintedResolution(const IntPoint& Res)
	{
		ConstraintedResolution = Res;
	}

	void Window::SetWindowMode(EWindowMode InWindowMode)
	{
		WindowMode = InWindowMode;
	}

	void Window::UpdateWindowSettings()
	{
		CameraManager::Get()->GetActiveCamera()->SetPerspectiveWidth((float)Resolution.X);
		CameraManager::Get()->GetActiveCamera()->SetPerspectiveHeight((float)Resolution.Y);

		if (WindowMode == EWindowMode::FullScreen)
		{
			// TODO: move GlfwWindow functions from render command to this class
			MaximaizeWindow();
			IntPoint WindowSize = GetWindowSize();
			float AspectRatio = (float)Resolution.X / (float)Resolution.Y;
			if (AspectRatio >= WindowSize.X / (float)WindowSize.Y)
			{
				ConstraintedResolution = IntPoint((int32)(WindowSize.X, WindowSize.X / AspectRatio));
				ConstraintedOffset = IntPoint(0, (WindowSize.Y - ConstraintedResolution.Y) / 2);
			}
			else
			{
				ConstraintedResolution = IntPoint((int32)(WindowSize.Y * AspectRatio, WindowSize.Y));
				ConstraintedOffset = IntPoint((WindowSize.X - ConstraintedResolution.X) / 2, 0);
			}
		}

		else if (WindowMode == EWindowMode::Windowed)
		{
			RestoreWindow();
			SetWindowSize(Resolution);
			ConstraintedResolution = Resolution;
			ConstraintedOffset = IntPoint::Zero;
		}
		
		else if (WindowMode == EWindowMode::BorderlessFullscreen)
		{
			MaximaizeWindow();
			IntPoint WindowSize = GetWindowSize();
			ConstraintedResolution = WindowSize;
			ConstraintedOffset = IntPoint::Zero;
		}
		
		Renderer::OnResolutionChanged(Resolution);
	}
}