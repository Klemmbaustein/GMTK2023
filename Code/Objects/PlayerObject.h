#pragma once
#include <Objects/WorldObject.h>
#include <GENERATED/GENERATED_PlayerObject.h>
#include <Objects/Components/CameraComponent.h>
#include <Objects/Components/MeshComponent.h>
#include <UI/GameUI.h>
#include <Sound/Sound.h>
#include <Engine/Application.h>

class PlayerObject : public WorldObject
{
	MeshComponent* PlayerMesh = nullptr;
	MeshComponent* AttractBeam = nullptr;
	CameraComponent* PlayerCamera = nullptr;

	Application::Timer ImpactTimer;

	Sound::SoundBuffer* ImpactSound = Sound::LoadSound("Impact");

	const float Acceleration = 200;
	const float Deceleration = 200;
	const float MaxSpeed = 100;
	size_t TotalNumObjects = 0;
	bool HasFinishedLevel = false;
	Application::Timer FadeoutTimer;

public:
	GameUI* PlayerGameUI = nullptr;
	static PlayerObject* GetPlayer();

	void FinishLevel();


	Vector3 CameraOffset;
	Vector3 Velocity;
	float Size = 1;
	float DisplayedSize = Size;

	float Progress = 0;

	void TryMove(Vector3 Movement);

	PLAYEROBJECT_GENERATED("");

	void Begin() override;
	void Tick() override;
	void Destroy() override;
};