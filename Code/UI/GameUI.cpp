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
	TextContainer->AddChild(new UIText(1, 1, "Helth: 69%", Text));

}

void GameUI::Tick()
{
	PlayerSizeText->SetText("Size: " + std::to_string((int)(PlayerObject::GetPlayer()->DisplayedSize * 10)) + "%");
}

GameUI::~GameUI()
{
	delete Text;
}
