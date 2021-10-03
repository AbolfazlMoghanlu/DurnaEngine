namespace Durna
{
	class Engineloop
	{
	public:
		Engineloop()
			: MaxTimeDilation(0.01667f)
			, LastTickTime(-1.0f)
		{
		}

		bool Init()
		{
			// todo: make application class and initiate it

			return true;
		}

		void StartLoop();

		void Tick(float DeltaTime);

		void Shutdown()
		{

		}

		private:

		float MaxTimeDilation;
		double LastTickTime;
	};
}