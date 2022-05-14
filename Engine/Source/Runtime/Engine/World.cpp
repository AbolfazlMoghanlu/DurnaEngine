#include "DurnaPCH.h"
#include "World.h"

#include "Actor.h"

namespace Durna
{
	World::World()
	{ }

	World::~World()
	{ }

	void World::Tick(float DeltaTime)
	{
		for (LinkedListIterator It(Actors); It; ++It)
		{
			if (It)
			{
				if (!It->IsMarkDestroy())
				{
					It->Tick(DeltaTime);
				}

				else
				{
					delete *It;
					It.Remove();
				}
			}

			else
			{
				It.Remove();
			}
		}

	}

	void World::AddActor(Actor* InActor)
	{
		Actors.AddFirst(InActor);
	}

	LinkedList<Actor> World::Actors;
}