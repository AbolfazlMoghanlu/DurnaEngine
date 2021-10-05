#pragma once

struct GLFWwindow;

namespace Durna
{
	class Window
	{
	public:
		Window(std::string InTitle, int InWidth, int InHeight)
			: Title		(InTitle)
			, Width		(InWidth)
			, Height	(InHeight)
			, window	(nullptr)
		{
		}

		~Window()
		{
			//delete window;
		}

		void Init();

		void Tick(float DeltaTime);

		// TODO: move to input class
		void ProcessInput();

		bool IsClosing() const;

	private:

		GLFWwindow* window;

		std::string Title;

		int Width;
		int Height;
	};
}



