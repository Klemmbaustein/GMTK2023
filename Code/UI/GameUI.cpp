#include "GameUI.h"
#include <Objects/PlayerObject.h>
#include <UI/UIBackground.h>
#include <format>

GameUI::GameUI()
{
	UIBackground* TextBackground = new UIBackground(true, Vector2(-0.5, -0.8), 0.1, Vector2(1, 0.1));
	TextBackground->SetOpacity(0.75)->SetBorder(UIBox::E_ROUNDED, 1);
	TextBackground->Align = UIBox::E_CENTERED;

	UIBox* TextContainer = (new UIBox(true, 0))->SetPadding(0);
	TextBackground->AddChild(TextContainer);

	TimerText = new UIText(1, 1, "Size: 10%", Text);
	TextContainer->AddChild(TimerText);
	ProgressText = new UIText(1, 1, "Progress: 0%", Text);
	TextContainer->AddChild(ProgressText);
	ScoreText = new UIText(1, 1, std::format("Score: {}", PlayerObject::Score), Text);
	TextContainer->AddChild(ScoreText);
}

void GameUI::Tick()
{
	if (!PlayerObject::GetPlayer())
	{
		delete this;
		return;
	}

	int32_t Seconds = PlayerObject::GetPlayer()->LevelTimer.TimeSinceCreation();
	std::string SecondsString = std::to_string(Seconds % 60);
	if (SecondsString.size() == 1)
	{
		SecondsString = std::format("0{}", SecondsString);
	}

	std::string TimeString = std::format("Time: {}:{}", Seconds / 60, SecondsString);


	TimerText->SetText(TimeString);
	ProgressText->SetText("Progress: " + std::to_string((int)(PlayerObject::GetPlayer()->Progress * 100)) + "%");
	
}

GameUI::~GameUI()
{
	delete Text;
}
