#include "pch.h"

#pragma region Basic Sprite

BTSprite::BTSprite()
{
}

BTSprite::~BTSprite()
{

}
#pragma endregion

#pragma region Animation Sprite

BTAniSprite::BTAniSprite()
{
	loopCount = 0;

	mCellSizeX = 0;
	mCellSizeY = 0;

	anitime = 0.f;
	aniframe = 0;

	mPlayCount = 0;
}

BTAniSprite::~BTAniSprite()
{

}

///积己 矫 汲沥
void BTAniSprite::InitAniSprite(HDC* backDC, bool IsAlphaBlend, int cellSizeX, int cellSizeY)
{
	mbAlphaBlend = IsAlphaBlend;

	mDrawDC = backDC;

	mCellSizeX = cellSizeX;
	mCellSizeY = cellSizeY;

	mCellCountX = Width / cellSizeX;
	mCellCountY = Height / cellSizeX;
}

///犁积 傈 汲沥
void BTAniSprite::SetAnimation(float speed, float alpha, int start, int end, int loop = -1)
{
	mAniSpeed = speed;

	mStartIdx = start;
	mEndIdx = end;


	mPlayCount = end - start + 1;

	aniframe = start;

	loopCount = loop;
	currLoopCount = 0;

	mBF.BlendOp = AC_SRC_OVER;
	mBF.BlendFlags = 0;
	mBF.SourceConstantAlpha = (BYTE)(255 * alpha);
	mBF.AlphaFormat = AC_SRC_ALPHA;
}

///犁积
void BTAniSprite::PlayAnimation(float dtime, int x, int y, float scaleX, float scaleY)
{
	if (loopCount > 0)
	{
		if (currLoopCount >= loopCount)
		{
			aniframe = mStartIdx;
			return;
		}
	}

	anitime += dtime;
	if (anitime > FPS(mAniSpeed))
	{
		anitime = 0.0f;
		aniframe++;
		if (aniframe > mEndIdx)
		{
			aniframe = mStartIdx;
			currLoopCount += 1;
		}
	}

	int poxX = (aniframe % mCellCountX) * mCellSizeX;
	int poxY = (aniframe / mCellCountX) * mCellSizeY;

	if (mbAlphaBlend)
	{
		AlphaBlend(
			*mDrawDC,
			x, y,
			mCellSizeX * scaleX, mCellSizeY * scaleY,
			hMemDC,
			poxX, poxY,
			mCellSizeX, mCellSizeY,
			mBF);
		return;
	}

	TransparentBlt(
		*mDrawDC,
		x, y,
		mCellSizeX * scaleX, mCellSizeY * scaleY,
		hMemDC,
		poxX, poxY,
		mCellSizeX, mCellSizeY,
		RGB(255, 0, 255)
	);
}

#pragma endregion

#pragma region Scroll Sprite
BTScrollObject::BTScrollObject() {}
BTScrollObject::~BTScrollObject() {}

void BTScrollObject::InitScrollSprite(HDC* backDC, BTSprite* pSprite, bool IsAlphaBlend)
{
	mDrawDC = backDC;
	mpSprite = pSprite;
	mbAlphaBlend = IsAlphaBlend;
}

void BTScrollObject::SetScroll(float speed, int x, int y, float scaleX, float scaleY, float alpha, int dirX = 1)
{
	mSpeed = speed;
	mOffset = 0;

	mPosX = x;
	mPosY = y;
	mSizeX = scaleX;
	mSizeY = scaleY;

	mDirX = dirX;

	mBF.BlendOp = AC_SRC_OVER;
	mBF.BlendFlags = 0;
	mBF.SourceConstantAlpha = (BYTE)(255 * alpha);
	mBF.AlphaFormat = AC_SRC_ALPHA;
}

void BTScrollObject::SetScroll(BTScrollData scrollData)
{
	SetScroll(scrollData.speed, scrollData.x, scrollData.y, scrollData.scaleX, scrollData.scaleY, scrollData.alpha, scrollData.dirX);
}

void BTScrollObject::PlayScroll(float dtime)
{
	if (mDirX < 0)
	{
		if (mOffset < -1 * (mpSprite->Width * mSizeX)) 
		{
			mOffset = 0;
		}
	}
	else if (mDirX > 0)
	{
		if (mOffset > (mpSprite->Width * mSizeX)) 
		{
			mOffset = 0;
		}
	}

	mOffset += (mSpeed * dtime * mDirX);

	//胶农费1
	AlphaBlend(
		*mDrawDC,
		mPosX + mOffset, mPosY,
		mpSprite->Width * mSizeX, mpSprite->Height * mSizeY,
		mpSprite->hMemDC,
		0, 0,
		mpSprite->Width, mpSprite->Height,
		mBF);

	//胶农费2
	AlphaBlend(
		*mDrawDC,
		mPosX + (-mpSprite->Width * mSizeX + 1) * mDirX + mOffset, mPosY,
		mpSprite->Width * mSizeX, mpSprite->Height * mSizeY,
		mpSprite->hMemDC,
		0, 0,
		mpSprite->Width, mpSprite->Height,
		mBF);

	//胶农费3
	//AlphaBlend(
	//	*mDrawDC,
	//	mPosX + (-mpSprite->Width * 2 * mSizeX + 1) * mDirX + mOffset, mPosY,
	//	mpSprite->Width * mSizeX, mpSprite->Height * mSizeY,
	//	mpSprite->hMemDC,
	//	0, 0,
	//	mpSprite->Width, mpSprite->Height,
	//	mBF);
}


#pragma endregion

#pragma region GameObject

BTGameObject::BTGameObject()
{

}

BTGameObject::~BTGameObject()
{

}

void BTGameObject::Initialize(int left, int top, int right, int bottom)
{
	object.left = left;
	object.top = top;
	object.right = left + right;
	object.bottom = top + bottom;
}

bool BTGameObject::IsCollided(POINT cursorPos)
{
	if (cursorPos.x >= object.left && cursorPos.x <= object.right &&
		cursorPos.y >= object.top && cursorPos.y <= object.bottom)
	{
		m_IsCollided = true;
		return true;
	}
	else
	{
		m_IsCollided = false;
		return false;
	}
}

#pragma endregion
