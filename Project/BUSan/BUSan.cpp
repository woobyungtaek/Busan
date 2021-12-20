#include "pch.h"
#include <crtdbg.h>

using namespace std;

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PopupMsgProc(HWND, UINT, WPARAM, LPARAM);

char* g_ClassName = "BUSan";
char* g_ChildName = "BUSan Watch";
char* g_WindowName = "BUSan";

//POINT g_ScreenSize;

//HINSTANCE ghInst;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;

	HINSTANCE hInst = hInstance;
	POINT screenSize;
	screenSize.x = 1920 * 0.8;
	screenSize.y = 1080 * 0.8;

	//메인 윈도우 등록
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainMsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	RegisterClassEx(&wc);

	////팝업 윈도우 등록
	////팝업의 종류에 따라 Proc가 달라진다.

	//wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//wc.lpfnWndProc = (WNDPROC)PopupMsgProc;
	//wc.lpszClassName = g_ChildName;
	//RegisterClassEx(&wc);

	hWnd = CreateWindow(
		g_ClassName,
		"BUSan~!",
		WS_OVERLAPPED | WS_SYSMENU,
		0, 0,
		screenSize.x + 16, screenSize.y + 39,
		GetDesktopWindow(),
		NULL,
		hInst,
		NULL
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//_CrtSetBreakAlloc(155);

	//BT엔진 : 사용할 엔진
	BTEngine* pBTEngine = new BTEngine();
	pBTEngine->Initialize(hInstance, hWnd, screenSize.x, screenSize.y);

	//GameManager : 게임 매니저
	GameManager* pGameManager = new GameManager();
	pGameManager->InitGameManager(pBTEngine, hWnd);

	int gameState = GS_GO;

	while (gameState)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			pBTEngine->SetEngineTime();

			////BT엔진 : ClearMain
			pBTEngine->ClearMain();

			////BT엔진 : Update
			pBTEngine->Update();

			//GameManager : GameLoop
			pGameManager->TestKeyUpdate();
			gameState = pGameManager->GameLoop();
			//pGameManager->ShowTestInfo();

			////BT엔진 : Render
			pBTEngine->Render();
		}
	}

	//BT엔진 : Release
	pGameManager->ReleaseAll(hWnd);
	pBTEngine->Release(hInstance, hWnd);

	delete pGameManager;
	delete pBTEngine;

	UnregisterClass(g_ClassName, wc.hInstance);
	//_CrtDumpMemoryLeaks();
	return 0;
}

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SHOWWINDOW:
		RECT rc;
		POINT p1, p2;

		GetClientRect(hwnd, &rc);					// 클라이언트 영역

		// 클라이언트 크기를 좌표로 변환
		p1.x = rc.left;
		p1.y = rc.top;
		p2.x = rc.right;
		p2.y = rc.bottom;

		// 클라이언트 크기를 스크린 크기로 변환
		ClientToScreen(hwnd, &p1);
		ClientToScreen(hwnd, &p2);

		//int offset = GetSystemMetrics(SM_CYMENU);	// 타이틀 바 크기

		rc.left = p1.x;
		rc.top = p1.y - 37;
		rc.right = p2.x;
		rc.bottom = p2.y;

		// 해당좌표를 기준으로 커서를 고정
		ClipCursor(&rc);

	case WM_CREATE:
	{
		//아주 간단한 Popup... 어떻게 써먹어야할지...
		//HWND hPopup = CreateWindow(
		//	g_ChildName,
		//	"팝업윈도우",
		//	WS_POPUPWINDOW | WS_CAPTION
		//	, 100, 100, 320, 480,
		//	hwnd,
		//	(HMENU)NULL,
		//	ghInst,
		//	NULL
		//);
		//ShowWindow(hPopup, SW_SHOW);		

		//hPopup = CreateWindow(
		//	g_ChildName,
		//	"팝업윈도우2",
		//	WS_POPUPWINDOW | WS_CAPTION
		//	, 100, 100, 320, 480,
		//	hwnd,
		//	(HMENU)NULL,
		//	ghInst,
		//	NULL
		//);

		//ShowWindow(hPopup, SW_SHOW);
		//CreateWindow(g_ChildName, "Child Window", WS_POPUP|WS_CAPTION | WS_VISIBLE, 20, 20, 150, 30, hwnd, (HMENU)NULL, ghInst, NULL);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK PopupMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		int res = MessageBox(hwnd, "프로그램을 종료할까요?MsgProc", "프로그램 종료", MB_YESNO | MB_ICONQUESTION);
		if (res == IDNO)
		{
			return 0;
		}
	}
	break;
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}