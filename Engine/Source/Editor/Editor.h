#pragma once

namespace Durna
{
#if WITH_EDITOR

	class Editor
	{
	public:
		Editor();
		~Editor();

		void Init();
		void Tick(float DeltaTime);

		static Editor* Get();

	protected:

	private:
		static std::unique_ptr<Editor> SingletonInstance;
	};


#endif
}

