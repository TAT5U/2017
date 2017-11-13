//////////////////////////////////////////////////////////////////////
// 重力
//	Tatsuya
//		2017.11.13
//////////////////////////////////////////////////////////////////////

// #include
#include <Windows.h>
#include "constants.h"
#include "Ball.h"

// Function prototype
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp );
BOOL CreateMainWindow( HINSTANCE hInst, int nCmdShow );
ATOM InitApp( HINSTANCE hInst );
BOOL InitInstance( HINSTANCE hInst, int nCmdShow );

// Global variable
Ball *pBall;


//////////////////////////////////////////////////////////////////////
//	WinMain
//		Entry Point
//////////////////////////////////////////////////////////////////////
int APIENTRY WinMain( HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow )
{
	MSG	msg;
	BOOL bRet;

	// メインウィンドウの生成
	if( !CreateMainWindow( hCurInst, nCmdShow ) )
		return 1;

/*	
	// ToDo::ゲーム初期化処理
	
	// メインメッセージループ
	do
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ToDo::ゲーム処理
		}
	}while( msg.message != WM_QUIT );

	// ToDo::ゲーム終了処理
*/
	
	

	while( ( bRet = GetMessage( &msg, NULL, 0, 0 ) ) != 0 )
	{
		if( bRet == -1 )
		{
			break;
		}
		else
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
	

	return (int)msg.wParam;
}

//////////////////////////////////////////////////////////////////////
//	WndProc
//		ウィンドウプロシージャ
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp )
{
	PAINTSTRUCT ps;
	HDC hdc;

	// メッセージ処理
	switch( msg )
	{
		// ウィンドウ生成
		case WM_CREATE:
			pBall = new Ball();
			pBall->Init( GAME_WIDTH / 2, 0, 0, 1, 9.8, 15 );			// 初期化
			SetTimer( hWnd, TIMER_ID, TIMER_INTERVAL, NULL );		// タイマーセット
			break;

		// タイマー
		case WM_TIMER:
			pBall->Update();										// 更新処理
			InvalidateRect( hWnd, NULL, TRUE );						// 再描画命令
			break;

		// 描画
		case WM_PAINT:
			hdc = BeginPaint( hWnd, &ps );
			pBall->Draw( hdc );										// 描画処理
			EndPaint (hWnd, &ps );
			break;

		// ウィンドウ破棄
		case WM_DESTROY:
			KillTimer( hWnd, TIMER_ID );							// タイマー破棄
			SAFE_DELETE( pBall );
			PostQuitMessage(0);
			break;

		// デフォルト処理
		default:
			return ( DefWindowProc( hWnd, msg, wp, lp ) );

	}

	// デフォルト処理
	return 0;
}

//////////////////////////////////////////////////////////////////////
//	CreateMainWindow
//		メインウィンドウの生成
//////////////////////////////////////////////////////////////////////
BOOL CreateMainWindow( HINSTANCE hInst, int nCmdShow )
{
	// ウィンドウクラスの登録
	if( !InitApp( hInst ) )
		return FALSE;

	// ウィンドウの生成
	if( !InitInstance( hInst, nCmdShow ) )
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//	InitApp
//		ウィンドウクラスの登録
//////////////////////////////////////////////////////////////////////
ATOM InitApp( HINSTANCE hInst )
{
	WNDCLASSEX	wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor( hInst, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	// ウィンドウクラスの登録	エラー時は0がかえる
	return	( RegisterClassEx( &wc ) );
}


//////////////////////////////////////////////////////////////////////
//	InitInstance
//		ウィンドウの生成
//////////////////////////////////////////////////////////////////////
BOOL InitInstance( HINSTANCE hInst, int nCmdShow )
{
	HWND hWnd;
	DWORD style = WS_OVERLAPPEDWINDOW;
	int width;
	int height;
	
	// ウィンドウサイズ調整
	RECT rect = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	AdjustWindowRect( &rect, style, FALSE );
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;


	// ウィンドウ生成
	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInst,
		NULL );

	// ウィンドウ生成に失敗
	if( !hWnd )
		return FALSE;

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
	return TRUE;
}



