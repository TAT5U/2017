/*Fade.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Sprite.h"
#include "Label.h"
#include<vector>
/********************/


//フェード処理を行うFadeクラス
//Sceneクラスを継承しているのでInitなどは行わなければならない
class Fade : public Sprite, Label
{
	//フェードイン,フェードアウト実行時の現在の透明度・カウント
	int fadeInAlpha, fadeOutAlpha, i;

	//フェードに登録するSprite, フェードさせないSprite
	std::vector<Sprite *>fadeInSprite, fadeOutSprite, notFadeSprite;
	
	//フェードに登録するLabel, フェードさせないLabel
	std::vector<Label *>fadeInLabel, fadeOutLabel, notFadeLabel;
	
	//フェード実行可能かどうかなどのFlag
	bool fadeInFlg, fadeOutFlg, isFade;

public:

	//コンストラクタ
	Fade();

	//デストラクタ
	~Fade();

	//初期化処理(使用しない)
	void Update();

	void FadeIn(Sprite *fadeSprite);
	void FadeOut(Sprite *fadeSprite);

	void FadeIn(Label *label);
	void FadeOut(Label *label);
	void NoFade(Sprite *noFadeSprite);
	void NoFade(Label *noFadeLabel);
	bool GetFadeEnd();

};