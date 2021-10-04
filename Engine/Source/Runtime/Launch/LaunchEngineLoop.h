namespace Durna
{
	class Application;

	class Engineloop
	{
	public:
		Engineloop()
			: MaxTimeDilation(1 / 60.0f)
			, LastTickTime(-1.0f)
		{
		}

		bool Init();
		void Shutdown();

		void MainLoop();

		void Tick(float DeltaTime);

		private:

		Application* App;

		float MaxTimeDilation;
		double LastTickTime;
	};
}