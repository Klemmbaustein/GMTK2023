#pragma once
#include <UI/Default/UICanvas.h>
#include <UI/UIBackground.h>
#include <UI/UIText.h>
#include <Sound/Sound.h>

class LevelEndUI : public UICanvas
{
	UIBackground* Background = nullptr;
	TextRenderer* Text = nullptr;
	UIText* SecondsText = nullptr;
	UIText* ScoreText = nullptr;
	size_t Seconds = 0;
	size_t TargetScore = 0;
	float TimerDownTick = 1;
	bool ScreenEnded = false;
	Sound::SoundBuffer* EndSound = Sound::LoadSound("EndScreen");
	Sound::SoundBuffer* TickSound = Sound::LoadSound("TickSound");
public:
	LevelEndUI();
	~LevelEndUI();
	void Tick() override;

};