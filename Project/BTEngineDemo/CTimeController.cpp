#include <Windows.h>
#include "CTimeController.h"

LARGE_INTEGER	CTimeController::mStaticTime;

LARGE_INTEGER	CTimeController::mPrevTime;
LARGE_INTEGER	CTimeController::mCurrTime;

LARGE_INTEGER	CTimeController::mStartTime;
LARGE_INTEGER	CTimeController::mEndTime;
LARGE_INTEGER	CTimeController::mElaspedTime;

CTimeController::CTimeController()
{
}

CTimeController::~CTimeController()
{
}

void CTimeController::Initialize()
{
	//���� ������
	mFPS = 60.f;
	mTargetElaspedTime = 1 / mFPS;

	// QueryPerfomence
	QueryPerformanceFrequency(&mStaticTime);
	QueryPerformanceCounter(&mCurrTime);

	// GetTickCount
	GetTickCount64();

	//timeGetTime
}

void CTimeController::StartTimeStamp()
{
	QueryPerformanceCounter(&mStartTime);	
}

void CTimeController::EndTimeStamp()
{
	QueryPerformanceCounter(&mEndTime);
}

float CTimeController::GetElaspedTimeSec() const
{
	return ((float)mElaspedTime.QuadPart / (float)mStaticTime.QuadPart) * 1000.f;
}

void CTimeController::CheckTime()
{
	mElaspedTime.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;
}

bool CTimeController::FPSCheck()
{
	EndTimeStamp();
	CheckTime();

	if (mTargetElaspedTime * 1000.0f < GetElaspedTimeSec())
	{
		//���� ����������
		StartTimeStamp();
		return true;
	}
	return false;
}
