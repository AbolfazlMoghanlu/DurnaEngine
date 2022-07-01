#include "DurnaPCH.h"
#include "World.h"

#include "Actor.h"
#include "Runtime/Engine/GameFramwork/DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/GameFramwork/SkyLightActor.h"

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

	DirectionalLightActor* World::GetDirectionalLight() const
	{
		return DirectionalLightSource;
	}

	SkyLightActor* World::GetSkyLight() const
	{
		return SkyLightSource;
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

		SkyLightSource = new SkyLightActor();
		SkyLightSource->SetActorLocation(Vector3f(0.0f, 0.0f, 0.2f));
		AddActor(SkyLightSource);

#if WITH_EDITOR
		SkyLightSource->SetActorLabel("Sky Light");
#endif
	}
}