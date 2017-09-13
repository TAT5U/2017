/*Label.cpp*/

/*2017-07-13
	狩野 達哉
		ラベルを表示するために
			使用するLabelプログラム*/

/****インクルード****/
#include "Label.h"
/********************/


//コンストラクタ
Label::Label()
{
	//変数の初期化
	_pFont = nullptr;
	ZeroMemory(_string, sizeof(_string));
}

//デストラクタ
Label::~Label()
{
	//開放処理
	_pFont->Release();
}

//静的関数	ラベルの作成をcocos2dxのような記述をできるようにする
Label *Label::Create(LPCSTR str, LPCSTR font, int size)
{
	Label *plabel = new Label();
	plabel->Load(font, size);
	plabel->SetString(str);
	return plabel;
}

//フォントの準備
void Label::Load(LPCSTR fontType, int fontSize)
{
	//2番目がフォントサイズ
	//最後から2番目がフォントの種類
	D3DXCreateFont(g.pDevice, fontSize, 0, FW_NORMAL, 1,
		FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, fontType, &_pFont);
}

//文字の描画
void Label::Draw()
{
	//描画位置(範囲)の設定
	//左・上・幅・高さの順番
	RECT rect;
	rect.left = _position.x - _size.x * _anchorPoint.x * _scale.x;
	rect.top = _position.y - _size.y * _anchorPoint.y * _scale.y;
	rect.right = rect.left + _size.x * _scale.x;
	rect.bottom = rect.top + _size.y * _scale.y;

	//文字の格納
	//2番目が表示する文字数
	_pFont->DrawText(NULL, _string, -1, &rect,
		DT_LEFT | DT_TOP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

//表示する文字の変更
void Label::SetString(LPCSTR str)
{
	//一度メンバ変数にコピーしてから文字を変更する
	strcpy(_string, str);
	RECT rect = { 0, 0, 0, 0 };
	_pFont->DrawText(NULL, _string, -1, &rect, DT_CALCRECT, NULL);
	_size.x = rect.right;
	_size.y = rect.bottom;
}