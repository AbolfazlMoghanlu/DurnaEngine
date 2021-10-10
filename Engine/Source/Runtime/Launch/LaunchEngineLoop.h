
LOG_DECLARE_CATEGORY(LogApp);

namespace Durna
{
	class Application;

	class Engineloop
	{
	public:
		Engineloop();

		~Engineloop();

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