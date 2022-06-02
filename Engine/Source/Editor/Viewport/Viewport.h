#pragma once

#if WITH_EDITOR

namespace Durna
{
	class ViewportGuiLayer;

	class Viewport
	{
	public:
		Viewport();
		~Viewport();

		void Init();
		void Tick(float DeltaTime);

		static Viewport* Get();
		void OnViewportSizeChanged(const IntPoint& OldSize, const IntPoint& NewSize);

	protected:
		std::unique_ptr<ViewportGuiLayer> ViewportLayer;

		bool bCustomResolution = false;
		IntPoint Resolution = IntPoint(800, 600);
		IntPoint PreviousFrameResolution = IntPoint(800, 600);

	private:
		static std::unique_ptr<Viewport> SingletonInstance;

		void UpdateViewport();

		friend class ViewportGuiLayer;
	};
}

#endif