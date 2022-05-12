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

	private:

		static void OnScroll(GLFWwindow* InWindow, double XOffset, double YOffset);
		static void OnMouseMove(GLFWwindow* InWindow, double XPos, double YPos);

		GLFWwindow* window;
		std::string Title;

		int Width;
		int Height;

		static float MouseLastX;
		static float MouseLastY;
	};
}



