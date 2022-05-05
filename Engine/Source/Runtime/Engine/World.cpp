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
		LinkedListNode<Actor>* PrevNode = nullptr;
		LinkedListNode<Actor>* Node = Actors.Root;

		while (Node)
		{
			bool bDestroyNode = false;

			Actor* TargetActor = **Node;
			if (TargetActor)
			{
				if (!TargetActor->IsMarkDestroy())
				{
					TargetActor->Tick(DeltaTime);
				}

				else
				{
					delete TargetActor;
					TargetActor = nullptr;
					bDestroyNode = true;
				}
			}

			else
			{
				bDestroyNode = true;
			}

			if (bDestroyNode)
			{
				if (PrevNode)
				{
					PrevNode->SetNextNode(Node->Next());
					delete Node;
					Node = PrevNode->Next();
				}
				else
				{
					Actors.Root = Node->Next();
					delete Node;
					Node = Actors.Root;
				}
			}
			else
			{
				PrevNode = Node;
				Node = Node->Next();
			}

		}
	}

	void World::AddActor(Actor* InActor)
	{
		Actors.Add(InActor);
	}

	LinkedList<Actor> World::Actors;
}