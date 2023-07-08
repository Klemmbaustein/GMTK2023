#include "GameExit.h"
#include <Objects/PlayerObject.h>
#include <Engine/Application.h>
#include <Engine/Log.h>

void GameExit::Begin()
{
	ExitMesh = new MeshComponent();
	Attach(ExitMesh);
	ExitMesh->Load("AttractBeam");
}

void GameExit::Tick()
{
#if !EDITOR
	if (!PlayerObject::GetPlayer())
	{
		return;
	}

	GetTransform().Location.Y = 30;
	GetTransform().Rotation.Y += Performance::DeltaTime * 180;
	if (PlayerObject::GetPlayer()->Progress == 1)
	{
		if (GetTransform().Scale == 0)
		{
			Sound::PlaySound2D(BeginSound, 1, 0.5);
		}
		GetTransform().Scale = Vector3::Clamp(GetTransform().Scale + Performance::DeltaTime * 10, 0, 10);

		Vector3 PlayerPos2D = PlayerObject::GetPlayer()->GetTransform().Location;
		Vector3 Pos2D = GetTransform().Location;
		PlayerPos2D.Y = 0;
		Pos2D.Y = 0;

		if (Vector3::Distance(PlayerPos2D, Pos2D) <= 10)
		{
			PlayerObject::GetPlayer()->FinishLevel();
		}
	}
	else
	{
		GetTransform().Scale = 0;
	}
#endif
}

void GameExit::Destroy()
{
#if !EDITOR
	delete BeginSound;
#endif
}
