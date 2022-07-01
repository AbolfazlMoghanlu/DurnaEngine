#pragma once

#include "Runtime/Containers/List.h"

namespace Durna
{
	class Actor;
	class DirectionalLightActor;
	class SkyLightActor;
	class SkySphereActor;

	class World
	{
	public:
		World();
		~World();

		static World* Get();

		void Tick(float DeltaTime);
		void AddActor(Actor* InActor);

		DirectionalLightActor* GetDirectionalLight() const;
		SkyLightActor* GetSkyLight() const;
		SkySphereActor* GetSkySphere() const;

	private:
		static std::unique_ptr<World> MainWorld;

		void InitPrimitiveActors();

		LinkedList<Actor> Actors;

		DirectionalLightActor* DirectionalLightSource;
		SkyLightActor* SkyLightSource;
		SkySphereActor* SkySphereSource;

		friend class WorldOutliner;
		friend class WorldOutlinerGuiLayer;
	};
}

