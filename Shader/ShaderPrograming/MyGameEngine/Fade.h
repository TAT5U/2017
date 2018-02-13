/*Fade.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Sprite.h"
#include "Label.h"
#include<vector>
/********************/


//�t�F�[�h�������s��Fade�N���X
//Scene�N���X���p�����Ă���̂�Init�Ȃǂ͍s��Ȃ���΂Ȃ�Ȃ�
class Fade : public Sprite, Label
{
	//�t�F�[�h�C��,�t�F�[�h�A�E�g���s���̌��݂̓����x�E�J�E���g
	int fadeInAlpha, fadeOutAlpha, i;

	//�t�F�[�h�ɓo�^����Sprite, �t�F�[�h�����Ȃ�Sprite
	std::vector<Sprite *>fadeInSprite, fadeOutSprite, notFadeSprite;
	
	//�t�F�[�h�ɓo�^����Label, �t�F�[�h�����Ȃ�Label
	std::vector<Label *>fadeInLabel, fadeOutLabel, notFadeLabel;
	
	//�t�F�[�h���s�\���ǂ����Ȃǂ�Flag
	bool fadeInFlg, fadeOutFlg, isFade;

public:

	//�R���X�g���N�^
	Fade();

	//�f�X�g���N�^
	~Fade();

	//����������(�g�p���Ȃ�)
	void Update();

	void FadeIn(Sprite *fadeSprite);
	void FadeOut(Sprite *fadeSprite);

	void FadeIn(Label *label);
	void FadeOut(Label *label);
	void NoFade(Sprite *noFadeSprite);
	void NoFade(Label *noFadeLabel);
	bool GetFadeEnd();

};