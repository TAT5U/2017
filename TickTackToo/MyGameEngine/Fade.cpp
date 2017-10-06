#include "Fade.h"

Fade::Fade()
{
	fadeInAlpha = 0;
	fadeOutAlpha = 255;
	fadeInSprite.clear();
	fadeOutSprite.clear();
	fadeInFlg = false;
	fadeOutFlg = false;
	isFade = false;
	i = 0;
}
Fade::~Fade()
{

}
//‰Šú‰»ˆ—
void Fade::Init()
{
}

//XVˆ—
void Fade::Update()
{
	if (fadeInFlg)
	{
		fadeInAlpha = fadeInAlpha + 5;
		while (i < fadeInSprite.size())
		{
			fadeInSprite[i]->SetFadeValue(fadeInAlpha);
			g.SetFadeFlg(true);
			i++;
		}
		i = 0;
		if (fadeInAlpha >= 255)
		{
			fadeInFlg = false;
			fadeInAlpha = 0;
			fadeInSprite.clear();
			g.SetFadeFlg(false);
			isFade = true;
		}
	}
	if (fadeOutFlg)
	{
		fadeOutAlpha = fadeOutAlpha - 3;
		while (i < fadeOutSprite.size())
		{
			fadeOutSprite[i]->SetFadeValue(fadeOutAlpha);
			g.SetFadeFlg(true);
			i++;
		}
		i = 0;
		if (fadeOutAlpha <= 0)
		{
			fadeOutFlg = false;
			fadeOutAlpha = 255;
			fadeOutSprite.clear();
			isFade = true;
		}
	}
}
void Fade::Input()
{

}

void Fade::FadeIn(Sprite *fadeSprite)
{
	fadeInSprite.push_back(fadeSprite);
	fadeInFlg = true;
	isFade = false;
}
void Fade::FadeOut(Sprite *fadeSprite)
{
	fadeOutSprite.push_back(fadeSprite);
	fadeOutFlg = true;
	isFade = false;
}

bool Fade::GetFadeEnd()
{
	return isFade;
}