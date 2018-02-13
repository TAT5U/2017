/*Player.cpp*/

/*2017-06-07
	狩野 達哉
		ゲーム画面の描画を行う*/

/****インクルード****/
#include "Game.h"
/********************/


//コンストラクタ
Game::Game()
{
	//変数の初期化
	_pD3d = nullptr;
	g.pDevice = nullptr;
	g.pScene = nullptr;
	g.pInput = nullptr;
	g.pFade = nullptr;
}

//デストラクタ
Game::~Game()
{
	//プログラム終了時にはオブジェクトとデバイスオブジェクトを消去しなければならない
	//なので、終了時に解放をする
	//解放順番は作成した順番の逆で解放を行う
	//LPで始まる型の変数はReleaseで解放できる
	//解放処理
	SAFE_DELETE(g.pFade);
	SAFE_DELETE(g.pInput);
	SAFE_DELETE(g.pScene);
	SAFE_RELEASE(g.pDevice);
	SAFE_RELEASE(_pD3d)
}

//初期化処理
HRESULT Game::Init(HWND hWnd)
{
	//Direct3Dオブジェクトを作成
	//DirectX本体準備
	_pD3d = Direct3DCreate9(D3D_SDK_VERSION);

	//DIRECT3Dデバイスオブジェクトの作成
	//Direct3DオブジェクトのpDeviceがゲーム画面になり、pDeviceにたいして操作ができる
	//DIRECT3Dデバイスオブジェクトの専用の構造体
	D3DPRESENT_PARAMETERS d3dpp;

	//構造体の中身を初期化
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//ウィンドウモードの選択
	d3dpp.Windowed = TRUE;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//クライアントの幅と高さ
	d3dpp.BackBufferWidth = g.WINDOW_WIDTH;
	d3dpp.BackBufferHeight = g.WINDOW_HEIGHT;

	// 画面デバイス作成に成功したかどうか
	if (FAILED(_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g.pDevice)))
	{
		// エラー
		MessageBox(NULL, "デバイスオブジェクトの生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	g.pFade = new Fade;

	//PlaySceneのオブジェクトを宣言
	g.pScene = new Sample;

	//PlaySceneのInitを呼び出す
	g.pScene->Init();

	//Inputのオブジェクトを宣言
	//普通にやると"Input"が他のソースとかぶってしまうので
	//new classで宣言する
	g.pInput = new class Input;

	//InputのInitを呼び出す
	//そのときウィンドウハンドルを引数として送る
	g.pInput->Init(hWnd);




	//アルファブレンドを有効化
	g.pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//半透明部分の表示
	//手前
	g.pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//奥
	g.pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//更新処理
void Game::Update()
{
	//PlaySceneのUpdateを呼び出す
	g.pScene->Update();
}

//入力処理
void Game::Input()
{
	//PlaySceneのInputを呼び出す
	g.pScene->Input();

	//InputのUpdateを呼び出す
	g.pInput->Update();
	g.pFade->Update();
}

//描画処理
void Game::Draw()
{
	//ゼットバッファ法で表示している	表示が早い
	//画面をクリア
	//ここで背景の色も指定できる
	//現在は水色に指定
	g.pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	//何かを描画するときは、描画する前にBeginScene関数、描画後にEndScene関数を呼び出す
	//最後にバックバッファとフロントバッファを入れ替える
	//描画は見えないところで描画し、それをまとめて入れ替えている

	//描画開始
	g.pDevice->BeginScene();

	//PlaySceneのDrawを呼び出す
	g.pScene->Draw();

	//描画終了
	g.pDevice->EndScene();

	//入れ替え
	g.pDevice->Present(NULL, NULL, NULL, NULL);
}