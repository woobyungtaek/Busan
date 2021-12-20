#pragma once
#include "../YenaSe/Inc/ynMMedia.h"

#define MAX_SOUNDTRACK 9	// 효과음 및 배경음 총 개수

static TCHAR* MediaFileName[MAX_SOUNDTRACK] =
{
	"../SoundResource/bgm_opening.wav",			// 0, 오프닝
	"../SoundResource/bgm_title.wav",			// 1, 타이틀
	"../SoundResource/bgm_busstop.wav",			// 2, 정류장
	"../SoundResource/bgm_minigame.wav",		// 3, 미니게임
	"../SoundResource/bgm_gameover.wav",		// 4, 게임오버		안나옴.
	"../SoundResource/bgm_ending1.wav",			// 5, 엔딩
	"../SoundResource/bgm_ending2.wav",			// 6
	"../SoundResource/bgm_ending3.wav",			// 7
	"../SoundResource/bgm_ending4.wav",			// 8				안나옴.
};

enum BGM
{
	OPENING = 0,
	TITLE,
	BUSSTOP,
	MINIGAME,
	GAMEOVER,
	ENDING1,
	ENDING2,
	ENDING3,
	ENDING4
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	LPSOUNDEFFECT pSoundEffect[MAX_SOUNDTRACK];		// .wav 파일
	int mTrackNum;										// 곡 번호

public:
	void Initiate(HWND hwnd);
	int	 DataLoad_WAV(TCHAR* filename);
	int  DataLoad_MP3(TCHAR* filename);
	void DataRelease();
	void Release(HWND hwnd);
	void Update(float dtime);
	void PlayWAV1(int TrackNum);				// BGM 반복재생됨
	void PlayWAV2(int TrackNum);				// Sound Effect 한번만 재생
	void PlayMP3();								// MP3 재생 - 1개만!
	void Volume();								// +Q, -W

	// 사운드 모든 기능이 있는 함수(필요한 것만 사용)
	void PlayingTool();
};

