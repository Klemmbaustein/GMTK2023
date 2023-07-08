#pragma once
#include <Objects/WorldObject.h>
#include <GENERATED/GENERATED_DestructibleObject.h>
#include <Objects/Components/MeshComponent.h>
#include <Objects/Components/CollisionComponent.h>
#include <Sound/Sound.h>

class DestructibleObject : public WorldObject
{
public:
	DESTRUCTIBLEOBJECT_GENERATED("Destr");

	static Sound::SoundBuffer* SuckUpSound;

	float PulledHeight = 0;
	bool IsPulled = false;
	float RequiredSize = 1;
	float Reward = 0;
	CollisionComponent* Collider = nullptr;
	MeshComponent* ObjectMesh = nullptr;
	std::string ModelName = "Cube";
	std::string BrokenModelName = "";
	void Begin() override;
	void OnPropertySet() override;
	void Tick() override;

	bool IsSuckedUp = false;
	void SuckUp();
};