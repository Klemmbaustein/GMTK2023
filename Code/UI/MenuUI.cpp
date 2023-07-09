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
#include <Engine/Save.h>

const char* GameDescriptionText = "Oh no!\nThe alien invaders have destroyed your\nhome planetby sucking everything up with their\nspacecraft!\n\
But now the roles are reversed.\nThe alien invaders want you to earn your\nfreedom by sucking up all valuables from\nanother planet.";

void MenuUI::GenerateDescriptionText()
{
	UIBox* GameDescrBox = new UIBox(false, Vector2(0.4, 0.25));
	GameDescrBox->Align = UIBox::E_REVERSE;

	std::vector<std::string> Lines;
	std::string NewLine;
	for (char c : std::string(GameDescriptionText))
	{
		if (c == '\n')
		{
			Lines.push_back(NewLine);
			NewLine.clear();
			continue;
		}
		NewLine.append({c});
	}
	Lines.push_back(NewLine);

	for (auto& i : Lines)
	{
		GameDescrBox->AddChild((new UIText(0.6, 1, i, Text))->SetPadding(0));
	}
}

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
		std::pair(2, "Fulscreen (F11)"),
		std::pair(3, "Quit")
	};
	
	UIBackground* bg = new UIBackground(false, 0, 0.1, Vector2(0.5, 1));

	bg	->SetOpacity(0.75)
		->SetBorder(UIBox::E_ROUNDED, 1)
		->SetPosition(Vector2(-0.25, -0.5))
		->AddChild(new UIText(2, 1, "Alien Invaders", Text))
		->Align = UIBox::E_REVERSE;


	for (auto& opt : GameOptions)
	{
		auto NewButton = (new UIButton(true, 0, 1, this, opt.first));
		bg->AddChild(NewButton
			->SetBorder(UIBox::E_ROUNDED, 1)
			->SetTryFill(true)
			->AddChild((new UIText(1, 0, opt.second, Text))));
	}

	SaveGame ScoreSave = SaveGame("Gameplay");
	size_t HighScore = 0;
	try
	{
		HighScore = std::stoi(ScoreSave.GetPropterty("HighScore").Value);
	}
	catch (std::exception& e) {}
	bg->AddChild(new UIText(1, 1, std::format("High score: {}", HighScore), Text));

	Input::CursorVisible = true;
	GenerateDescriptionText();
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
		PlayerObject::CurrentLevel = 1;
		PlayerObject::Score = 0;
		Scene::LoadNewScene("Level1");
		break;
	case 2:
		Application::SetFullScreen(!Application::GetFullScreen());
		break;
	case 3:
		Application::Quit();
		break;
	default:
		break;
	}
}
