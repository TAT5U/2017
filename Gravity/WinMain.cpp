//////////////////////////////////////////////////////////////////////
// �d��
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

	// ���C���E�B���h�E�̐���
	if( !CreateMainWindow( hCurInst, nCmdShow ) )
		return 1;

/*	
	// ToDo::�Q�[������������
	
	// ���C�����b�Z�[�W���[�v
	do
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ToDo::�Q�[������
		}
	}while( msg.message != WM_QUIT );

	// ToDo::�Q�[���I������
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
//		�E�B���h�E�v���V�[�W��
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp )
{
	PAINTSTRUCT ps;
	HDC hdc;

	// ���b�Z�[�W����
	switch( msg )
	{
		// �E�B���h�E����
		case WM_CREATE:
			pBall = new Ball();
			pBall->Init( GAME_WIDTH / 2, 0, 0, 1, 9.8, 15 );			// ������
			SetTimer( hWnd, TIMER_ID, TIMER_INTERVAL, NULL );		// �^�C�}�[�Z�b�g
			break;

		// �^�C�}�[
		case WM_TIMER:
			pBall->Update();										// �X�V����
			InvalidateRect( hWnd, NULL, TRUE );						// �ĕ`�施��
			break;

		// �`��
		case WM_PAINT:
			hdc = BeginPaint( hWnd, &ps );
			pBall->Draw( hdc );										// �`�揈��
			EndPaint (hWnd, &ps );
			break;

		// �E�B���h�E�j��
		case WM_DESTROY:
			KillTimer( hWnd, TIMER_ID );							// �^�C�}�[�j��
			SAFE_DELETE( pBall );
			PostQuitMessage(0);
			break;

		// �f�t�H���g����
		default:
			return ( DefWindowProc( hWnd, msg, wp, lp ) );

	}

	// �f�t�H���g����
	return 0;
}

//////////////////////////////////////////////////////////////////////
//	CreateMainWindow
//		���C���E�B���h�E�̐���
//////////////////////////////////////////////////////////////////////
BOOL CreateMainWindow( HINSTANCE hInst, int nCmdShow )
{
	// �E�B���h�E�N���X�̓o�^
	if( !InitApp( hInst ) )
		return FALSE;

	// �E�B���h�E�̐���
	if( !InitInstance( hInst, nCmdShow ) )
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//	InitApp
//		�E�B���h�E�N���X�̓o�^
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

	// �E�B���h�E�N���X�̓o�^	�G���[����0��������
	return	( RegisterClassEx( &wc ) );
}


//////////////////////////////////////////////////////////////////////
//	InitInstance
//		�E�B���h�E�̐���
//////////////////////////////////////////////////////////////////////
BOOL InitInstance( HINSTANCE hInst, int nCmdShow )
{
	HWND hWnd;
	DWORD style = WS_OVERLAPPEDWINDOW;
	int width;
	int height;
	
	// �E�B���h�E�T�C�Y����
	RECT rect = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	AdjustWindowRect( &rect, style, FALSE );
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;


	// �E�B���h�E����
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

	// �E�B���h�E�����Ɏ��s
	if( !hWnd )
		return FALSE;

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
	return TRUE;
}



