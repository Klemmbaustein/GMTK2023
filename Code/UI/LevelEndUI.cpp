#include "LevelEndUI.h"
#include <Engine/Log.h>
#include <Engine/Input.h>
#include <Objects/PlayerObject.h>
#include <format>
#include <Engine/Scene.h>
#include <Engine/EngineRandom.h>
#include <World/Assets.h>
#include <filesystem>
#include <Engine/Save.h>

const std::map<const size_t, const std::string> Results =
{
	std::pair(600, "Perfect"),
	std::pair(550, "Great"),
	std::pair(550, "Good"),
	std::pair(500, "Ok"),
	std::pair(450, "Slow"),
	std::pair(300, "Very slow"),
	std::pair(200, "Bad"),
	std::pair(0, "Very bad"),
};

const std::string GetResultFromScore(size_t Score)
{
	std::string HighestScore;
	for (auto& i : Results)
	{
		if (Score >= i.first)
		{
			HighestScore = i.second;
		}
	}
	return HighestScore;
}

LevelEndUI::LevelEndUI()
{
	Sound::PlaySound2D(EndSound, 1, 0.5);
	Background = new UIBackground(true, -1, 0, 2);
	Text = new TextRenderer();

	SecondsText = new UIText(1, 1, "Time: ???", Text);
	ScoreText = new UIText(1, 1, "Score: ???", Text);
	HighScoreText = new UIText(1.5, 1, "", Text);
	HighScoreDescr = new UIText(1, 1, "", Text);
	UIBox* EndUI = new UIBox(false, 0);

	IsLastLevel = !std::filesystem::exists(Assets::GetAsset(std::format("Level{}.jscn", PlayerObject::CurrentLevel + 1)));

	EndUI->SetPadding(0)
		->SetMinSize(1)
		->AddChild((new UIText(2, 1, std::format("Level {} complete!", PlayerObject::CurrentLevel), Text))->SetPadding(0.005))
		->AddChild((new UIBackground(true, 0, 1, Vector2(1, 0.005)))->SetPadding(0.01, 0.01, 0.005, 0.005))
		->AddChild(SecondsText->SetPadding(0.005))
		->AddChild(ScoreText->SetPadding(0.005));

	if (IsLastLevel)
	{
		EndUI
			->AddChild(HighScoreDescr->SetPadding(0.005))
			->AddChild((new UIBackground(true, 0, 1, Vector2(1, 0.005)))->SetPadding(0.01, 0.01, 0.005, 0.005))
			->AddChild(HighScoreText->SetPadding(0.005));
	}

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
			if (!IsLastLevel)
			{
				Scene::LoadNewScene(std::format("Level{}", ++PlayerObject::CurrentLevel));
			}
			else
			{
				Scene::LoadNewScene("Menu");
			}
		}

		if (TargetScore > PlayerObject::Score)
		{
			Sound::PlaySound2D(TickSound, Random::GetRandomFloat(0.7, 1.3), 0.25);
			PlayerObject::Score += 5;
		}
		else
		{
			if (IsLastLevel)
			{
				SaveGame ScoreSave = SaveGame("Gameplay");
				size_t HighScore = 0;
				try
				{
					HighScore = std::stoi(ScoreSave.GetPropterty("HighScore").Value);
				}
				catch (std::exception& e) {}

				HighScore = std::max(PlayerObject::Score, HighScore);
				HighScoreText->SetText(std::format("High score: {} {}", HighScore, HighScore == PlayerObject::Score ? "(New)" : ""));
				HighScoreDescr->SetText(std::format("The hivemind says: {}", GetResultFromScore(PlayerObject::Score)));
				ScoreSave.SetPropterty(SaveGame::SaveProperty("HighScore", std::to_string(PlayerObject::Score), Type::E_INT));
				TimerDownTick = 5;
				PlayerObject::Score = TargetScore;
				ScreenEnded = true;
				return;
			}
			
			PlayerObject::Score = TargetScore;
			ScreenEnded = true;
			TimerDownTick = 1.5;
		}
	}
	else
	{
		TimerDownTick -= Performance::DeltaTime;
	}
}
