#pragma once

#if WITH_EDITOR

namespace Durna
{
	class ContentBrowserGuiLayer;

	class ContentBrowser
	{
	public:
		ContentBrowser();
		virtual ~ContentBrowser();

		void Init();
		void Tick(float DeltaTime);

		static ContentBrowser* Get();

	
	protected:
		std::unique_ptr<ContentBrowserGuiLayer> OutputLogLayer;

	private:

		static std::unique_ptr<ContentBrowser> SingletonInstance;
	
		friend class ContentBrowserGuiLayer;
	};
}

#endif