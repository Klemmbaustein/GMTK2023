#pragma once
#include <Objects/WorldObject.h>
#include <GENERATED/GENERATED_GameExit.h>

class MeshComponent;

class GameExit : public WorldObject
{
public:
	MeshComponent* ExitMesh = nullptr;
	GAMEEXIT_GENERATED("");
	void Begin() override;
	void Tick() override;
};