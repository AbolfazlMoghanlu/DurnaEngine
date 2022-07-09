#pragma once

namespace Durna
{
	class PrimitiveComponent;
	class PointLightComponent;


	// TODO: make queue class
	class RenderQueue
	{
	public:
		void Clear(uint32 SlackSize = 0);
		void AddPrimitive(PrimitiveComponent* Pr);

		void Resize(uint32 Size);
		void Reserve(uint32 Size);
		

	protected:
		std::vector<PrimitiveComponent*> Queue;
		
	private:
		friend class Renderer;
		friend class RenderCommands;
	};

	class PointLightRenderQueue
	{
	public:
		void Clear(uint32 SlackSize = 0);
		void AddPrimitive(PointLightComponent* InPointLightComponent);

		void Resize(uint32 Size);
		void Reserve(uint32 Size);


	protected:
		std::vector<PointLightComponent*> Queue;

	private:
		friend class Renderer;
		friend class RenderCommands;
	};
}