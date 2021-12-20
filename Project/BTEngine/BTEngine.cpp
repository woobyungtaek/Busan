// BTEngine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
#include "pch.h"

//BT엔진 : 선행선언
LARGE_INTEGER	BTEngine::mStaticTime;
LARGE_INTEGER	BTEngine::mPrevTime;
LARGE_INTEGER	BTEngine::mCurrTime;

BTEngine::BTEngine()
{

}

BTEngine::~BTEngine()
{

}

#pragma region 엔진 기본 함수
void BTEngine::Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight)
{
	mhWnd = hWnd;

	//화면 크기 저장
	ScreenSize.x = screenWidth;
	ScreenSize.y = screenHeight;

	//메인 프레임 
	mhMainDC = GetDC(hWnd);

	//BackBuffer
	mhBackBufferBitMap = CreateCompatibleBitmap(mhMainDC, ScreenSize.x, ScreenSize.y);
	mhBackBufferDC = CreateCompatibleDC(mhMainDC);

	SelectObject(mhBackBufferDC, mhBackBufferBitMap);

	//EngineTime
	QueryPerformanceFrequency(&mStaticTime);
}

void BTEngine::Release(HINSTANCE hinst, HWND hWnd)
{
	DeleteObject(mhBackBufferBitMap);

	ReleaseDC(hWnd, mhMainDC);
	ReleaseDC(hWnd, mhBackBufferDC);
}

void BTEngine::Update()
{
	btKeyUpdate();
	
	GetCursorPos(&MousePositionSC);
	MousePositionCT = MousePositionSC;
	ScreenToClient(mhWnd, &MousePositionCT);

}

void BTEngine::Render()
{
	/*char text[80];
	sprintf_s(text, "%f", GetDeltaTime());
	TextOut(mhBackBufferDC, 0, 0, text, (int)strlen(text));

	sprintf_s(text, "ScreenMouse : (%d, %d)", mMousePostionSC.x, mMousePostionSC.y);
	TextOut(mhBackBufferDC, 0, 16, text, (int)strlen(text));
	sprintf_s(text, "ClientMouse : (%d, %d)", mMousePostionCT.x, mMousePostionCT.y);
	TextOut(mhBackBufferDC, 0, 32, text, (int)strlen(text));*/

	//btTextOut(0, 0, "%d , %d", MousePositionCT.x, MousePositionCT.y);
	// BT엔진 : 화면 그리기
	BitBlt(mhMainDC, 0, 0, ScreenSize.x, ScreenSize.y, mhBackBufferDC, 0, 0, SRCCOPY);
}

void BTEngine::ClearMain()
{
	// BT엔진 : BackBuffer 초기화
	HBRUSH hBrush = CreateSolidBrush(RGB(88, 88, 88));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(mhBackBufferDC, hBrush);
	Rectangle(mhBackBufferDC, -1, -1, (int)ScreenSize.x + 1, (int)ScreenSize.y + 1);
	SelectObject(mhBackBufferDC, hOldBrush);
	DeleteObject(hBrush);
}
#pragma endregion

#pragma region 엔진 정보 함수
void BTEngine::SetEngineTime()
{
	//현재 클럭 수
	QueryPerformanceCounter(&mCurrTime);

	//DeltaTime 계산
	float elapseTime = (float)mCurrTime.QuadPart - (float)mPrevTime.QuadPart;
	mDeltaTime = elapseTime / (float)mStaticTime.QuadPart;

	//union 하나의 구조체로 여러개를 표현하고 싶을때
	//왜 나누어 쓰는가
	//mCurrTime.u.LowPart
	//mCurrTime.u.HighPart
	//mCurrTime.LowPart
	//mCurrTime.HighPart
	//mCurrTime.QuadPart

	//이전 값 설정
	mPrevTime = mCurrTime;
}
#pragma endregion

#pragma region 엔진 BitMap 함수
void BTEngine::btLoadSpriteFromFile(BTSprite* sprite, char* filePath)
{
	// 스프라이트 메모리 DC
	sprite->hMemDC = CreateCompatibleDC(mhMainDC);

	//비트맵 로드(비트맵 핸들)
	sprite->hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SelectObject(sprite->hMemDC, sprite->hBitmap);

	BITMAP _bitmap;
	GetObject(sprite->hBitmap, sizeof(BITMAP), &_bitmap);

	sprite->Width = _bitmap.bmWidth;
	sprite->Height = _bitmap.bmHeight;

	DeleteObject(sprite->hBitmap);
}

