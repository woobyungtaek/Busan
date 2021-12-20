#pragma once
/// <summary>
/// �ð� ���� Ŭ����
/// 
/// 20.11.13
/// 1. FPS ����
/// 2. Ư�� ������ �ɸ� �ð� ����
/// </summary>

class CTimeController
{
private:
	static LARGE_INTEGER	mStaticTime;
	
	static LARGE_INTEGER	mStartTime;
	static LARGE_INTEGER	mEndTime;
	static LARGE_INTEGER	mElaspedTime;

	static LARGE_INTEGER	mPrevTime;
	static LARGE_INTEGER	mCurrTime;
public:
	CTimeController();
	~CTimeController();
	void Initialize();
	
	void StartTimeStamp();
	void EndTimeStamp();

	LARGE_INTEGER GetElaspedTime() const { return mElaspedTime;}
	float GetElaspedTimeSec() const;

	void CheckTime();

	bool FPSCheck();

private:
	float mFPS;
	float mTargetElaspedTime;
};

