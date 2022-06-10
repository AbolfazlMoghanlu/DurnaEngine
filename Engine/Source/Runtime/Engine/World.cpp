#include "DurnaPCH.h"
#include "World.h"

#include "Actor.h"
#include "Runtime/Engine/GameFramwork/DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"

// TODO: Remove
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Math/Math.h"

namespace Durna
{
	std::unique_ptr<World> World::MainWorld;

	World::World()
	{ 
		InitPrimitiveActors();
	}

	World::~World()
	{ }

	World* World::Get()
	{
		if (!MainWorld)
		{
			MainWorld = std::make_unique<World>();
		}

		return MainWorld.get();
	}

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

	DirectionalLightActor* World::GetDirectionalLight()
	{
		return DirectionalLightSource;
	}

	void World::InitPrimitiveActors()
	{
		DirectionalLightSource = new DirectionalLightActor();
		DirectionalLightSource->GetLightComponent()->SetCastShadow(true);
		DirectionalLightSource->SetActorLocation(Vector3f(0.5f, 0, 1.0f));
		DirectionalLightSource->SetActorRotation(Rotatorf(270.0f, 180.0f, 0.0f));
		AddActor(DirectionalLightSource);

#if WITH_EDITOR
		DirectionalLightSource->SetActorLabel("Directional Light");
#endif
	}
}