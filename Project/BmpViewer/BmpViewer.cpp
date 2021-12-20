/*
2020.11.16 김경재, 우병택 공동 작업

*/

#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include "TCHAR.h"
#include "windowsx.h"
#include "commdlg.h"
#include "BTEngine.h"
#include "BTEngineDefine.h"
#include "BmpViewer.h"
#include "resource.h"

using namespace std;

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void LoadBitmapImage(TCHAR fileName[], HWND hwnd);

char* g_ClassName = "이미지 뷰어";
char* g_WindowName = "이미지 뷰어";

HINSTANCE gInst;

POINT g_ScreenSize;

float gScaleValue;
float gScaleX, gScaleY;
bool IsTransMode;

BTEngine* g_pBTEngine;
BTSprite* g_psprite;

HWND hWnd_Scale_X_Lb, hWnd_Scale_Y_Lb, hWnd_Scale_Lb;
HWND hWnd_Scale_X_Up, hWnd_Scale_X_Down, hWnd_Scale_Y_Up, hWnd_Scale_Y_Down;
HWND hWnd_Scale_Up, hWnd_Scale_Down, hWnd_Scale_Reset;
HWND hWnd_AlphaBlend, hWnd_Transparent;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;

	g_ScreenSize = {1080,1080};

	gScaleValue = 0.1f;
	gScaleX = 1;
	gScaleY = 1;

	gInst = hInstance;

	g_psprite = nullptr;

	//메인 윈도우 등록
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	RegisterClassEx(&wc);

	hWnd = CreateWindow(
		g_ClassName,
		g_WindowName,
		WS_OVERLAPPEDWINDOW,
		0, 0,
		g_ScreenSize.x + 300, g_ScreenSize.y,
		GetDesktopWindow(),
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	g_pBTEngine = new BTEngine();
	g_pBTEngine->Initialize(hInstance, hWnd, g_ScreenSize.x, g_ScreenSize.y);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) { break; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_pBTEngine->ClearMain();

			// 메인 루프
			if (g_psprite != nullptr)
			{
				if (IsTransMode == true)
				{
					g_pBTEngine->btDrawSpriteTransparent(g_psprite, 0, 0, gScaleX, gScaleY);
				}
				else 
				{
					g_pBTEngine->btDrawSpriteAlphablend(g_psprite, 0, 0, gScaleX, gScaleY, 1.0f);
				}
			}

			g_pBTEngine->Render();
		}
	}
	UnregisterClass(g_ClassName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[100], lpstrFile[100] = "";
	TCHAR filter[] = "Bmp(*.bmp)\0*.bmp\0";

	char buff[100];

	switch (msg)
	{
	case WM_CREATE:

		sprintf_s(buff, "%f", gScaleX);
		hWnd_Scale_X_Lb = CreateWindow("STATIC", "Scale X : ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 50, 75, 25, hwnd, (HMENU)IDC_Label, gInst, NULL);
		hWnd_Scale_X_Up = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 200, 50, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_X_UP, gInst, NULL);
		hWnd_Scale_X_Down = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 150, 50, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_X_DOWN, gInst, NULL);

		sprintf_s(buff, "%f", gScaleY);
		hWnd_Scale_Y_Lb = CreateWindow("STATIC", "Scale Y : ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 80, 75, 25, hwnd, (HMENU)IDC_Label, gInst, NULL);
		hWnd_Scale_Y_Up = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 200, 80, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_Y_UP, gInst, NULL);
		hWnd_Scale_Y_Down = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 150, 80, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_Y_DOWN, gInst, NULL);

		hWnd_Scale_Lb = CreateWindow("STATIC", "Scale ALL: ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 110, 75, 25, hwnd, (HMENU)IDC_Label, gInst, NULL);
		hWnd_Scale_Up = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 200, 110, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_UP, gInst, NULL);
		hWnd_Scale_Down = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 150, 110, 25, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_DOWN, gInst, NULL);

		hWnd_Scale_Reset = CreateWindow("button", "Reset All Scale", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 140, 150, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_RESET, gInst, NULL);

		hWnd_AlphaBlend = CreateWindow("button", "AlphaBlend Mode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 170, 150, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_ALPHA, gInst, NULL);
		hWnd_Transparent = CreateWindow("button", "TransParent Mode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_ScreenSize.x + 75, 200, 150, 25, hwnd, (HMENU)IDC_BUTTON_SCALE_TRANS, gInst, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			OPENFILENAME ofn;
			memset(&ofn, 0, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = filter;
			ofn.lpstrFile = lpstrFile;
			ofn.nMaxFile = 100;
			ofn.lpstrInitialDir = "../../4_Resources";
			if (GetOpenFileName(&ofn) != 0)
			{
				sprintf_s(str, "%s 파일을 열겠습니까?", ofn.lpstrFile);
				int res = MessageBox(hwnd, str, "열기 선택", MB_YESNO | MB_ICONQUESTION);
				if (res == IDNO)
				{
					return 0;
				}
				// 이미지 파일을 불러와서 출력한다.
				LoadBitmapImage(ofn.lpstrFile, hwnd);
			}
		}
		break;
		case IDC_BUTTON_SCALE_X_UP:
			gScaleX += gScaleValue;
			break;
		case IDC_BUTTON_SCALE_X_DOWN:
			gScaleX -= gScaleValue;
			break;
		case IDC_BUTTON_SCALE_Y_UP:
			gScaleY += gScaleValue;
			break;
		case IDC_BUTTON_SCALE_Y_DOWN:
			gScaleY -= gScaleValue;
			break;
		case IDC_BUTTON_SCALE_UP:
			gScaleX += gScaleValue;
			gScaleY += gScaleValue;
			break;
		case IDC_BUTTON_SCALE_DOWN:
			gScaleX -= gScaleValue;
			gScaleY -= gScaleValue;
			break;
		case IDC_BUTTON_SCALE_RESET:
			gScaleX = 1;
			gScaleY = 1;
			break;
		case IDC_BUTTON_SCALE_ALPHA:
			IsTransMode = false;
			break;
		case IDC_BUTTON_SCALE_TRANS:
			IsTransMode = true;
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
	{
		int res = MessageBox(hwnd, "프로그램을 종료할까요?", "프로그램 종료", MB_YESNO | MB_ICONQUESTION);
		if (res == IDNO)
		{
			return 0;
		}
	}
	break;
	case WM_DESTROY:

		delete g_pBTEngine;
		delete g_psprite;

		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void LoadBitmapImage(TCHAR fileName[], HWND hwnd)
{
	if (g_psprite == nullptr)
	{
		g_psprite = new BTSprite();
	}
	g_pBTEngine->btLoadSpriteFromFile(g_psprite, fileName);

	IsTransMode = true;
	gScaleX = 1;
	gScaleY = 1;
}