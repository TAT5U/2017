#pragma once

//インクルード
#include <Windows.h>
#include <d3dx9.h>
#include "MyRect.h"
#include "Input.h"

#define SAFE_DELETE(X) if(X){ delete X; X = nullptr;}
#define SAFE_RELEASE(X) if(X){ X->Release(); X = nullptr;}

class Scene;
class Camera;

//グローバル変数
class Global
{
public:
	//定数
	const int	WINDOW_WIDTH = 800;		//ウィンドウの幅
	const int	WINDOW_HEIGHT = 600;	//ウィンドウの高さ

	//変数
	LPDIRECT3DDEVICE9	pDevice;		//Direct3Dデバイスオブジェクト
	Scene*				pScene;
	Input*				pInput;
	Camera*				pCamera;
	void ReplaceScene(Scene* pNextScene);
};

//グローバルオブジェクト（外部宣言）
extern Global g;