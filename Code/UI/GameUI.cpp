#include "GameUI.h"
#include <Objects/PlayerObject.h>
#include <UI/UIBackground.h>

GameUI::GameUI()
{
	UIBackground* TextBackground = new UIBackground(true, Vector2(-0.5, -0.8), 0.1, Vector2(1, 0.1));
	TextBackground->SetOpacity(0.75)->SetBorder(UIBox::E_ROUNDED, 1);
	TextBackground->Align = UIBox::E_CENTERED;

	UIBox* TextContainer = (new UIBox(true, 0))->SetPadding(0);
	TextBackground->AddChild(TextContainer);

	PlayerSizeText = new UIText(1, 1, "Size: 10%", Text);
	TextContainer->AddChild(PlayerSizeText);
	ProgressText = new UIText(1, 1, "Progress: 0%", Text);
	TextContainer->AddChild(ProgressText);

}

void GameUI::Tick()
{
	if (!PlayerObject::GetPlayer())
	{
		delete this;
		return;
	}

	PlayerSizeText->SetText("Size: " + std::to_string((int)(PlayerObject::GetPlayer()->DisplayedSize * 10)) + "%");
	ProgressText->SetText("Progress: " + std::to_string((int)(PlayerObject::GetPlayer()->Progress * 100)) + "%");
	
}

GameUI::~GameUI()
{
	delete Text;
}
