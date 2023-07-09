#include "LevelEndUI.h"
#include <Engine/Log.h>
#include <Engine/Input.h>
#include <Objects/PlayerObject.h>
#include <format>
#include <Engine/Scene.h>
#include <Engine/EngineRandom.h>

LevelEndUI::LevelEndUI()
{
	Sound::PlaySound2D(EndSound, 1, 0.5);
	Background = new UIBackground(true, -1, 0, 2);
	Text = new TextRenderer();

	SecondsText = new UIText(1, 1, "Time: ???", Text);
	ScoreText = new UIText(1, 1, "Score: ???", Text);
	UIBox* EndUI = new UIBox(false, 0);

	EndUI->SetPadding(0)
		->SetMinSize(1)
		->AddChild(new UIText(2, 1, std::format("Level {} complete!", PlayerObject::CurrentLevel), Text))
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
	delete TickSound;
	delete EndSound;
}

void LevelEndUI::Tick()
{
	ScoreText->SetText(std::format("Score: {}", PlayerObject::Score));
	if (TimerDownTick <= 0)
	{
		TimerDownTick = 0.05;
		
		if (ScreenEnded)
		{
			Scene::LoadNewScene(std::format("Level{}", ++PlayerObject::CurrentLevel));
		}

		if (TargetScore > PlayerObject::Score)
		{
			Sound::PlaySound2D(TickSound, Random::GetRandomFloat(0.7, 1.3), 0.25);
			PlayerObject::Score += 5;
		}
		else
		{
			PlayerObject::Score = TargetScore;
			ScreenEnded = true;
			TimerDownTick = 0.5;
		}
	}
	else
	{
		TimerDownTick -= Performance::DeltaTime;
	}
}
