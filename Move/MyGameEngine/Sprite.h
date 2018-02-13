#pragma once
#include "Node.h"

class Sprite: public Node
{
	LPD3DXSPRITE		_pSprite;	//�X�v���C�g
	LPDIRECT3DTEXTURE9	_pTexture;	//�e�N�X�`��

	MyRect     _cut;    //�ؔ����͈�

public:
	Sprite();
	~Sprite();
	static Sprite* Create(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));
	void Load(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));	//�ǂݍ���
	void Draw();				//�`��

	void SetRect(MyRect cut);
	
};