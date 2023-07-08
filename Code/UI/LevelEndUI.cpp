#include "LevelEndUI.h"
#include <Engine/Log.h>
#include <Engine/Input.h>
#include <Objects/PlayerObject.h>
#include <format>
#include <Engine/Scene.h>

LevelEndUI::LevelEndUI()
{
	Background = new UIBackground(true, -1, 0, 2);
	Text = new TextRenderer();

	SecondsText = new UIText(1, 1, "Time: ???", Text);
	ScoreText = new UIText(1, 1, "Score: ???", Text);
	UIBox* EndUI = new UIBox(false, 0);

	EndUI->SetPadding(0)
		->SetMinSize(1)
		->AddChild(new UIText(1, 1, "Level 1 complete!", Text))
		->AddChild(SecondsText)
		->AddChild(ScoreText);

	EndUI->Align = UIBox::E_REVERSE;


	(new UIBox(true, Vector2(-0.5)))
		->AddChild(EndUI)
		->Align = UIBox::E_CENTERED;

	Seconds = PlayerObject::GetPlayer()->LevelTimer.TimeSinceCreation();
	TargetScore = 180 - std::min(Seconds, 180ull) + PlayerObject::Score;

	std::string SecondsString = std::to_string(Seconds % 60);
	if (SecondsString.size() == 1)
	{
		SecondsString = std::format("0{}", SecondsString);
	}

	std::string TimeString = std::format("Time: {}:{}", Seconds / 60, SecondsString);

	SecondsText->SetText(TimeString);
}

LevelEndUI::~LevelEndUI()
{
}

void LevelEndUI::Tick()
{
	ScoreText->SetText(std::format("Score: {}", PlayerObject::Score));
	if (TimerDownTick <= 0)
	{
		TimerDownTick = 0.025;
		
		if (ScreenEnded)
		{
			Scene::LoadNewScene("Level2");
		}

		if (TargetScore > PlayerObject::Score)
		{
			PlayerObject::Score += 5;
		}
		else
		{
			ScreenEnded = true;
			TimerDownTick = 0.5;
		}
	}
	else
	{
		TimerDownTick -= Performance::DeltaTime;
	}
}
