#pragma once
#include <Objects/WorldObject.h>
#include <GENERATED/GENERATED_PlayerObject.h>
#include <Objects/Components/CameraComponent.h>
#include <Objects/Components/MeshComponent.h>
#include <UI/GameUI.h>

class PlayerObject : public WorldObject
{
	MeshComponent* PlayerMesh = nullptr;
	MeshComponent* AttractBeam = nullptr;
	CameraComponent* PlayerCamera = nullptr;

public:
	GameUI* PlayerGameUI = nullptr;
	static PlayerObject* GetPlayer();

	Vector3 CameraOffset;
	Vector3 Velocity;
	const float Acceleration = 200;
	const float Deceleration = 200;
	const float MaxSpeed = 100;
	float Size = 1;
	float DisplayedSize = Size;

	size_t TotalNumObjects = 0;
	float Progress = 0;

	void TryMove(Vector3 Movement);

	PLAYEROBJECT_GENERATED("");

	void Begin() override;
	void Tick() override;
	void Destroy() override;
};