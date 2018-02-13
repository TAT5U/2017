/*Main.cpp*/

/*2017-06-06
	狩野達哉
		Windowsのウィンドウの表示を行う*/


/*****インクルード*****/
#include "Global.h"
#include "Game.h"
/**********************/


/**************リンカ**************/
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
/**********************************/


//定数宣言
//ウィンドウクラス名	constで変更不可にする
//LPCSTRで文字列専用型
const LPCSTR WIN_CLASS_NAME = "Sample";


//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/********************グローバル変数********************/
//外部宣言したオブジェクトを宣言することで
//他のところでもグローバルクラスが使えるようになる
//グローバルクラス
Global g;

//ゲームオブジェクト
Game *pGame;
/******************************************************/




/****メモリリークを検出するためにデバッグ機能などを設定****/
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
/**********************************************************/

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{


/*********************メモリリークを検出して出力*********************/
#if _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
/********************************************************************/




	//ウィンドウクラスの作成
	WNDCLASSEX wc;

	//作成したウィンドウクラスの情報
	//構造体のサイズ
	wc.cbSize = sizeof(WNDCLASSEX);

	//インスタンスハンドル
	wc.hInstance = hInstance;

	//ウィンドウクラス名
	wc.lpszClassName = WIN_CLASS_NAME;

	//ウィンドウプロシージャ
	wc.lpfnWndProc = WndProc;

	//ウィンドウスタイル(デフォルト)
	wc.style = CS_VREDRAW | CS_HREDRAW;

	//アイコン
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//小さいアイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	//マウスカーソル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	//メニュー(なし)
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//背景(白)
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//作成したクラスを登録
	RegisterClassEx(&wc);

	//ウィンドウサイズの計算(枠の内側部分)
	RECT winRect = { 0, 0, g.WINDOW_WIDTH, g.WINDOW_HEIGHT };

	//サイズ(RECT),ウィンドウスタイル,メニューバーの有無
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウの幅を格納
	int winW = winRect.right - winRect.left;

	//ウィンドウの高さを格納
	int winH = winRect.bottom - winRect.top;

	//ウィンドウ作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//ウィンドウクラス名
		"Sample",		//タイトルバーの内容
		WS_OVERLAPPEDWINDOW,	//スタイル(普通のウィンドウ)
		CW_USEDEFAULT,			//表示位置左(おまかせ)
		CW_USEDEFAULT,			//表示位置上(おまかせ)
		winW,					//ウィンドウ幅
		winH,					//ウィンドウ高さ
		NULL,					//親ウィンドウ(なし)
		NULL,					//メニュー
		hInstance,				//インスタンス
		NULL					//パラメータ(なし)
		);

	//ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);

	//ゲームオブジェクト作成
	pGame = new Game;

	//ゲーム(DirectX)の初期化
	// エラーが出たらそこで終了させる
	if (FAILED(pGame->Init(hWnd)))
	{
		return 0;
	}


	//メッセージループ
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
	delete pGame;

	return 0;
}

//ウィンドウプロシージャ(何かあったときに呼び出される)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//閉じる以外で終了したい場合にフラグを変えることで
	//終了処理を行う
	if (g.GetEndFlg())
	{
		PostQuitMessage(0);
		return 0;
	}

	switch (msg)
	{
	case WM_MOUSEMOVE:
		g.pInput->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		//プログラム終了
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}