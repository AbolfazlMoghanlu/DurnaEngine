#pragma once

#include "Runtime/Containers/List.h"

namespace Durna
{
	class Actor;
	class DirectionalLightActor;

	class World
	{
	public:
		World();
		~World();

		static World* Get();

		void Tick(float DeltaTime);
		void AddActor(Actor* InActor);

		DirectionalLightActor* GetDirectionalLight();

	private:
		static std::unique_ptr<World> MainWorld;

		void InitPrimitiveActors();

		LinkedList<Actor> Actors;

		DirectionalLightActor* DirectionalLightSource;

		friend class WorldOutliner;
		friend class WorldOutlinerGuiLayer;
	};
}

