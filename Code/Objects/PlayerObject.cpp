#include "PlayerObject.h"
#include <Engine/Input.h>
#include <World/Stats.h>
#include <Objects/DestructibleObject.h>
#include <Engine/Log.h>
#include <Math/Collision/Collision.h>

std::vector<WorldObject*> AllDestructibles;
PlayerObject* Player = nullptr;

PlayerObject* PlayerObject::GetPlayer()
{
	return Player;
}

void PlayerObject::TryMove(Vector3 Movement)
{
	Collision::HitResponse Hit = Collision::LineTrace(GetTransform().Location, GetTransform().Location + Movement);
	if (!Hit.Hit)
	{
		GetTransform().Location += Movement;
	}
	else
	{
		Velocity = glm::reflect((glm::vec3)Velocity, (glm::vec3)Hit.Normal) / 2;
	}
}

void PlayerObject::Begin()
{
	PlayerCamera = new CameraComponent();
	Attach(PlayerCamera);
	PlayerCamera->Use();
	PlayerCamera->RelativeTransform = Transform(Vector3(0, 50, 0), Vector3(-85, 0, 0), 1);

	PlayerMesh = new MeshComponent();
	Attach(PlayerMesh);
	PlayerMesh->Load("UFO");
	Player = this;


	PlayerGameUI = UICanvas::CreateNewCanvas<GameUI>();
}

void PlayerObject::Tick()
{
#if EDITOR
	return;
#endif

	if (AllDestructibles.empty())
	{
		AllDestructibles = Objects::GetAllObjectsWithID(DestructibleObject::GetID());
	}

	Vector3 ForwardRotation;

	Vector3 NewDir = 0;
	if (Input::IsKeyDown(SDLK_w) || Input::IsKeyDown(SDLK_UP))
	{
		NewDir += Vector3::GetForwardVector(ForwardRotation) * Performance::DeltaTime;
	}
	if (Input::IsKeyDown(SDLK_s) || Input::IsKeyDown(SDLK_DOWN))
	{
		NewDir += -Vector3::GetForwardVector(ForwardRotation) * Performance::DeltaTime;
	}
	if (Input::IsKeyDown(SDLK_d) || Input::IsKeyDown(SDLK_RIGHT))
	{
		NewDir += Vector3::GetRightVector(ForwardRotation) * Performance::DeltaTime;
	}
	if (Input::IsKeyDown(SDLK_a) || Input::IsKeyDown(SDLK_LEFT))
	{
		NewDir += -Vector3::GetRightVector(ForwardRotation) * Performance::DeltaTime;
	}
	NewDir = NewDir.Normalize();
	Velocity += NewDir * Performance::DeltaTime * Acceleration;

	CameraOffset = Vector3::Lerp(CameraOffset, Velocity, Performance::DeltaTime * 5);

	PlayerCamera->RelativeTransform.Location = CameraOffset / 10 + Vector3(0, 75 + DisplayedSize, 0);
	GetTransform().Location.Y = 5 + Size;

	TryMove(Velocity * Performance::DeltaTime);
	PlayerMesh->RelativeTransform.Scale = DisplayedSize / 2;

	DisplayedSize = std::lerp(DisplayedSize, Size, std::clamp(Performance::DeltaTime * 2, 0.0f, 1.0f));

	if (Velocity.Length() > MaxSpeed)
	{
		Velocity = Velocity.Normalize() * MaxSpeed;
	}

	if (NewDir.Length() == 0)
	{
		Velocity -= Velocity.Normalize() * Performance::DeltaTime * Deceleration;

		if (Vector3::NearlyEqual(Velocity, 0, 1))
		{
			Velocity = 0;
		}
	}


	Vector3 Pos2D = GetTransform().Location;
	Pos2D.Y = 0;
	bool ChangedSize = false;
	for (WorldObject* obj : AllDestructibles)
	{
		DestructibleObject* DestructibleObj = dynamic_cast<DestructibleObject*>(obj);

		if (DestructibleObj->IsSuckedUp)
			continue;

		float dst = Vector3::Distance(Vector3(obj->GetTransform().Location.X, 0, obj->GetTransform().Location.Z), Pos2D);

		if (dst < Size * 3 && DestructibleObj->RequiredSize <= Size)
		{
			Size += DestructibleObj->Reward * 0.15f;
			ChangedSize = true;
			DestructibleObj->SuckUp();
		}
		else if (dst < 5 && DestructibleObj)
		{
			DestructibleObj->IsPulled = true;
		}
	}
	if (ChangedSize)
	{
		AllDestructibles = Objects::GetAllObjectsWithID(DestructibleObject::GetID());
	}

	PlayerCamera->SetFOV(50);
}

void PlayerObject::Destroy()
{
	Player = nullptr;
}
