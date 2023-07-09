#include "MenuUI.h"
#include <UI/UIButton.h>
#include <Engine/OS.h>
#include <Rendering/Texture/Texture.h>
#include <UI/UIText.h>
#include <Engine/Input.h>
#include <format>
#include <Engine/Application.h>
#include <Engine/EngineProperties.h>
#include <UI/UIBackground.h>
#include <Engine/Scene.h>
#include <Objects/PlayerObject.h>

MenuUI::MenuUI()
{
	Text = new TextRenderer();
	(new UIButton(true, Vector2(0.6, -0.75), 1, this, 0))
		->SetUseTexture(true, Texture::LoadTexture("GMTK-Jam"))
		->SetSizeMode(UIBox::E_PIXEL_RELATIVE)
		->SetMinSize(Vector2(0.03) * Vector2(16, 9));

	(new UIText(0.6, 1, std::format("Klemmgine version {}", VERSION_STRING), Text))
		->SetPosition(Vector2(0.6, -0.9));

	std::map<int, std::string> GameOptions =
	{
		std::pair(1, "Play"),
		std::pair(2, "Quit")
	};
	
	UIBackground* bg = new UIBackground(false, 0, 0.1, Vector2(0.5, 1.5));

	bg	->SetOpacity(0.75)
		->SetPosition(Vector2(-0.25, -0.75));

	bg->Align = UIBox::E_REVERSE;
	bg->AddChild(new UIText(1, 1, "Cool logo here", Text));

	for (auto& opt : GameOptions)
	{
		auto NewButton = (new UIButton(true, 0, 1, this, opt.first));
		bg->AddChild(NewButton
			->SetBorder(UIBox::E_ROUNDED, 1)
			->SetTryFill(true)
			->AddChild((new UIText(1, 0, opt.second, Text))));
	}

	Input::CursorVisible = true;
}

MenuUI::~MenuUI()
{
	delete Text;
}

void MenuUI::OnButtonClicked(int Index)
{
	switch (Index)
	{
	case 0:
		OS::OpenFile("https://itch.io/jam/gmtk-2023");
		break;
	case 1:
		PlayerObject::CurrentLevel = 69;
		PlayerObject::Score = 9999;
		Scene::LoadNewScene("Level1");
		break;
	case 2:
		Application::Quit();
		break;
	default:
		break;
	}
}
