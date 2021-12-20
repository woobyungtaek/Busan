#include "pch.h"

SoundManager::SoundManager()
{
	mTrackNum = 0;

	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		pSoundEffect[i] = nullptr;
	}
}

SoundManager::~SoundManager() 
{

}

void SoundManager::Initiate(HWND hwnd)
{
	ynMMedia_Initial(hwnd);
}

int SoundManager::DataLoad_WAV(TCHAR* filename)
{
	// 사운드 파일 로드(wav, mp3)
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndLoad(MediaFileName[i], pSoundEffect[i]);		//'WAVE' 파일.로드.
	}

	return true;
}
void SoundManager::DataLoadAllWavByFile()
{
	// 사운드 파일 로드(wav, mp3)
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndLoad(MediaFileName[i], pSoundEffect[i]);		//'WAVE' 파일.로드.
	}
}

int SoundManager::DataLoad_MP3(TCHAR* filename)
{
	// 사운드 MP3 로드
	// MP3 는 한번에 하나의 파일만 로딩, 플레이 가능. 
	ynMediaLoad(filename);

	return true;
}

void SoundManager::DataRelease()
{
	// 사운드 제거
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndRelease(pSoundEffect[i]);
	}
	// mp3 제거
	//ynMediaRelease();
}

void SoundManager::Release(HWND hwnd)
{
	// 미디어 제
	ynMMedia_Release();
}

void SoundManager::Update(float dtime)
{
	// 사운드 엔진 갱신
	ynMMedia_Update(dtime);
}

void SoundManager::PlayWAV_LOOP(int TrackNum)
{
	// 반복재생
	ynSndPlay(pSoundEffect[TrackNum], PLAY_LOOP_, TRUE);
}

void SoundManager::PlayWAV_ONCE(int TrackNum)
{
	// 한 번만 재생
	ynSndPlay(pSoundEffect[TrackNum], PLAY_ONCE_, TRUE);
}

void SoundManager::StopWAV(int TrackNum)
{
	ynSndStop(pSoundEffect[TrackNum]);
}

void SoundManager::StopAllWAV()
{
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		StopWAV(i);
	}
}

void SoundManager::PlayMP3()
{
	ynMediaPlay();
}

void SoundManager::Volume()
{
	//------------------------------------
	// 마스터 볼륨 (믹스 버퍼)조작. (0 ~ 100)
	//------------------------------------
	if (IsKeyDn(VK_0)) { ynSndMasterVolumeUp(100); }
	if (IsKeyDn(VK_9)) { ynSndMasterVolumeDn(100); }
}

void SoundManager::PlayingTool()
{
	//---------------------------------
	// 사운드 테스트 Wave #1.★
	//---------------------------------
	if (IsKeyUp(VK_A))							//한번  연주.
	{
		ynSndPlay(pSoundEffect[1]);				//1번 연주+되감기(rewind) 없음: Play 함수 연속 호출에도 '처음'부터 플레이 없음.★
	}

	if (IsKeyUp(VK_Z))							//한번  연주+되감기★
	{
		ynSndPlay(pSoundEffect[1], PLAY_ONCE_, TRUE);	//1번 연주+되감기 : Play 함수 호출시마다 '처음'부터 플레이.★
	}
	if (IsKeyUp(VK_C))							//연속 연주 중지.
	{
		ynSndStop(pSoundEffect[1]);
	}

	//---------------------------------
	// 사운드 테스트 Wave #2.★
	//---------------------------------
	if (IsKeyUp(VK_S))							//연속 연주 시작.
	{
		ynSndPlay(pSoundEffect[3], PLAY_LOOP_);			//무한반복+되감기(rewind) 없음.★
	}

	if (IsKeyUp(VK_X))							//연속 연주 시작+되감기.★
	{
		ynSndPlay(pSoundEffect[3], PLAY_LOOP_, TRUE);	//무한반복+되감기
	}

	if (IsKeyUp(VK_D))							//연속 연주 중지.
	{
		ynSndStop(pSoundEffect[3]);
	}

	//------------------------------------
	// 마스터 볼륨 (믹스 버퍼)조작. (0 ~ 100)
	//------------------------------------
	if (IsKeyDn(VK_T))
		ynSndMasterVolumeUp(100);

	if (IsKeyDn(VK_G))
		ynSndMasterVolumeDn(100);

	// 갑자기 안됨. 2020.11.24. YenaSed.dll이 이상한듯 하다.

	//---------------------------------
	// 연주 데모 (mp3) ★
	//---------------------------------
	if (IsKeyUp(VK_1))						//한번  연주.
	{
		ynMediaPlay();
	}

	if (IsKeyUp(VK_2))						//일시정지.
	{
		ynMediaPause();
	}

	if (IsKeyUp(VK_3))						//연주 중지.
	{
		ynMediaStop();
	}

	if (IsKeyDn(VK_4))						//볼륨+
	{
		ynMediaVolumeUp();
	}

	if (IsKeyDn(VK_5))						//볼륨-
	{
		ynMediaVolumeDn();
	}

	if (IsKeyUp(VK_7))						// 뮤트
	{
		ynMediaSetVolume(0);
	}

	if (IsKeyUp(VK_8))						// 뮤트취소
	{
		ynMediaSetVolume(100);
	}
}