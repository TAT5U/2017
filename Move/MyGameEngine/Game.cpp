#include "Game.h"
#include "..\PlayScene.h"


Game::Game()
{
	_pD3d = nullptr;
	g.pInput = nullptr;
	g.pScene = nullptr;
}


Game::~Game()
{
	//開放処理
	SAFE_DELETE(g.pInput);
	SAFE_DELETE(g.pScene);
	SAFE_RELEASE(g.pDevice);
	SAFE_RELEASE(_pD3d);

}

//初期化処理
HRESULT Game::Init(HWND hWnd)
{
	//Direct3Dオブジェクトの作成
	_pD3d = Direct3DCreate9(D3D_SDK_VERSION);


	//DIRECT3Dデバイスオブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;					//専用の構造体
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//中身を全部0にする
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferWidth = g.WINDOW_WIDTH;
	d3dpp.BackBufferHeight = g.WINDOW_HEIGHT;

	
	if (FAILED(_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g.pDevice)))
	{
		MessageBox(NULL, "デバイスオブジェクトの生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}



	g.pScene = new PlayScene;
	g.pScene->Init();

	g.pInput = new class Input;
	g.pInput->Init(hWnd);

	g.pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g.pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g.pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	

	return S_OK;
}

//更新処理
void Game::Update()
{
	g.pScene->Update();
}

//入力処理
void Game::Input()
{
	g.pInput->Update();
	g.pScene->Input();
}

//描画処理
void Game::Draw()
{
	//画面をクリア
	g.pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

	//描画開始
	g.pDevice->BeginScene();

	//ゲーム画面の描画
	g.pScene->Draw();

	//描画終了
	g.pDevice->EndScene();

	//スワップ
	g.pDevice->Present(NULL, NULL, NULL, NULL);
}