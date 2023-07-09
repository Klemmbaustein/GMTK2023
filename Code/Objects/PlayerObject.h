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


	Sound::SoundBuffer* ImpactSound = Sound::LoadSound("Impact");

	const float Acceleration = 400;
	const float Deceleration = 400;
	const float MaxSpeed = 50;
	size_t TotalNumObjects = 0;
	bool HasFinishedLevel = false;
	Application::Timer FadeoutTimer;
	bool HasEnded = false;
public:
	GameUI* PlayerGameUI = nullptr;
	Application::Timer LevelTimer;
	static PlayerObject* GetPlayer();
	static int16_t CurrentLevel;
	void FinishLevel();

	static size_t Score;

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