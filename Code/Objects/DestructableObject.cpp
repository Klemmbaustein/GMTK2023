#include "DestructibleObject.h"
#include <Objects/Components/CollisionComponent.h>
#include <Engine/Log.h>
#include <World/Stats.h>
#include "PlayerObject.h"
#include <Engine/EngineRandom.h>

Sound::SoundBuffer* DestructibleObject::SuckUpSound = nullptr;

void DestructibleObject::Begin()
{
	Properties.push_back(Objects::Property("Model name", Type::E_STRING, &ModelName));
	Properties.push_back(Objects::Property("Destroyed model name", Type::E_STRING, &BrokenModelName));
	Properties.push_back(Objects::Property("Required size", Type::E_FLOAT, &RequiredSize));
	Properties.push_back(Objects::Property("Reward", Type::E_FLOAT, &Reward));
	if (!SuckUpSound)
	{
		SuckUpSound = Sound::LoadSound("SuckUp");
	}
}

void DestructibleObject::OnPropertySet()
{
	if (ObjectMesh)
	{
		Detach(Collider);
		Detach(ObjectMesh);
	}

	ModelGenerator::ModelData m;
	m.LoadModelFromFile(ModelName);

	Collider = new CollisionComponent();
	Attach(Collider);
	Collider->Init(m.GetMergedVertices(), m.GetMergedIndices());

	ObjectMesh = new MeshComponent();
	Attach(ObjectMesh);
	ObjectMesh->Load(m);
	if (Reward == 0)
	{
		Reward = RequiredSize;
	}

}

void DestructibleObject::Tick()
{
#if !EDITOR
	if (!ObjectMesh)
	{
		return;
	}

	if (IsPulled || IsSuckedUp)
	{
		float Height = 20;
		if (!IsSuckedUp)
		{
			Height = 0;
		}
		PulledHeight = std::lerp(PulledHeight, Height, std::max(Performance::DeltaTime, 0.0f));
		if (IsSuckedUp)
		{
			ObjectMesh->RelativeTransform.Scale = Vector3::Clamp(ObjectMesh->RelativeTransform.Scale - Performance::DeltaTime * 3, 0, 1);
			if (ObjectMesh->RelativeTransform.Scale == 0)
			{
				Detach(ObjectMesh);
				ObjectMesh = nullptr;
				return;
			}
		}
	}
	else
	{
		PulledHeight = std::lerp(PulledHeight, 0, std::max(Performance::DeltaTime * 2, 0.0f));
	}
	ObjectMesh->RelativeTransform.Location.Y = PulledHeight;
	IsPulled = false;
#endif
}

void DestructibleObject::SuckUp()
{
	Sound::PlaySound2D(SuckUpSound, Random::GetRandomFloat(0.8, 1.2), 0.25);
	IsSuckedUp = true;
	if (Collider)
	{
		Detach(Collider);
	}
	if (!BrokenModelName.empty())
	{
		auto DestroyedMesh = new MeshComponent();
		Attach(DestroyedMesh);
		DestroyedMesh->Load(BrokenModelName);
	}
}
