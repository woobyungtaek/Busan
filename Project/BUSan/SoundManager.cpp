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
	// ���� ���� �ε�(wav, mp3)
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndLoad(MediaFileName[i], pSoundEffect[i]);		//'WAVE' ����.�ε�.
	}

	return true;
}
void SoundManager::DataLoadAllWavByFile()
{
	// ���� ���� �ε�(wav, mp3)
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndLoad(MediaFileName[i], pSoundEffect[i]);		//'WAVE' ����.�ε�.
	}
}

int SoundManager::DataLoad_MP3(TCHAR* filename)
{
	// ���� MP3 �ε�
	// MP3 �� �ѹ��� �ϳ��� ���ϸ� �ε�, �÷��� ����. 
	ynMediaLoad(filename);

	return true;
}

void SoundManager::DataRelease()
{
	// ���� ����
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		ynSndRelease(pSoundEffect[i]);
	}
	// mp3 ����
	//ynMediaRelease();
}

void SoundManager::Release(HWND hwnd)
{
	// �̵�� ��
	ynMMedia_Release();
}

void SoundManager::Update(float dtime)
{
	// ���� ���� ����
	ynMMedia_Update(dtime);
}

void SoundManager::PlayWAV_LOOP(int TrackNum)
{
	// �ݺ����
	ynSndPlay(pSoundEffect[TrackNum], PLAY_LOOP_, TRUE);
}

void SoundManager::PlayWAV_ONCE(int TrackNum)
{
	// �� ���� ���
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
	// ������ ���� (�ͽ� ����)����. (0 ~ 100)
	//------------------------------------
	if (IsKeyDn(VK_0)) { ynSndMasterVolumeUp(100); }
	if (IsKeyDn(VK_9)) { ynSndMasterVolumeDn(100); }
}

void SoundManager::PlayingTool()
{
	//---------------------------------
	// ���� �׽�Ʈ Wave #1.��
	//---------------------------------
	if (IsKeyUp(VK_A))							//�ѹ�  ����.
	{
		ynSndPlay(pSoundEffect[1]);				//1�� ����+�ǰ���(rewind) ����: Play �Լ� ���� ȣ�⿡�� 'ó��'���� �÷��� ����.��
	}

	if (IsKeyUp(VK_Z))							//�ѹ�  ����+�ǰ����
	{
		ynSndPlay(pSoundEffect[1], PLAY_ONCE_, TRUE);	//1�� ����+�ǰ��� : Play �Լ� ȣ��ø��� 'ó��'���� �÷���.��
	}
	if (IsKeyUp(VK_C))							//���� ���� ����.
	{
		ynSndStop(pSoundEffect[1]);
	}

	//---------------------------------
	// ���� �׽�Ʈ Wave #2.��
	//---------------------------------
	if (IsKeyUp(VK_S))							//���� ���� ����.
	{
		ynSndPlay(pSoundEffect[3], PLAY_LOOP_);			//���ѹݺ�+�ǰ���(rewind) ����.��
	}

	if (IsKeyUp(VK_X))							//���� ���� ����+�ǰ���.��
	{
		ynSndPlay(pSoundEffect[3], PLAY_LOOP_, TRUE);	//���ѹݺ�+�ǰ���
	}

	if (IsKeyUp(VK_D))							//���� ���� ����.
	{
		ynSndStop(pSoundEffect[3]);
	}

	//------------------------------------
	// ������ ���� (�ͽ� ����)����. (0 ~ 100)
	//------------------------------------
	if (IsKeyDn(VK_T))
		ynSndMasterVolumeUp(100);

	if (IsKeyDn(VK_G))
		ynSndMasterVolumeDn(100);

	// ���ڱ� �ȵ�. 2020.11.24. YenaSed.dll�� �̻��ѵ� �ϴ�.

	//---------------------------------
	// ���� ���� (mp3) ��
	//---------------------------------
	if (IsKeyUp(VK_1))						//�ѹ�  ����.
	{
		ynMediaPlay();
	}

	if (IsKeyUp(VK_2))						//�Ͻ�����.
	{
		ynMediaPause();
	}

	if (IsKeyUp(VK_3))						//���� ����.
	{
		ynMediaStop();
	}

	if (IsKeyDn(VK_4))						//����+
	{
		ynMediaVolumeUp();
	}

	if (IsKeyDn(VK_5))						//����-
	{
		ynMediaVolumeDn();
	}

	if (IsKeyUp(VK_7))						// ��Ʈ
	{
		ynMediaSetVolume(0);
	}

	if (IsKeyUp(VK_8))						// ��Ʈ���
	{
		ynMediaSetVolume(100);
	}
}