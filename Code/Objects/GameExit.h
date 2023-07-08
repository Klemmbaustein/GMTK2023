#pragma once
#include <Objects/WorldObject.h>
#include <GENERATED/GENERATED_GameExit.h>
#include <Sound/Sound.h>

class MeshComponent;

class GameExit : public WorldObject
{
public:
#if !EDITOR
	Sound::SoundBuffer* BeginSound = Sound::LoadSound("EndAppear");
#endif
	MeshComponent* ExitMesh = nullptr;
	GAMEEXIT_GENERATED("");
	void Begin() override;
	void Tick() override;
	void Destroy() override;
};