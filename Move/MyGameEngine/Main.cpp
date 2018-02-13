//インクルード
#include "Global.h"
#include "Game.h"

//リンカ
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//定数宣言
const LPCSTR WIN_CLASS_NAME = "SampleGame";	//ウィンドウクラス名

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//グローバル変数
Global g;
Game* pGame;	//ゲームオブジェクト

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#if _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);	            //この構造体のサイズ
	wc.hInstance = hInstance;					//インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;			//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;					//ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;			//スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//マウスカーソル
	wc.lpszMenuName = NULL;						//メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//背景（白）
	RegisterClassEx(&wc);	//クラスを登録


	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, g.WINDOW_WIDTH, g.WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;	    //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;	    //ウィンドウ高さ


	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//ウィンドウクラス名
		"サンプルゲーム",		//タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW,	//スタイル（普通のウィンドウ）
		CW_USEDEFAULT,			//表示位置左（おまかせ）
		CW_USEDEFAULT,			//表示位置上（おまかせ）
		winW,					//ウィンドウ幅
		winH,					//ウィンドウ高さ
		NULL,					//親ウインドウ（なし）
		NULL,					//メニュー（なし）
		hInstance,				//インスタンス
		NULL					//パラメータ（なし）
		);


	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);


	//ゲームオブジェクト作成
	pGame = new Game;

	//ゲーム（DirectX）の初期化
	if (FAILED(pGame->Init(hWnd)))
	{
		return 0;
	}




	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//ゲームの処理

			//入力処理
			pGame->Input();

			//更新処理
			pGame->Update();

			//画面表示
			pGame->Draw();

		}
	}

	//DirectX開放処理
	SAFE_DELETE(pGame);


	return 0;
}


//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//case WM_KEYDOWN:
	//	g.ReplaceScene(new ClearScene);
	//	break;

	case WM_MOUSEMOVE:
		g.pInput->SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_DESTROY:
		PostQuitMessage(0);	//プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}