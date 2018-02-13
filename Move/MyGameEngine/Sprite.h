#pragma once
#include "Node.h"

class Sprite: public Node
{
	LPD3DXSPRITE		_pSprite;	//スプライト
	LPDIRECT3DTEXTURE9	_pTexture;	//テクスチャ

	MyRect     _cut;    //切抜き範囲

public:
	Sprite();
	~Sprite();
	static Sprite* Create(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));
	void Load(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));	//読み込み
	void Draw();				//描画

	void SetRect(MyRect cut);
	
};