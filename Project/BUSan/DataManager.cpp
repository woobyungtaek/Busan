#include "pch.h"
#include "DataManager.h"
#include <stdio.h>

DataManager::DataManager(){}

DataManager::~DataManager(){}

#pragma region ������ �ε�

/// ������ ������ �ε�
void DataManager::LoadStationDataListFromFile(TCHAR filePath[])
{
	mStationNodeList.clear();

	FILE* fp = NULL;

#ifdef _UNICODE
	fopen_s(&fPtr, fileName, "rb, ccs = UNICODE");
#else
	fopen_s(&fp, filePath, "rb");
#endif

	if (fp == NULL) { return; }

	//�� ��� ��
	int DataCount = 0;
	fread(&DataCount, sizeof(int), 1, fp);

	//��� �б�
	for (int index = 0; index < DataCount; index++)
	{
		StationNode instNode;

		fread(&instNode.StationID, sizeof(short), 1, fp);
		fread(&instNode.DistrictID, sizeof(short), 1, fp);
		fread(&instNode.EventID, sizeof(short), 1, fp);

		int aroundSize = sizeof(instNode.AroundList) / sizeof(AroundNode);
		for (int aroundIdx = 0; aroundIdx < aroundSize; aroundIdx++)
		{
			fread(&instNode.AroundList[aroundIdx].StationID, sizeof(short), 1, fp);
			fread(&instNode.AroundList[aroundIdx].BusTimeTable, sizeof(instNode.AroundList->BusTimeTable), 1, fp);
		}
		mStationNodeList.push_back(instNode);
	}

	fclose(fp);
}

/// �̹��� ���ҽ� �ε�
void DataManager::LoadImageDataFromFile(BTEngine* engine)
{
	// ��Ʈ �ε�
	// ������ �Ǿ�� �Ѵ�.
	// ��Ʈ�̸�(���� �Ӽ� ��)���� ���

	AddFontResource(PATH_FONT);

	mSpriteList.clear();

	//��� �̹��� ������ �ε� �մϴ�.
	BTSprite* loadSprite = new BTSprite();
	int loopCount = (int)EImgSrcIdx::SrcMax;
	for (int index = 0; index < loopCount; index++)
	{
		engine->btLoadSpriteFromFile(loadSprite, ImgSrcPath[index]);
		mSpriteList.insert(mSpriteList.begin() + index, *loadSprite);
	}
	delete loadSprite;
}

/// �̴ϸ� ���ҽ� �ε�
void DataManager::LoadMiniMapDataFromFile(BTEngine* engine)
{
	mMiniMapSpriteList.clear();
	
	char buffer[30];

	BTSprite* loadSprite = new BTSprite();
	engine->btLoadSpriteFromFile(loadSprite, "../Data/minimap/MiniMap.bmp");
	mMiniMapSpriteList.insert(mMiniMapSpriteList.begin() + 0, *loadSprite);

	int arrIdx = 1;
	for (int index = 1; index <= 34; index++)
	{
		sprintf_s(buffer, "../Data/minimap/%d_blue.bmp", index);
		engine->btLoadSpriteFromFile(loadSprite, buffer);
		mMiniMapSpriteList.insert(mMiniMapSpriteList.begin() + arrIdx, *loadSprite);
		arrIdx++;
		sprintf_s(buffer, "../Data/minimap/%d_red.bmp", index);
		engine->btLoadSpriteFromFile(loadSprite, buffer);
		mMiniMapSpriteList.insert(mMiniMapSpriteList.begin() + arrIdx, *loadSprite);
		arrIdx++;
	}
	delete loadSprite;
}

#pragma endregion

#pragma region ������ ���� ����
///������ ���� (ID)
StationNode* DataManager::GetStationNodeByID(int stationID)
{
	int loopCount = mStationNodeList.size();
	for (int index = 0; index < loopCount; index++)
	{
		if (mStationNodeList[index].StationID == stationID)
		{
			return &mStationNodeList[index];
		}
	}
	return nullptr;
}

///������ �̸�	 (by StationID)
char* DataManager::GetStationNameDataById(int stationID)
{
	if (stationID < 0 || stationID > STATION_COUNT) { return nullptr; }
	return mStationNameList[stationID - 1].Name;
}

///������ �̹��� ��ȣ (by StationID)
int DataManager::GetStationImageIdById(int stationID)
{
	if (stationID < 0 || stationID > STATION_COUNT) { return 0; }
	return mStationNameList[stationID - 1].ImageID - 1;
}
#pragma endregion

#pragma region �̹��� ����

///�̹��� (by Index)
BTSprite* DataManager::GetSpriteByIndex(int index)
{
	return &mSpriteList[index];
}

BTSprite* DataManager::GetMiniMapByID(int ID)
{
	return &mMiniMapSpriteList[ID];
}

#pragma endregion

#pragma region �̺�Ʈ ����

///�̺�Ʈ ������ (by Index)
EventData* DataManager::GetEventDataByIndex(int index)
{
	return &mEventDataList[index];
}

#pragma endregion

#pragma region ������ ����

void DataManager::DataRelease()
{
	int loopCount = mSpriteList.size();
	for (int index = 0; index < loopCount; index++)
	{
		DeleteDC(mSpriteList[index].hMemDC);
	}	
	loopCount = mSpriteList.size();
	for (int index = 0; index < loopCount; index++)
	{
		DeleteDC(mMiniMapSpriteList[index].hMemDC);
	}
}

#pragma endregion