#pragma once
#include "../YenaSe/Inc/ynMMedia.h"

#define MAX_SOUNDTRACK 12	// 효과음 및 배경음 총 개수

static TCHAR* MediaFileName[MAX_SOUNDTRACK] =
{
	"../SoundResource/bgm_opening.wav",			// 0	오프닝
	"../SoundResource/bgm_title.wav",			// 1	타이틀
	"../SoundResource/bgm_busstop.wav",			// 2	정류장
	"../SoundResource/bgm_minigame.wav",		// 3	미니게임
	"../SoundResource/bgm_gameover.wav",		// 4	게임오버
	"../SoundResource/bgm_ending1.wav",			// 5	엔딩1
	"../SoundResource/bgm_ending2.wav",			// 6	엔딩2
	"../SoundResource/bgm_ending3.wav",			// 7	엔딩3
	"../SoundResource/bgm_ending4.wav",			// 8	엔딩4

	"../SoundResource/sfx_AirBreaks.wav",		// 9	미니게임 버스멈춤
	"../SoundResource/sfx_BusLeave.wav",		// 10	미니게임 버스출발
	"../SoundResource/sfx_TrafficSignal.wav"	// 11	미니게임 신호등
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

	// 효과음
	BREAK,
	DEPARTURE,
	SIGNAL
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	LPSOUNDEFFECT pSoundEffect[MAX_SOUNDTRACK];		// .wav 파일
	int mTrackNum;									// 곡 번호

public:
	void Initiate(HWND hwnd);
	int	 DataLoad_WAV(TCHAR* filename);
	void DataLoadAllWavByFile();
	int  DataLoad_MP3(TCHAR* filename);
	void DataRelease();
	void Release(HWND hwnd);
	void Update(float dtime);
	void PlayWAV_LOOP(int TrackNum);			// BGM 반복재생됨
	void PlayWAV_ONCE(int TrackNum);			// Sound Effect 한번만 재생
	void StopWAV(int TrackNum);
	void StopAllWAV();							// 모든 wav 정지
	void PlayMP3();								// MP3 재생 - 1개만!
	void Volume();								// +Q, -W

	// 사운드 모든 기능이 있는 함수(필요한 것만 사용)
	void PlayingTool();
};

