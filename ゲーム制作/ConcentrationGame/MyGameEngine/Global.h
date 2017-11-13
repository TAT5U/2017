/*Global.h*/

//インクルードガード
//二重にインクルードすることを防いでくれる
//#ifndefと同じ
#pragma once

/***************インクルード***************/
//WindowsAPIを使用可能にする
#include<windows.h>

//これでDirectXが使用できるようになる
//DirectXのヘッダ
#include<d3dx9.h>

//ここに記述でどこでも使用することができる
//オリジナルのMyRectヘッダ
#include "MyRect.h"

#include "Input.h"
/******************************************/


//deleteしてnullを格納する正しい解放処理のマクロ化
#define SAFE_DELETE(X) if(X){delete X; X = nullptr;}
#define SAFE_RELEASE(X) if(X){X->Release(); X = nullptr;}


//お互いにインクルードしあうとエラーを吐いてしまい
//片側だけインクルードでもエラーを吐いてしまう
//その場合にはヘッダをインクルードしないで前方宣言というものを使用する
//前方宣言はプロトタイプ宣言のクラスバージョン
//使用することによって【宣言した型のポインタ】なら宣言できるようになる
//前方宣言
class Scene;
class Fade;


//WinMainとプロシージャはクラス化×
//どこのクラスでも使う定数を宣言するグローバルクラス
class Global
{
	bool fadeFlg;

	bool endFlg;

public:

	Global();

	//定数宣言
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	const float STANDARD_CONTENT_WIDTH;
	const float STANDARD_CONTENT_HEIGHT;

	//透明度のMAX値・MIN値
	const int ALPHA_MAX, ALPHA_MIN;

	//Direct3Dデバイスオブジェクト
	LPDIRECT3DDEVICE9 pDevice;

	//シーンを管理するための変数
	Scene *pScene;

	//入力デバイスの管理
	Input *pInput;

	Fade *pFade;

	//シーン切り替え
	//引数->次のシーン
	//戻値->なし
	void ReplaceScene(Scene *pNextScene);

	void SetAlphaFlg(bool flg);

	bool GetAlphaFlg();

	void SetEndFlg(bool flg);

	bool GetEndFlg();
};

//ここで使用する定数などが複数のcppで使われる場合などに使用する
//他の方法としてシングルトンもある
//グローバルオブジェクト(外部宣言)
extern Global g;