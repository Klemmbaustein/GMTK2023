#pragma once
#include <UI/Default/UICanvas.h>
#include <UI/UIText.h>

class GameUI : public UICanvas
{
	UIText* PlayerSizeText = nullptr;
	UIText* ProgressText = nullptr;
public:
	GameUI();
	void Tick() override;
	~GameUI();
	TextRenderer* Text = new TextRenderer();
};