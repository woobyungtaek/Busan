#pragma once
/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
 //
#define FPS(v) (1.0f/(float)v)

#pragma region VK 키
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
#pragma endregion

class BTEngine;

// 스프라이트 클래스
class BTSprite
{
public:
	BTSprite();
	~BTSprite();

	//비트맵 핸들
	HBITMAP hBitmap;

	//메모리 DC
	HDC hMemDC;

	int Width;
	int Height;
};

// 애니메이션 클래스
class BTAniSprite : public BTSprite
{
public:
	BTAniSprite();
	~BTAniSprite();

private:
	int loopCount;
	int currLoopCount;

	int mCellSizeX, mCellSizeY;

	int mCellCountX,  mCellCountY;

	int mStartIdx, mEndIdx;

	int mPlayCount;

	bool mbAlphaBlend;

	float	mAniSpeed;
	float	anitime;
	int		aniframe;

	BLENDFUNCTION mBF;
	HDC* mDrawDC;

public :
	void InitAniSprite(HDC* backDC, bool IsAlphaBlend, int cellSizeX, int cellSizeY);
	void SetAnimation(float speed, float alpha, int start, int end, int loop);

	void PlayAnimation(float dtime, int x, int y, float scaleX, float scaleY);
};

class BTScrollData
{
public : 
	float speed;
	int x, y;
	float scaleX, scaleY;
	float alpha;
	int dirX = 1;
};

class BTScrollObject
{
public:
	BTScrollObject();
	~BTScrollObject();

private :
	BTSprite* mpSprite;

	BLENDFUNCTION mBF;
	HDC* mDrawDC;

	float mSpeed;
	float mOffset;

	int	  mPosX,   mPosY;
	float	  mSizeX,  mSizeY;

	int	  mDirX,  mDirY;
	bool  mbAlphaBlend;

public:
	void InitScrollSprite(HDC* backDC, BTSprite* pSprite, bool IsAlphaBlend);
	void SetScroll(float speed, int x, int y, float scaleX, float scaleY, float alpha, int dirX);
	void SetScroll(BTScrollData scrollData);
	void PlayScroll(float dtime);
};

// 게임오브젝트 클래스
class BTGameObject
{
public:
	BTGameObject();
	~BTGameObject();

public:
	RECT object;

	bool m_IsCollided = false;

public:
	void Initialize(int left, int top, int right, int bottom);
	bool IsCollided(POINT cursorPos);
};