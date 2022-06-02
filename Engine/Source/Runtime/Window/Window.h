#pragma once

struct GLFWwindow;

namespace Durna
{
	class Window
	{
	public:
		Window(const std::string& InTitle, int InWidth, int InHeight);
		virtual ~Window();
		static std::shared_ptr<Window> Create(const std::string& InTitle, int32 Width, int32 Height);

		GLFWwindow* GetGLFWWindow() const;

		void Tick(float DeltaTime);

		// TODO: move to input class
		void ProcessInput(float DeltaTime);

		bool IsClosing() const;

		void UpdateWindowSettings();

	protected:

		EWindowMode WindowMode = EWindowMode::FullScreen;
		IntPoint Resolution = IntPoint(800, 600);
		IntPoint ConstraintedResolution = IntPoint(800, 600);
		IntPoint ConstraintedOffset = IntPoint(0, 0);

		GLFWwindow* GlfwWindow;
		std::string Title;

		void OnFrameBufferSizeChanged(int InWidth, int InHeight);
		void OnScroll(double XOffset, double YOffset);
		void OnMouseMove(double XPos, double YPos);
	
	private:

		void InitalizeWindow(const std::string& InTitle, float InWidth, float InHeight);
		void BindCallbacks();
		
		static void s_OnFrameBufferSizeChanged(GLFWwindow* InWindow, int InWidth, int InHeight);
		static void s_OnScroll(GLFWwindow* InWindow, double XOffset, double YOffset);
		static void s_OnMouseMove(GLFWwindow* InWindow, double XPos, double YPos);
		
		float MouseLastX = 0.0f;
		float MouseLastY = 0.0f;

		friend class RenderCommands;
		friend class Renderer;
	};
}