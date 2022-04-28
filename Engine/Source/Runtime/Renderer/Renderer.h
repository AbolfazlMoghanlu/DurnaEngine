#pragma once

namespace Durna
{
	class Window;

	class Shader;

	class PrimitiveComponent;

	class Image;

	class Texture;

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

		 static float Time;

		 static Image* img1;
		 static Image* img2;

		 static Texture* Texture1;
		 static Texture* Texture2;
	};
}



