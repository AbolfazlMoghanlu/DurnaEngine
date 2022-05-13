#pragma once

#include "Runtime/Containers/List.h"

namespace Durna
{
	class Actor;

	class World
	{
	public:
		World();
		~World();

		static void Tick(float DeltaTime);
		static void AddActor(Actor* InActor);

	private:
		static LinkedList<Actor> Actors;

		friend class WorldOutlinerGuiLayer;
	};

}

