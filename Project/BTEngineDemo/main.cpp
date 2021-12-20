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

char* g_ClassName = "병택엔진 데모";
char* g_ChildName = "자식 윈도우";
char* g_WindowName = "병택엔진 데모";
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

	//메인 윈도우 등록
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

	////팝업 윈도우 등록
	////팝업의 종류에 따라 Proc가 달라진다.
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

	//BT엔진 : 사용할 엔진
	BTEngine* pBTEngine = new BTEngine();
	pBTEngine->Initialize(hInstance, hWnd, g_ScreenSize.x, g_ScreenSize.y);

	//테스트용 스프라이트
	BTSprite sprite;
	pBTEngine->btLoadSpriteFromFile(&sprite, "../Data/Circlebutton.bmp");

	//테스트용 애니메이션
	BTAniSprite pAniSprite;
	pBTEngine->btLoadAniSpriteFromFile(&pAniSprite, false, "../Data/enemies.bmp", 32, 32);
	pAniSprite.SetAnimation(1, 1, 3, 9, -1);

	//테스트용 화면스크롤
	BTSprite sprite2;
	pBTEngine->btLoadSpriteFromFile(&sprite2, "../Data/Title_Test1_BMP.bmp");
	BTScrollObject scrollSprite;
	pBTEngine->btLoadScrollSprite(&scrollSprite, &sprite2, true);
	scrollSprite.SetScroll(800, 0, 0, 0.8, 0.8, 1, 1);

	//테스트용 충돌박스
	BTGameObject GameObject;
	GameObject.Initialize( 300, 300, 200, 200);

	// 테스트용 사운드 매니저
	SoundManager Sound;
	Sound.Initiate(hWnd);
	Sound.DataLoad_WAV(MediaFileName[Sound.mTrackNum]);
	Sound.DataLoad_MP3(MediaFileName[BUSSTOP]);

	//BTSprite sprite2;
	//pBTEngine->btLoadSpriteFromFile(&sprite2, "../Data/enemies.bmp");

	//타이머
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

			//BT엔진 : Update
			pBTEngine->Update();

			//GameDemo : Update
			pBTEngine->ClearMain();
			
			scrollSprite.PlayScroll(dTime);

			/// 그리기
			// 스프라이트 그리기
			//pBTEngine->btDrawSprite(&sprite, 0, 0);

			// 스프라이트 스케일 조절
			//pBTEngine->btDrawSpriteScale(&sprite2, 0, 0, 20, 20);
			//pBTEngine->btDrawSpriteScale(&sprite, 150, 150, 1, 1);

			// 트랜스페어런트, 알파 블렌드
			pBTEngine->btDrawSpriteTransparent(&pAniSprite, 200, 500, 1, 1);
			//pBTEngine->btDrawSpriteAlphablend(&sprite, 400, 400, 1, 1, 1.f);

			// 각종 도형 그리기
			//pBTEngine->btDrawLine(300, 300, 350, 370, RGB(255, 80, 7));
			//pBTEngine->btDrawRect(move.x, move.y, 50 + move.x, 50 + move.y, RGB(90, 255, 90));
			//pBTEngine->btDrawEllipse(300, 300, 350, 370, RGB(255, 0, 255));
			//pBTEngine->btTextOut(move.x, move.y, "(%d,%d)", move.x, move.y);

			//애니메이션 테스트
			//pBTEngine->btAnimation(&aniSprite, dTime);
			pAniSprite.PlayAnimation(dTime, 300, 300, 1,1);
			
			//pAniSprite.SetAniFrame(dTime);

			//화면 스크롤 테스트

			//마우스 collision 테스트
			if (pBTEngine->btInputKeyDown(VK_LBUTTON))
			{
				POINT cursorPos = pBTEngine->MousePositionCT;
				GameObject.IsCollided(cursorPos);
				// cursorPos가 버튼(collidor)의 바운더리 안에 있는지 체크
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

			pBTEngine->btTextOut(40, 40, "마우스 커서 위치 : %d, %d", pBTEngine->MousePositionCT.x, pBTEngine->MousePositionCT.y);

			// 사운드 테스트
			Sound.Update(dTime);		// 볼륨조절시 필요

			// 0~8번 선택
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
			Sound.Volume();				// 볼륨 조절 + Q, - W

			//BT엔진 : Render
			pBTEngine->Render();
		}
	}

	//BT엔진 : Release
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
		//아주 간단한 Popup... 어떻게 써먹어야할지...
		HWND hPopup = CreateWindow(
			g_ChildName,
			"팝업윈도우",
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
		//	"팝업윈도우2",
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
		int res = MessageBox(hwnd, "프로그램을 종료할까요? FrameMsgProc", "프로그램 종료", MB_YESNO | MB_ICONQUESTION);
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