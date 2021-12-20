#pragma once
class BTSprite;
class BTAniSprite;
class BTScrollData;
class BTScrollObject;

class KeyState
{
public:
	KeyState() : current(false), prev(false) {};
	~KeyState() {};

public:
	bool current;
	bool prev;
};

class BTEngine
{
public:
	BTEngine();
	~BTEngine();
public:
	/// BT엔진 : 초기화 
	void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight);

	/// BT엔진 : All DC 릴리즈
	void Release(HINSTANCE hinst, HWND hWnd);

	/// BT엔진 : 동작 
	void Update();

	/// BT엔진 : 화면 그리기
	void Render();

	void ClearMain();


public:
	/// BT엔진 : EngineTime
	void SetEngineTime();
	float GetDeltaTime() { return mDeltaTime; }

public:
	void btLoadSpriteFromFile(BTSprite* sprite, char* filePath);

	void btDrawSprite(BTSprite* sprite, int x, int y);
	void btDrawSpriteScale(BTSprite* sprite, int x, int y, float sx, float sy);
	void btDrawSpriteTransparent(BTSprite* sprite, int x, int y, float sx, float sy);
	void btDrawSpriteAlphablend(BTSprite* sprite, int x, int y, float sx, float sy, float alpha);

	void btLoadAniSpriteFromFile(BTAniSprite* aniSprite, bool IsAlphaBlend, char* filePath, int cellSizeX, int cellSizeY);

	void btLoadScrollSprite(BTScrollObject* scroolSprite, BTSprite* sprite, bool IsAlphaBlend);

	void btTextOut(int x, int y, const char* pch, ...);
	void btTextOutSize(int x, int y, int size, COLORREF color, const char* pch, ...);
	void btDrawText(int x, int y, int sx, int sy, int fontSize, int weight, int alig, COLORREF color, const char* pch, ...);
	void btDrawText(RECT rect, int fontSize, int weight, int alig, COLORREF color, const char* pch, ...);
	void btDrawLine(int sx, int sy, int ex, int ey, COLORREF edgeColor);
	void btDrawRect(int left, int top, int right, int bottom, COLORREF edgeColor);
	void btDrawRect(RECT rect, COLORREF edgeColor);
	void btDrawFillRect(int left, int top, int right, int bottom, COLORREF edgeColr, COLORREF fillColor);
	void btDrawEllipse(int left, int top, int right, int bottom, COLORREF edgeColor);

public:
	void btKeyUpdate();
	bool btInputKey(int vk);
	bool btInputKeyDown(int vk);
	bool btInputKeyUp(int vk);

public:
	/// BT엔진 : 화면 크기
	POINT ScreenSize;

	/// BT엔진 : 마우스 위치
	POINT MousePositionSC;		//
	POINT MousePositionCT;		//

private:
	/// BT엔진 : 핸들 윈도우
	HWND mhWnd;

	/// BT엔진 : Main Frame
	HDC mhMainDC;

	/// BT엔진 : Back Buffer
	HDC mhBackBufferDC;
	HBITMAP mhBackBufferBitMap;

	float mDeltaTime;
	static LARGE_INTEGER mStaticTime;	//성능 클럭 수
	static LARGE_INTEGER mPrevTime;		//이전 클럭 수
	static LARGE_INTEGER mCurrTime;		//현재 클럭 수

	/// BT엔진 : 키보드 상태
	KeyState mKeyStateArr[256];

};