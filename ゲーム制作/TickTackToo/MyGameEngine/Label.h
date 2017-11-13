/*Label.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Node.h"
/********************/


//文字を表示するためのラベルクラス
//Nodeクラスを継承
class Label : public Node
{
	//ラベルのフォントを格納する変数
	LPD3DXFONT _pFont;

	//表示する文字を格納する変数
	TCHAR _string[256];

public:

	//コンストラクタ
	Label();

	//デストラクタ
	~Label();

	//静的関数	ラベルの作成をcocos2dxのような記述をできるようにする
	//引数->表示する文字・フォントの種類・フォントサイズ
	//戻値->ラベル
	static Label *Create(LPCSTR str, LPCSTR font, int size);

	//フォントの準備
	//引数->フォントの種類・フォントサイズ
	//戻値->なし
	void Load(LPCSTR fontType, int fontSize);

	//文字の描画
	//引数->なし
	//戻値->なし
	void Draw();

	//表示する文字の変更
	//引数->表示する文字
	//戻値->なし
	void SetString(LPCSTR str);
};