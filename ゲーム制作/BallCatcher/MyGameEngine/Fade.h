#pragma once
#include "Game.h"

class Fade : public Scene
{
	int fadeInAlpha, fadeOutAlpha, i;
	vector<Sprite *>fadeInSprite, fadeOutSprite;
	vector<Label *>fadeInLabel, fadeOutLabel;
	bool fadeInFlg, fadeOutFlg, isFade;
public:
	Fade();
	~Fade();

	void Init() override;
	void Update() override;
	void Input() override;

	void FadeIn(Sprite *fadeSprite);
	void FadeOut(Sprite *fadeSprite);

	void FadeIn(Label *label);
	void FadeOut(Label *label);
	bool GetFadeEnd();

};