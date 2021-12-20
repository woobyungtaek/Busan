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
	/// BT���� : �ʱ�ȭ 
	void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight);

	/// BT���� : All DC ������
	void Release(HINSTANCE hinst, HWND hWnd);

	/// BT���� : ���� 
	void Update();

	/// BT���� : ȭ�� �׸���
	void Render();

	void ClearMain();


public:
	/// BT���� : EngineTime
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
	/// BT���� : ȭ�� ũ��
	POINT ScreenSize;

	/// BT���� : ���콺 ��ġ
	POINT MousePositionSC;		//
	POINT MousePositionCT;		//

private:
	/// BT���� : �ڵ� ������
	HWND mhWnd;

	/// BT���� : Main Frame
	HDC mhMainDC;

	/// BT���� : Back Buffer
	HDC mhBackBufferDC;
	HBITMAP mhBackBufferBitMap;

	float mDeltaTime;
	static LARGE_INTEGER mStaticTime;	//���� Ŭ�� ��
	static LARGE_INTEGER mPrevTime;		//���� Ŭ�� ��
	static LARGE_INTEGER mCurrTime;		//���� Ŭ�� ��

	/// BT���� : Ű���� ����
	KeyState mKeyStateArr[256];

};