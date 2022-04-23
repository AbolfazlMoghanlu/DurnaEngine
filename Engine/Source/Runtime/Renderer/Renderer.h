#pragma once

namespace Durna
{
	class Window;

	class Shader;

	class PrimitiveComponent;

	class Image;

	class Renderer
	{
	public:
		Renderer();

		static void Init();

		static void Tick(float DeltaTime);

		static void Shutdown();

		static Window* MainWindow;

		// TODO: Move to static mesh class
		 static Shader* shader;
		// TODO: Remove
		 static PrimitiveComponent* pr;

		 static Image* img;
	};
}



