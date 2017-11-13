/*Light.cpp*/

/*2017-09-18
	狩野 達哉
		ライトを使用できるようにするLightプログラム*/

/****インクルード****/
#include "Light.h"
/********************/


//デストラクタ
Light::~Light()
{
}

//静的関数	ライトの作成
Light *Light::Create()
{
	//ライトの情報
	D3DLIGHT9 lightState;

	//ライトの情報をすべて初期化
	ZeroMemory(&lightState, sizeof(lightState));

	//ライトの種類を平行光源に設定
	lightState.Type = D3DLIGHT_DIRECTIONAL;

	//ライトの向きを右下奥方向に設定
	lightState.Direction = D3DXVECTOR3(1, -1, 1);

	//ライトの色を設定
	lightState.Diffuse.r = 1.0f;
	lightState.Diffuse.g = 1.0f;
	lightState.Diffuse.b = 1.0f;

	//ライトをセット
	//第一引数はライトの番号
	g.pDevice->SetLight(0, &lightState);

	//ライトを有効化
	g.pDevice->LightEnable(0, true);

	Light *pLight = new Light;
	return pLight;
}
