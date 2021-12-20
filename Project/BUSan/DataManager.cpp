#include "pch.h"
#include "DataManager.h"
#include <stdio.h>

DataManager::DataManager(){}

DataManager::~DataManager(){}

#pragma region 데이터 로드

/// 정거장 데이터 로드
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

	//총 노드 수
	int DataCount = 0;
	fread(&DataCount, sizeof(int), 1, fp);

	//노드 읽기
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

/// 이미지 리소스 로드
void DataManager::LoadImageDataFromFile(BTEngine* engine)
{
	// 폰트 로드
	// 릴리즈 되어야 한다.
	// 폰트이름(파일 속성 값)으로 사용

	AddFontResource(PATH_FONT);

	mSpriteList.clear();

	//모든 이미지 파일을 로드 합니다.
	BTSprite* loadSprite = new BTSprite();
	int loopCount = (int)EImgSrcIdx::SrcMax;
	for (int index = 0; index < loopCount; index++)
	{
		engine->btLoadSpriteFromFile(loadSprite, ImgSrcPath[index]);
		mSpriteList.insert(mSpriteList.begin() + index, *loadSprite);
	}
	delete loadSprite;
}

/// 미니맵 리소스 로드
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

#pragma region 정거장 정보 관련
///정거장 정보 (ID)
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

///정거장 이름	 (by StationID)
char* DataManager::GetStationNameDataById(int stationID)
{
	if (stationID < 0 || stationID > STATION_COUNT) { return nullptr; }
	return mStationNameList[stationID - 1].Name;
}

///정거장 이미지 번호 (by StationID)
int DataManager::GetStationImageIdById(int stationID)
{
	if (stationID < 0 || stationID > STATION_COUNT) { return 0; }
	return mStationNameList[stationID - 1].ImageID - 1;
}
#pragma endregion

#pragma region 이미지 관련

///이미지 (by Index)
BTSprite* DataManager::GetSpriteByIndex(int index)
{
	return &mSpriteList[index];
}

BTSprite* DataManager::GetMiniMapByID(int ID)
{
	return &mMiniMapSpriteList[ID];
}

#pragma endregion

#pragma region 이벤트 관련

///이벤트 데이터 (by Index)
EventData* DataManager::GetEventDataByIndex(int index)
{
	return &mEventDataList[index];
}

#pragma endregion

#pragma region 데이터 해제

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