void BTEngine::btDrawSprite(BTSprite* sprite, int x, int y)
{
	BitBlt(
		mhBackBufferDC,
		x, y,
		sprite->Width, sprite->Height,
		sprite->hMemDC,
		0, 0,
		SRCCOPY);
}

void BTEngine::btDrawSpriteScale(BTSprite* sprite, int x, int y, float sx, float sy)
{
	StretchBlt(
		mhBackBufferDC,
		x, y,
		sprite->Width * sx, sprite->Height * sy,
		sprite->hMemDC,
		0, 0,
		sprite->Width, sprite->Height,
		SRCCOPY);
}

void BTEngine::btDrawSpriteTransparent(BTSprite* sprite, int x, int y, float sx, float sy)
{
	TransparentBlt(
		mhBackBufferDC,
		x, y,
		sprite->Width * sx, sprite->Height * sy,
		sprite->hMemDC,
		0, 0,
		sprite->Width, sprite->Height,
		RGB(255, 0, 255));
}

void BTEngine::btDrawSpriteAlphablend(BTSprite* sprite, int x, int y, float sx, float sy, float alpha)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(255 * alpha);
	bf.AlphaFormat = AC_SRC_ALPHA; // 알파채널이 있는 경우

	AlphaBlend(mhBackBufferDC, x, y, sprite->Width * sx, sprite->Height * sy, sprite->hMemDC, 0, 0, sprite->Width, sprite->Height, bf);
}

void BTEngine::btLoadAniSpriteFromFile(BTAniSprite* aniSprite, bool IsAlphaBlend, char* filePath, int cellSizeX, int cellSizeY)
{
	btLoadSpriteFromFile(aniSprite, filePath);
	aniSprite->InitAniSprite(&mhBackBufferDC , IsAlphaBlend, cellSizeX, cellSizeY);
}

void BTEngine::btLoadScrollSprite(BTScrollObject* scroolSprite, BTSprite* sprite, bool IsAlphaBlend)
{
	scroolSprite->InitScrollSprite(&mhBackBufferDC, sprite, IsAlphaBlend);
}

#pragma endregion

#pragma region 엔진 기본 Draw 함수
void BTEngine::btTextOut(int x, int y, const char* pch, ...)
{
	SetBkMode(mhBackBufferDC, TRANSPARENT);

	char* buffer;
	int len;

	va_list ap;
	va_start(ap, pch);
	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];
	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	//SetTextAlign(mhBackBufferDC, TA_CENTER);
	//SetTextColor(mhBackBufferDC, color);

	TextOut(mhBackBufferDC, x, y, buffer, (int)strlen(buffer));

	delete[] buffer;
}

void BTEngine::btTextOutSize(int x, int y, int size, COLORREF color ,const char* pch, ...)
{
	SetBkMode(mhBackBufferDC, TRANSPARENT);

	char* buffer;
	int len;
	
	va_list ap;
	va_start(ap, pch);
	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];
	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	HFONT font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Neo둥근모"));
	HFONT oldfont = (HFONT)SelectObject(mhBackBufferDC, font);
	//SetTextAlign(mhBackBufferDC, TA_CENTER);
	SetTextColor(mhBackBufferDC, color);

	TextOut(mhBackBufferDC, x, y, buffer, (int)strlen(buffer));

	delete[] buffer;
	SelectObject(mhBackBufferDC, oldfont);
	DeleteObject(font);
}

void BTEngine::btDrawText(int left, int top, int right, int bottom, int fontSize, int weight, int alig ,COLORREF color, const char* pch, ...)
{
	SetBkMode(mhBackBufferDC, TRANSPARENT);

	char* buffer;
	int len;

	va_list ap;
	va_start(ap, pch);
	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];
	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	RECT rc;
	SetRect(&rc, left, top, left + right, top + bottom);
	HFONT font = CreateFont(fontSize, 0, 0, 0, weight, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH  |FF_ROMAN, TEXT("Neo둥근모"));
	HFONT oldfont = (HFONT)SelectObject(mhBackBufferDC, font);
	SetTextColor(mhBackBufferDC, color);

	DrawText(mhBackBufferDC, buffer, (int)strlen(buffer), &rc, alig | DT_EXTERNALLEADING | DT_WORDBREAK);

	SetTextColor(mhBackBufferDC, RGB(0,0,0));
	delete[] buffer;
	SelectObject(mhBackBufferDC, oldfont);
	DeleteObject(font);
}

