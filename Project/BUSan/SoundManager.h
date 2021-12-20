#pragma once
#include "../YenaSe/Inc/ynMMedia.h"

#define MAX_SOUNDTRACK 12	// ȿ���� �� ����� �� ����

static TCHAR* MediaFileName[MAX_SOUNDTRACK] =
{
	"../SoundResource/bgm_opening.wav",			// 0	������
	"../SoundResource/bgm_title.wav",			// 1	Ÿ��Ʋ
	"../SoundResource/bgm_busstop.wav",			// 2	������
	"../SoundResource/bgm_minigame.wav",		// 3	�̴ϰ���
	"../SoundResource/bgm_gameover.wav",		// 4	���ӿ���
	"../SoundResource/bgm_ending1.wav",			// 5	����1
	"../SoundResource/bgm_ending2.wav",			// 6	����2
	"../SoundResource/bgm_ending3.wav",			// 7	����3
	"../SoundResource/bgm_ending4.wav",			// 8	����4

	"../SoundResource/sfx_AirBreaks.wav",		// 9	�̴ϰ��� ��������
	"../SoundResource/sfx_BusLeave.wav",		// 10	�̴ϰ��� �������
	"../SoundResource/sfx_TrafficSignal.wav"	// 11	�̴ϰ��� ��ȣ��
};

enum SoundTrackNumber
{
	// BGM
	OPENING = 0,
	TITLE,
	BUSSTOP,
	MINIGAME,
	GAMEOVER,
	ENDING1,
	ENDING2,
	ENDING3,
	ENDING4,

	// ȿ����
	BREAK,
	DEPARTURE,
	SIGNAL
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	LPSOUNDEFFECT pSoundEffect[MAX_SOUNDTRACK];		// .wav ����
	int mTrackNum;									// �� ��ȣ

public:
	void Initiate(HWND hwnd);
	int	 DataLoad_WAV(TCHAR* filename);
	void DataLoadAllWavByFile();
	int  DataLoad_MP3(TCHAR* filename);
	void DataRelease();
	void Release(HWND hwnd);
	void Update(float dtime);
	void PlayWAV_LOOP(int TrackNum);			// BGM �ݺ������
	void PlayWAV_ONCE(int TrackNum);			// Sound Effect �ѹ��� ���
	void StopWAV(int TrackNum);
	void StopAllWAV();							// ��� wav ����
	void PlayMP3();								// MP3 ��� - 1����!
	void Volume();								// +Q, -W

	// ���� ��� ����� �ִ� �Լ�(�ʿ��� �͸� ���)
	void PlayingTool();
};

