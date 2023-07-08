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
	GetTransform().Location.Y = 30;
	GetTransform().Rotation.Y += Performance::DeltaTime * 180;
	if (PlayerObject::GetPlayer()->Progress == 1)
	{
		GetTransform().Scale = Vector3::Clamp(GetTransform().Scale + Performance::DeltaTime * 10, 0, 10);

		Vector3 PlayerPos2D = PlayerObject::GetPlayer()->GetTransform().Location;
		Vector3 Pos2D = GetTransform().Location;
		PlayerPos2D.Y = 0;
		Pos2D.Y = 0;

		if (Vector3::Distance(PlayerPos2D, Pos2D) <= 5)
		{
			Application::Quit();
		}
	}
	else
	{
		GetTransform().Scale = 0;
	}
#endif
}
