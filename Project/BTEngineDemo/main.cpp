//#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include "windowsx.h"
#include "BTEngineDefine.h"
#include "BTEngine.h"
#include "SoundManager.h"
#include "CTimeController.h"

using namespace std;

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PopupMsgProc(HWND, UINT, WPARAM, LPARAM);

char* g_ClassName = "���ÿ��� ����";
char* g_ChildName = "�ڽ� ������";
char* g_WindowName = "���ÿ��� ����";
POINT g_ScreenSize;

HINSTANCE ghInst;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;

	ghInst = hInstance;
	g_ScreenSize.x = 1920;
	g_ScreenSize.y = 1080;

	//���� ������ ���
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainMsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghInst;
	wc.hIcon = LoadIcon(ghInst, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	RegisterClassEx(&wc);

	////�˾� ������ ���
	////�˾��� ������ ���� Proc�� �޶�����.
	//wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//wc.lpfnWndProc = (WNDPROC)PopupMsgProc;
	//wc.lpszClassName = g_ChildName;
	//RegisterClassEx(&wc);

	hWnd = CreateWindow(
		g_ClassName,
		"Main Window Title",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		g_ScreenSize.x, g_ScreenSize.y,
		GetDesktopWindow(),
		NULL,
		ghInst,
		NULL
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//BT���� : ����� ����
	BTEngine* pBTEngine = new BTEngine();
	pBTEngine->Initialize(hInstance, hWnd, g_ScreenSize.x, g_ScreenSize.y);

	//�׽�Ʈ�� ��������Ʈ
	BTSprite sprite;
	pBTEngine->btLoadSpriteFromFile(&sprite, "../Data/Circlebutton.bmp");

	//�׽�Ʈ�� �ִϸ��̼�
	BTAniSprite pAniSprite;
	pBTEngine->btLoadAniSpriteFromFile(&pAniSprite, false, "../Data/enemies.bmp", 32, 32);
	pAniSprite.SetAnimation(1, 1, 3, 9, -1);

	//�׽�Ʈ�� ȭ�齺ũ��
	BTSprite sprite2;
	pBTEngine->btLoadSpriteFromFile(&sprite2, "../Data/Title_Test1_BMP.bmp");
	BTScrollObject scrollSprite;
	pBTEngine->btLoadScrollSprite(&scrollSprite, &sprite2, true);
	scrollSprite.SetScroll(800, 0, 0, 0.8, 0.8, 1, 1);

	//�׽�Ʈ�� �浹�ڽ�
	BTGameObject GameObject;
	GameObject.Initialize( 300, 300, 200, 200);

	// �׽�Ʈ�� ���� �Ŵ���
	SoundManager Sound;
	Sound.Initiate(hWnd);
	Sound.DataLoad_WAV(MediaFileName[Sound.mTrackNum]);
	Sound.DataLoad_MP3(MediaFileName[BUSSTOP]);

	//BTSprite sprite2;
	//pBTEngine->btLoadSpriteFromFile(&sprite2, "../Data/enemies.bmp");

	//Ÿ�̸�
	//CTimeController* timer = new CTimeController();
	//timer->Initialize();

	float speed = 100.f;
	POINT move;
	move.x = 0;
	move.y = 0;
	
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
			pBTEngine->SetEngineTime();
			float dTime = pBTEngine->GetDeltaTime();

			//if (pBTEngine->btInputKey(VK_SPACE)) { move.x -= (speed * dTime); }
			//if (IsKeyDown(VK_S)) { move.y += (speed * dTime); }
			//if (IsKeyDown(VK_D)) { move.x += (speed * dTime); }
			//if (IsKeyDown(VK_W)) { move.y -= (speed * dTime); }

			//BT���� : Update
			pBTEngine->Update();

			//GameDemo : Update
			pBTEngine->ClearMain();
			
			scrollSprite.PlayScroll(dTime);

			/// �׸���
			// ��������Ʈ �׸���
			//pBTEngine->btDrawSprite(&sprite, 0, 0);

			// ��������Ʈ ������ ����
			//pBTEngine->btDrawSpriteScale(&sprite2, 0, 0, 20, 20);
			//pBTEngine->btDrawSpriteScale(&sprite, 150, 150, 1, 1);

			// Ʈ������Ʈ, ���� ����
			pBTEngine->btDrawSpriteTransparent(&pAniSprite, 200, 500, 1, 1);
			//pBTEngine->btDrawSpriteAlphablend(&sprite, 400, 400, 1, 1, 1.f);

			// ���� ���� �׸���
			//pBTEngine->btDrawLine(300, 300, 350, 370, RGB(255, 80, 7));
			//pBTEngine->btDrawRect(move.x, move.y, 50 + move.x, 50 + move.y, RGB(90, 255, 90));
			//pBTEngine->btDrawEllipse(300, 300, 350, 370, RGB(255, 0, 255));
			//pBTEngine->btTextOut(move.x, move.y, "(%d,%d)", move.x, move.y);

			//�ִϸ��̼� �׽�Ʈ
			//pBTEngine->btAnimation(&aniSprite, dTime);
			pAniSprite.PlayAnimation(dTime, 300, 300, 1,1);
			
			//pAniSprite.SetAniFrame(dTime);

			//ȭ�� ��ũ�� �׽�Ʈ

			//���콺 collision �׽�Ʈ
			if (pBTEngine->btInputKeyDown(VK_LBUTTON))
			{
				POINT cursorPos = pBTEngine->MousePositionCT;
				GameObject.IsCollided(cursorPos);
				// cursorPos�� ��ư(collidor)�� �ٿ���� �ȿ� �ִ��� üũ
			}
			if (GameObject.m_IsCollided == true)
			{
				pBTEngine->btDrawRect(GameObject.object.left, GameObject.object.top, 
					GameObject.object.right, GameObject.object.bottom, RGB(255, 0, 255));
			}
			else
			{
				pBTEngine->btDrawRect(GameObject.object.left, GameObject.object.top,
					GameObject.object.right, GameObject.object.bottom, RGB(255, 255, 255));
			}

			pBTEngine->btTextOut(40, 40, "���콺 Ŀ�� ��ġ : %d, %d", pBTEngine->MousePositionCT.x, pBTEngine->MousePositionCT.y);

			// ���� �׽�Ʈ
			Sound.Update(dTime);		// ���������� �ʿ�

			// 0~8�� ����
			//Sound.PlayWAV1(OPENING);
			//Sound.PlayWAV1(TITLE);
			//Sound.PlayWAV1(BUSSTOP);
			Sound.PlayWAV1(MINIGAME);
			//Sound.PlayWAV1(GAMEOVER);
			//Sound.PlayWAV1(ENDING1);
			//Sound.PlayWAV1(ENDING2);
			//Sound.PlayWAV1(ENDING3);
			//Sound.PlayWAV1(ENDING4);

			//Sound.PlayWAV2(OPENING);
			//Sound.PlayMP3();
			Sound.Volume();				// ���� ���� + Q, - W

			//BT���� : Render
			pBTEngine->Render();
		}
	}

	//BT���� : Release
	pBTEngine->Release(hInstance, hWnd);
	Sound.DataRelease();
	Sound.Release(hWnd);
	UnregisterClass(g_ClassName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//���� ������ Popup... ��� ��Ծ������...
		HWND hPopup = CreateWindow(
			g_ChildName,
			"�˾�������",
			WS_POPUPWINDOW | WS_CAPTION
			, 100, 100, 320, 480,
			hwnd,
			(HMENU)NULL,
			ghInst,
			NULL
		);
		//ShowWindow(hPopup, SW_SHOW);		
		//hPopup = CreateWindow(
		//	g_ChildName,
		//	"�˾�������2",
		//	WS_POPUPWINDOW | WS_CAPTION
		//	, 100, 100, 320, 480,
		//	hwnd,
		//	(HMENU)NULL,
		//	ghInst,
		//	NULL
		//);
		ShowWindow(hPopup, SW_SHOW);
		//CreateWindow(g_ChildName, "Child Window", WS_POPUP|WS_CAPTION | WS_VISIBLE, 20, 20, 150, 30, hwnd, (HMENU)NULL, ghInst, NULL);
	}
	break;
	case WM_CLOSE:
	{
		int res = MessageBox(hwnd, "���α׷��� �����ұ��? FrameMsgProc", "���α׷� ����", MB_YESNO | MB_ICONQUESTION);
		if (res == IDNO)
		{
			return 0;
		}
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
		int res = MessageBox(hwnd, "���α׷��� �����ұ��?MsgProc", "���α׷� ����", MB_YESNO | MB_ICONQUESTION);
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