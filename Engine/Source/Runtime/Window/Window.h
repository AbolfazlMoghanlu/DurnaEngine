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
		{
		}

		void Init();

	private:

		GLFWwindow* window = nullptr;

		std::string Title;

		int Width;
		int Height;
	};
}