void BTEngine::btDrawText(RECT rect, int fontSize, int weight, int alig, COLORREF color, const char* pch, ...)
{
	char* buffer;
	int len;

	va_list ap;
	va_start(ap, pch);
	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];
	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	HFONT font = CreateFont(fontSize, 0, 0, 0, weight, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Neo둥근모"));
	HFONT oldfont = (HFONT)SelectObject(mhBackBufferDC, font);
	SetTextColor(mhBackBufferDC, color);

	DrawText(mhBackBufferDC, buffer, (int)strlen(buffer), &rect, alig | DT_EXTERNALLEADING | DT_WORDBREAK);

	SetTextColor(mhBackBufferDC, RGB(0, 0, 0));
	delete[] buffer;
	SelectObject(mhBackBufferDC, oldfont);
	DeleteObject(font);
}

void BTEngine::btDrawLine(int sx, int sy, int ex, int ey, COLORREF edgeColor)
{
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, edgeColor);
	HPEN hOldPen = (HPEN)SelectObject(mhBackBufferDC, hPen);

	MoveToEx(mhBackBufferDC, sx, sy, NULL);
	LineTo(mhBackBufferDC, ex, ey);

	SelectObject(mhBackBufferDC, hOldPen);
	DeleteObject(hPen);
}

void BTEngine::btDrawRect(int left, int top, int right, int bottom, COLORREF edgeColor)
{
	//기본색 : 검정 테두리 / 채우기 없음 
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(mhBackBufferDC, hBrush);
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, edgeColor);
	HPEN hOldPen = (HPEN)SelectObject(mhBackBufferDC, hPen);

	Rectangle(mhBackBufferDC, left, top, right, bottom);

	SelectObject(mhBackBufferDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(mhBackBufferDC, hOldBrush);
	DeleteObject(hBrush);
}

void BTEngine::btDrawRect(RECT rect, COLORREF edgeColor)
{
	//기본색 : 검정 테두리 / 채우기 없음 
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(mhBackBufferDC, hBrush);
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, edgeColor);
	HPEN hOldPen = (HPEN)SelectObject(mhBackBufferDC, hPen);

	Rectangle(mhBackBufferDC, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(mhBackBufferDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(mhBackBufferDC, hOldBrush);
	DeleteObject(hBrush);
}

void BTEngine::btDrawFillRect(int left, int top, int right, int bottom, COLORREF edgeColor, COLORREF fillColor)
{
	HBRUSH hBrush =		(HBRUSH)CreateSolidBrush(fillColor);
	HBRUSH hOldBrush =	(HBRUSH)SelectObject(mhBackBufferDC, hBrush);
	HPEN hPen =			(HPEN)CreatePen(PS_SOLID, 1, edgeColor);
	HPEN hOldPen =		(HPEN)SelectObject(mhBackBufferDC, hPen);

	Rectangle(mhBackBufferDC, left, top, right, bottom);

	SelectObject(mhBackBufferDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(mhBackBufferDC, hOldBrush);
	DeleteObject(hBrush);
}

void BTEngine::btDrawEllipse(int left, int top, int right, int bottom, COLORREF edgeColor)
{
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(mhBackBufferDC, hBrush);
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, edgeColor);
	HPEN hOldPen = (HPEN)SelectObject(mhBackBufferDC, hPen);

	Ellipse(mhBackBufferDC, left, top, right, bottom);

	SelectObject(mhBackBufferDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(mhBackBufferDC, hOldBrush);
	DeleteObject(hBrush);
}
#pragma endregion

#pragma region 엔진 입력 함수
//배열로 모든 키의 이전 상태를 체크
void BTEngine::btKeyUpdate()
{
	for (int index = 0; index < 255; index++)
	{
		mKeyStateArr[index].prev	= mKeyStateArr[index].current;
		mKeyStateArr[index].current = HIWORD(GetAsyncKeyState(index));
	}
}

bool BTEngine::btInputKey(int vk)
{
	return mKeyStateArr[vk].current;
}

bool BTEngine::btInputKeyDown(int vk)
{
	return !mKeyStateArr[vk].prev && mKeyStateArr[vk].current;
}

bool BTEngine::btInputKeyUp(int vk)
{
	return mKeyStateArr[vk].prev && !mKeyStateArr[vk].current;
}

#pragma endregion
