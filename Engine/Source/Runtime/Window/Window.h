#pragma once

struct GLFWwindow;

namespace Durna
{
	class Window
	{
	public:
		Window(std::string InTitle, int InWidth, int InHeight);

		virtual ~Window();

		void Init();

		void Tick(float DeltaTime);

		// TODO: move to input class
		void ProcessInput(float DeltaTime);

		bool IsClosing() const;

		GLFWwindow* GetGLFWWindow() const;

		EWindowMode WindowMode = EWindowMode::FullScreen;
		IntPoint Resolution = IntPoint(800, 600);
		IntPoint ConstraintedResolution = IntPoint(800, 600);
		IntPoint ConstraintedOffset = IntPoint(0, 0);

		void UpdateWindowSettings();

	private:

		static void OnScroll(GLFWwindow* InWindow, double XOffset, double YOffset);
		static void OnMouseMove(GLFWwindow* InWindow, double XPos, double YPos);

		GLFWwindow* window;
		std::string Title;

		int32 Width;
		int32 Height;

		static float MouseLastX;
		static float MouseLastY;
	};
}