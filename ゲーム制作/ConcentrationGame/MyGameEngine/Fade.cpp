/*Fade.cpp*/

/*2017-10-16
	狩野 達哉
		フェードプログラム*/

/****インクルード****/
#include "Fade.h"
/********************/


//コンストラクタ
Fade::Fade()
{
	//変数の初期化
	fadeInAlpha = 0;
	fadeOutAlpha = 255;

	fadeInSprite.clear();
	fadeOutLabel.clear();
	fadeInLabel.clear();
	fadeOutSprite.clear();

	notFadeSprite.clear();
	notFadeLabel.clear();

	fadeInFlg = false;
	fadeOutFlg = false;
	isFade = false;
	i = 0;
}
Fade::~Fade()
{

}

//更新処理
//フェードイン・フェードアウトは
//Spriteが登録されていればSpriteに反映し、
//Labelが登録されていればLabelに反映する
//フェードしたくないものも登録可(後にコード修正必須)
void Fade::Update()
{
	//フェードイン処理
	if (fadeInFlg)
	{
		fadeInAlpha = fadeInAlpha + 5;

		//Sprite
		while (i < fadeInSprite.size())
		{
			fadeInSprite[i]->SetFadeValue(fadeInAlpha);
			g.SetAlphaFlg(true);
			i++;
		}
		i = 0;

		// NGSprite
		while (i < notFadeSprite.size())
		{
			notFadeSprite[i]->SetFadeValue(g.ALPHA_MAX);
			i++;
		}
		i = 0;
		
		//Label
		while (i < fadeInLabel.size())
		{
			fadeInLabel[i]->SetFadeValue(fadeInAlpha);
			g.SetAlphaFlg(true);
			i++;
		}
		i = 0;

		// NGLabel
		while (i < notFadeLabel.size())
		{
			notFadeLabel[i]->SetFadeValue(g.ALPHA_MAX);
			i++;
		}
		i = 0;

		//透明度がMAXになったら戻す
		if (fadeInAlpha >= g.ALPHA_MAX)
		{
			fadeInFlg = false;
			fadeInAlpha = g.ALPHA_MIN;
			fadeInSprite.clear();
			fadeInLabel.clear();
			notFadeSprite.clear();
			notFadeLabel.clear();
			g.SetAlphaFlg(false);
			isFade = true;
		}
	}

	//フェードアウト処理
	if (fadeOutFlg)
	{
		fadeOutAlpha = fadeOutAlpha - 3;
		
		//Sprite
		while (i < fadeOutSprite.size())
		{
			fadeOutSprite[i]->SetFadeValue(fadeOutAlpha);
			g.SetAlphaFlg(true);
			i++;
		}
		i = 0;

		// NGSprite
		while (i < notFadeSprite.size())
		{
			notFadeSprite[i]->SetFadeValue(g.ALPHA_MAX);
			g.SetAlphaFlg(true);
			i++;
		}
		i = 0;
		
		//Label
		while (i < fadeOutLabel.size())
		{
			fadeOutLabel[i]->SetFadeValue(fadeOutAlpha);
			g.SetAlphaFlg(true);
			i++;
		}
		i = 0;

		// NGLabel
		while (i < notFadeLabel.size())
		{
			notFadeLabel[i]->SetFadeValue(g.ALPHA_MAX);
			i++;
		}
		i = 0;

		//透明度がMINになったら戻す
		if (fadeOutAlpha <= g.ALPHA_MIN)
		{
			fadeOutFlg = false;
			fadeOutAlpha = g.ALPHA_MAX;
			fadeOutSprite.clear();
			fadeOutLabel.clear();
			notFadeSprite.clear();
			notFadeLabel.clear();
			g.SetAlphaFlg(false);
			isFade = true;
		}
	}
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


void Fade::FadeIn(Label *label)
{
	fadeInLabel.push_back(label);
	fadeInFlg = true;
	isFade = false;
}
void Fade::FadeOut(Label *label)
{
	fadeOutLabel.push_back(label);
	fadeOutFlg = true;
	isFade = false;
}
void Fade::NoFade(Sprite *noFadeSprite)
{
	notFadeSprite.push_back(noFadeSprite);
}
void Fade::NoFade(Label *noFadeLabel)
{
	notFadeLabel.push_back(noFadeLabel);
}


bool Fade::GetFadeEnd()
{
	return isFade;
}