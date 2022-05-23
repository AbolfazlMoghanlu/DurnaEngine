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

	protected:
		std::unique_ptr<ViewportGuiLayer> ViewportLayer;

	private:
		static std::unique_ptr<Viewport> SingletonInstance;
	};
}

#endif