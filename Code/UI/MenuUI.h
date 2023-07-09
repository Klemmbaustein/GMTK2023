#pragma once
#include <UI/Default/UICanvas.h>

class TextRenderer;

class MenuUI : public UICanvas
{
public:
	void GenerateDescriptionText();
	MenuUI();
	~MenuUI();
	TextRenderer* Text = nullptr;
	void OnButtonClicked(int Index) override;
};