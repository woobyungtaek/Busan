#include "pch.h"

GameManager::GameManager() {}
GameManager::~GameManager() {}

//초기화
void GameManager::InitGameManager(BTEngine* engine, HWND hWnd)
{
	mBTEngine = engine;
	mDataManager = new DataManager();
	mSoundManager = new SoundManager();
	mSoundManager->Initiate(hWnd);

	mGameState = (int)EGameState::GS_MainLoad;
}

//게임 씬
int  GameManager::GameLoop()
{
	switch (mGameState)
	{
	case (int)EGameState::GS_MainLoad:
		DataLoad();
		return GS_GO;

	case (int)EGameState::GS_Intro_Start:
		Scene_Intro_Start();
		return GS_GO;
	case (int)EGameState::GS_Intro:
		Scene_Intro();
		return GS_GO;

	case (int)EGameState::GS_MainMenu_Start:
		Scene_MainMenu_Start();
		return GS_GO;
	case (int)EGameState::GS_MainMenu:
		Scene_MainMenu();
		return GS_GO;

	case (int)EGameState::GS_BusStation_Start:
		Scene_BusStation_Start();
		return GS_GO;
	case (int)EGameState::GS_BusStation:
		Scene_BusStation();
		return GS_GO;

	case (int)EGameState::GS_BusMove_Game_Start:
		Scene_BusMoveGame_Start();
		return GS_GO;
	case (int)EGameState::GS_BusMove_Game:
		Scene_BusMoveGame();
		return GS_GO;

	case (int)EGameState::GS_BusMove_Event_Start:
		Scene_BusMoveEvent_Start();
		return GS_GO;
	case (int)EGameState::GS_BusMove_Event:
		Scene_BusMoveEvent();
		return GS_GO;

	case (int)EGameState::GS_GameOver_Start:
		Scene_GameOver_Start();
		return GS_GO;
	case (int)EGameState::GS_GameOver:
		Scene_GameOver();
		return GS_GO;

	case (int)EGameState::GS_Ending_Start:
		Scene_GameEnding_Start();
		return GS_GO;
	case (int)EGameState::GS_Ending:
		Scene_GameEnding();
		return GS_GO;

	default:
		return GS_EXIT;
	}
}

void GameManager::DataLoad()
{
	//데이터 로드
	mDataManager->LoadStationDataListFromFile(STATION_DATA_PATH);
	mDataManager->LoadImageDataFromFile(mBTEngine);
	mDataManager->LoadMiniMapDataFromFile(mBTEngine);

	//사운드 로드
	mSoundManager->DataLoadAllWavByFile();						// wav파일 전부 로드
	//mSoundManager->DataLoad_MP3(MediaFileName[OPENING]);		// mp3파일 한 개 로드(파일명)

	//게임 오브젝트 생성
	CreateGameObject();

	//상태 변경
	mGameState = (int)EGameState::GS_Intro_Start;
	//mBTEngine->btTextOut(30, 30, "데이터 로드 중");
}

void GameManager::Scene_Intro_Start()
{
	//인트로 씬 도입부
	mStoryPage = 0;
	mTextIdx = 0;

	//인트로 BGM
	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(OPENING);

	mGameState = (int)EGameState::GS_Intro;
	//mBTEngine->btTextOut(30, 30, "인트로 시작 점");
}
void GameManager::Scene_Intro()
{
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Intro_0 + mStoryPage), 0, 0, 0.8, 0.8, 1);
	//mBTEngine->btDrawRect(bt_Intro_Skip.object, RGB(255, 0, 255));
	mBTEngine->btDrawText(bt_Intro_Skip.object, 35, 900, TA_RIGHT | TA_BOTTOM, RGB(0, 0, 0), "Skip >>");

	//text index need
	mBTEngine->btDrawText(0, 750, mBTEngine->ScreenSize.x, 35, 35, 100, DT_CENTER, RGB(0, 0, 0),
		"%s", mDataManager->GetStoryText(mTextIdx));

	//버튼을 눌렀을 때
	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		mTextIdx++;

		//삽화 변경 문구 Index
		if (mTextIdx == 1 || mTextIdx == 2 || mTextIdx == 4)
		{
			mStoryPage++;
		}

		if (bt_Intro_Skip.IsCollided(mBTEngine->MousePositionCT) || (mTextIdx > (int)EStoryTextIdx::Intro5 - (int)EStoryTextIdx::Intro1))
		{
			mGameState = (int)EGameState::GS_MainMenu_Start;
			return;
		}
	}
}

void GameManager::Scene_MainMenu_Start()
{
	//플레이어 값 초기화
	mCurrTime = START_TIME;			// 05:00분 출발
	mCurrStationID = START_STATION;	// 1번 서울역 출발
	mLinkedStationID = -1;
	mLerpTime = 1;

	bt_MainMenu_Start.Initialize(707, 401, 215, 68);
	bt_MainMenu_Exit.Initialize(707, 476, 215, 60);
	bt_MainMenu_BackIntro.Initialize(506, 539, 425, 61);

	//BGM 삽입
	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(TITLE);

	mGameState = (int)EGameState::GS_MainMenu;
	//mBTEngine->btTextOut(30, 30, "메인 메뉴 시작 점");
}
void GameManager::Scene_MainMenu()
{
	//타이틀 씬 그리기
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Title), 0, 0, 0.8, 0.8, 1);

	//mBTEngine->btTextOut(30, 30, "메인 메뉴 중");

	//mBTEngine->btDrawRect(bt_MainMenu_Start.object.left, bt_MainMenu_Start.object.top,		bt_MainMenu_Start.object.right, bt_MainMenu_Start.object.bottom, RGB(255, 0, 255));
	//mBTEngine->btDrawRect(bt_MainMenu_Exit.object.left, bt_MainMenu_Exit.object.top,		bt_MainMenu_Exit.object.right, bt_MainMenu_Exit.object.bottom, RGB(255, 0, 255));
	//mBTEngine->btDrawRect(bt_MainMenu_BackIntro.object.left, bt_MainMenu_BackIntro.object.top,		bt_MainMenu_BackIntro.object.right, bt_MainMenu_BackIntro.object.bottom, RGB(255, 0, 255));

	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		POINT cursorPos = mBTEngine->MousePositionCT;

		if (bt_MainMenu_Start.IsCollided(cursorPos))
		{
			mGameState = (int)EGameState::GS_BusStation_Start;
		}
		if (bt_MainMenu_Exit.IsCollided(cursorPos))
		{
			//게임 종료
			mGameState = -1;
		}
		if (bt_MainMenu_BackIntro.IsCollided(cursorPos))
		{
			mGameState = (int)EGameState::GS_Intro_Start;
		}
		return;
	}
}

void GameManager::Scene_BusStation_Start()
{
	if (mCurrStationID <= 0) { return; }

	mPage = 0;
	mTotalPage = 0;
	mSelectStationID = -1;
	mSelectEventID = -1;

	bt_Station_PagePrev.Initialize(180 + 200, 790, 35, 35);
	bt_Station_PageNext.Initialize(314 + 200, 790, 35, 35);

	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(TITLE);

	mbOnNext = false;

	mbOnBusEffect = false;
	mSoundManager->PlayWAV_LOOP(DEPARTURE);
	mBusEffect.Init(mDataManager->GetStationNodeByID(mCurrStationID)->DistrictID, 500 - mBTEngine->ScreenSize.x, 275);

	mGameState = (int)EGameState::GS_BusStation;
}
void GameManager::Scene_BusStation()
{
	StationNode* currentStation = mDataManager->GetStationNodeByID(mCurrStationID);

	DrawStationBackGround(currentStation);

	if (mbOnBusEffect == false)
	{
		DrawMiniMap(mCurrStationID, mSelectStationID);
	}

	DrawStationClock(currentStation);

	//총 노드 카운트 및 페이지 설정
	int nodeCount = 0;
	for (int index = 0; index < LINK_COUNT; index++)
	{
		if (currentStation->AroundList[index].StationID <= 0) { continue; }
		nodeCount += 1;
	}

	mTotalPage = nodeCount / 4;
	if (nodeCount % 4 != 0) { mTotalPage += 1; }

	DrawStationNodeInfo(currentStation);

	if (CheckGameOverState(currentStation)) { return; }

	//페이지 버튼 입력 및 갱신
	OnClickedPageButton();

	//버스 연출 이동
	mbOnBusEffect = DrawBusEffect(&mBusEffect);
	if (mbOnBusEffect == true)
	{
		return;
	}
	//else
	//{
	//	if (mbOnNext == true)
	//	{
	//		//출발 : 현재시간을 출발 시간으로 변경
	//		mCurrTime = mSelectDepartureTime;

	//		mPage = 0;
	//		mTotalPage = 0;

	//		//현재 정거장의 확정 이벤트 확인
	//		if (mSelectEventID <= 0)
	//		{
	//			mGameState = (int)EGameState::GS_BusMove_Game_Start;
	//		}
	//		else
	//		{
	//			mGameState = (int)EGameState::GS_BusMove_Event_Start;
	//		}
	//	}
	//}

	OnClickedNodeSelectButton(currentStation);
	OnClickedNextButton();
}

void GameManager::Scene_BusMoveGame_Start()
{
	IsStop = false;
	IsMovePopup = false;
	mPushCount = 0;
	mRealTime = 0;
	mLimitPushCount = (mSelectElapseTime / 10) * mPushCountCorrection;
	mSelectElapseTime = 0;//Game에서 다시 계산된다.
	mSignalLight.PosX = mSignalRegenPos;
	mSignalLight.SetRandomSignal();

	mStopTime = 0;
	mLerpTime = 1;

	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(MINIGAME);

	mGameState = (int)EGameState::GS_BusMove_Game;
	//mBTEngine->btTextOut(30, 30, "버스 이동 게임 시작점");
}
void GameManager::Scene_BusMoveGame()
{
	BTSprite* drawSprite = nullptr;

	//배경 그리기
	int districtID = mDataManager->GetStationNodeByID(mSelectStationID)->DistrictID;
	DrawBusMoving(districtID, mLerpTime);

	//1초에 5분씩 ElapseTime이 증가 한다.
	mRealTime += mBTEngine->GetDeltaTime();
	if (mRealTime > 0.5 && IsMovePopup == false)
	{
		//1초에 10분씩 시간이 증가
		mRealTime = 0;
		mSelectElapseTime += 5;
	}
	if (IsStop)
	{
		mStopTime += mBTEngine->GetDeltaTime();
		if (mStopTime > 2)
		{
			mSoundManager->StopWAV(DEPARTURE);
			mSoundManager->PlayWAV_ONCE(DEPARTURE);
			mStopTime = 0;
			mLerpTime = 1;
			IsStop = false;
		}
	}

	//키입력 
	if (mBTEngine->btInputKeyDown(VK_SPACE) && IsStop == false)
	{
		if (mPushCount < mLimitPushCount)
		{
			mPushCount++;
		}
	}
	if (mBTEngine->btInputKeyDown(VK_LBUTTON) && IsStop == false)
	{
		if (mSignalLight.IsCollided(mBTEngine->MousePositionCT))
		{
			mSoundManager->StopWAV(SIGNAL);
			mSoundManager->PlayWAV_ONCE(SIGNAL);
			mSignalLight.OnClickSignal();
		}
	}

	mBTEngine->btDrawFillRect(MINI_GAME_LIMIT, 642, MINI_GAME_LIMIT + 4, 672, RGB(255, 0, 0), RGB(255, 0, 0));
	mSignalLight.MovePos((mSignalSpeed * mBTEngine->GetDeltaTime() * mLerpTime * -1), 0, mSignalRegenPos);
	if (mSignalLight.PosX <= MINI_GAME_LIMIT && mSignalLight.IsChecked == false)
	{
		mSignalLight.IsChecked = true;
		if (mSignalLight.CurrentState != 2)
		{
			mSoundManager->PlayWAV_ONCE(BREAK);
			mLerpTime = 0;
			mStopTime = 0;
			IsStop = true;
		}
	}

	drawSprite = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Signal1 + mSignalLight.CurrentState);
	mBTEngine->btDrawSpriteAlphablend(
		drawSprite,
		mSignalLight.PosX,
		mSignalLight.PosY,
		0.9,
		0.9,
		1
	);

	mBTEngine->btDrawFillRect(mSignalLight.object.left, 642, mSignalLight.object.left - 4, 672, RGB(255, 0, 255), RGB(255, 0, 255));

	drawSprite = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MiniBoard);
	int xPos = (mBTEngine->ScreenSize.x / 2) - (drawSprite->Width * 0.9) / 2;
	int yPos = mBTEngine->ScreenSize.y - (drawSprite->Height * 0.8);
	int up = (drawSprite->Height * 0.8);
	mBTEngine->btDrawSpriteAlphablend(
		drawSprite,
		xPos, yPos - 30,
		0.9,
		0.8,
		1
	);

	int gaugePosX = (mBTEngine->ScreenSize.x / 2) - 400;
	int gaugeWidthX = (mBTEngine->ScreenSize.x / 2) + 400;
	mBTEngine->btDrawFillRect(gaugePosX, GAUGE_POS_Y, gaugeWidthX, GAUGE_HEIGHT, RGB(100, 100, 100), RGB(100, 100, 100));

	float progressValue = (float)mPushCount / (float)mLimitPushCount;
	progressValue = (gaugeWidthX - gaugePosX) * progressValue;

	int expectTime = mCurrTime + mSelectElapseTime;
	mBTEngine->btDrawFillRect(gaugePosX, GAUGE_POS_Y, gaugePosX + progressValue, GAUGE_HEIGHT, RGB(255, 36, 0), RGB(255, 36, 0));

	mBTEngine->btDrawText(
		MOVEGAME_POS_X,
		MOVEGAME_POS_Y + 60,
		MOVEGAME_WITDH - MOVEGAME_POS_X,
		100, 25,
		0,
		DT_CENTER, RGB(255, 255, 255),
		"도착 시간  %02d:%02d", MergeTimeToHour(expectTime), MergeTimeToMin(expectTime));

	mBTEngine->btDrawText(
		gaugePosX - 80, GAUGE_POS_Y,
		70, 100,

		30,
		FW_ULTRABOLD,
		DT_LEFT, RGB(255, 255, 255),
		"%s", mDataManager->GetStationNameDataById(mCurrStationID));

	mBTEngine->btDrawText(
		gaugeWidthX + 15, GAUGE_POS_Y,
		70, 100,
		30,
		FW_ULTRABOLD,
		DT_LEFT, RGB(255, 255, 255),
		"%s", mDataManager->GetStationNameDataById(mSelectStationID));

	if (mPushCount >= mLimitPushCount)
	{
		IsMovePopup = true;
		mLerpTime = 0;
		//팝업 만들기
		DrawMoveResultPopup(EGameState::GS_BusStation_Start, mCurrTime + mSelectElapseTime);
	}
}

void GameManager::Scene_BusMoveEvent_Start()
{
	mSelectEventData = mDataManager->GetEventDataByIndex(mSelectEventID - 1);

	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(MINIGAME);

	mEventAniTime = 0;
	mOffsetY = 0;
	IsMovePopup = false;

	mGameState = (int)EGameState::GS_BusMove_Event;
	//mBTEngine->btTextOut(30, 30, "버스 이동 이벤트 시작점");
}
void GameManager::Scene_BusMoveEvent()
{
	int districtID = mDataManager->GetStationNodeByID(mSelectStationID)->DistrictID;
	DrawBusMoving(districtID);

	mEventAniTime += mBTEngine->GetDeltaTime();

	if (mEventAniTime < 1)
	{
		return;
	}

	if (mEventAniTime > 1 && mEventAniTime < 2)
	{
		//이벤트 삽화 업
		mOffsetY += (mBTEngine->ScreenSize.y) * mBTEngine->GetDeltaTime();
		if (mOffsetY >= mBTEngine->ScreenSize.y)
		{
			mOffsetY = mBTEngine->ScreenSize.y;
		}
	}

#pragma region 이벤트 삽화 그리기
	int textPosX = 105;
	int ImageID = mSelectEventID;

	//이벤트 삽화
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Event_Fight + mSelectEventID - 1),
		900, 150 + (mBTEngine->ScreenSize.y) - mOffsetY,
		0.75, 0.75);

	//이벤트 끄기 이미지
	mBTEngine->btDrawSpriteTransparent(
		mDataManager->GetSpriteByIndex(
			(int)EImgSrcIdx::EventCloseBT), 1360, (mBTEngine->ScreenSize.y) + 105 - mOffsetY, 0.8, 0.8);
	//이벤트 끄기 버튼
	bt_Event_Close.Initialize(1360, (mBTEngine->ScreenSize.y) + 105 - mOffsetY, 46, 50);

	//제목
	mBTEngine->btDrawText(
		825 + textPosX, 650 + (mBTEngine->ScreenSize.y) - mOffsetY,
		711 + textPosX, 100,
		30, 0,
		DT_LEFT, RGB(0, 0, 0),
		"%s", mSelectEventData->Title);

	//시간 표시
	char buffer[30];
	int r = 0;
	int g = 0;
	int b = 0;
	if (mSelectEventData->Time < 0)
	{
		sprintf_s(buffer, "이동 시간: %d분 감소", mSelectEventData->Time * -1);
		//r = 0; g = 82; b = 255;
	}
	else
	{
		sprintf_s(buffer, "이동 시간: %d분 증가", mSelectEventData->Time);
		//r = 255; g = 82; b = 0;
	}
	mBTEngine->btDrawText(
		825 + textPosX, 690 + (mBTEngine->ScreenSize.y) - mOffsetY,
		711 + textPosX, 100,
		20, 0,
		DT_LEFT, RGB(r, g, b),
		"%s\n%s", mSelectEventData->Desc, buffer);
	//mBTEngine->btDrawRect(bt_Event_Close.object.left, bt_Event_Close.object.top, bt_Event_Close.object.right, bt_Event_Close.object.bottom, RGB(255, 0, 255));
#pragma endregion

	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		if (bt_Event_Close.IsCollided(mBTEngine->MousePositionCT))
		{
			//팝업 만들기
			IsMovePopup = true;
		}
	}
	if (IsMovePopup == true)
	{
		DrawMoveResultPopup(EGameState::GS_BusStation_Start, mCurrTime + mSelectElapseTime + mSelectEventData->Time);
	}
}

void GameManager::Scene_GameOver_Start()
{
	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(GAMEOVER);

	mGameState = (int)EGameState::GS_GameOver;
	//mBTEngine->btTextOut(30, 30, "게임오버 시작점");
}
void GameManager::Scene_GameOver()
{
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GameOver), 0, 0, 0.8, 0.8, 1);
	//mBTEngine->btDrawRect(bt_GameOver_MainMenuGo.object, RGB(255, 0, 255));

	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		if (bt_GameOver_MainMenuGo.IsCollided(mBTEngine->MousePositionCT))
		{
			mGameState = (int)EGameState::GS_MainMenu_Start;
			return;
		}
	}
}

void GameManager::Scene_GameEnding_Start()
{
	mEndingGrade = 0;
	mStoryPage = 0;
	mTextIdx = -1;
	mbStoryInput = false;

	mSoundManager->StopAllWAV();

	//게임 엔딩 등급 결정하기
	if (mCurrTime <= (16 * 60))
	{
		//True엔딩
		mEndingGrade = 1;
		mSoundManager->PlayWAV_LOOP(ENDING1);

		mTextStartIdx = (int)EStoryTextIdx::Ending1_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending1_4;
	}
	else if (mCurrTime > (16 * 60) && mCurrTime <= (18 * 60))
	{
		//엔딩 2
		mEndingGrade = 2;
		mSoundManager->PlayWAV_LOOP(ENDING2);

		mTextStartIdx = (int)EStoryTextIdx::Ending2_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending2_5;
	}
	else if (mCurrTime > (18 * 60) && mCurrTime <= (21 * 60))
	{
		//엔딩 3
		mEndingGrade = 3;
		mSoundManager->PlayWAV_LOOP(ENDING3);

		mTextStartIdx = (int)EStoryTextIdx::Ending3_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending3_3;
	}
	else if (mCurrTime > (21 * 60))
	{
		//엔딩 4
		mEndingGrade = 4;
		mSoundManager->PlayWAV_LOOP(ENDING4);

		mTextStartIdx = (int)EStoryTextIdx::Ending4_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending4_4;
	}

	mGameState = (int)EGameState::GS_Ending;
	//mBTEngine->btTextOut(30, 30, "게임 엔딩 시작점");
}
void GameManager::Scene_GameEnding()
{
	if (mbStoryInput == true && mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		mStoryPage = 5; // 삽화 고정
		mTextIdx += 1;
	}

	//자동으로 넘긴다.
	if (mStoryPage < 4)
	{
		mEndingTime += mBTEngine->GetDeltaTime();
		if (mEndingTime > 1)
		{
			mEndingTime = 0;
			mStoryPage++;
		}
	}

	mBTEngine->btDrawFillRect(0, 0, mBTEngine->ScreenSize.x, mBTEngine->ScreenSize.y, RGB(0, 0, 0), RGB(0, 0, 0));

	//게임 결과
	//ending page 1 = 등급, 시간
	if (mStoryPage < 5)
	{
		if (mStoryPage >= 1)
		{
			mBTEngine->btDrawText(200, mBTEngine->ScreenSize.y / 2 - 90, mBTEngine->ScreenSize.x, 50, 50, 900, DT_LEFT, RGB(255, 255, 255), "부산 도착 시간");
		}
		if (mStoryPage >= 2)
		{
			mBTEngine->btDrawText(275, mBTEngine->ScreenSize.y / 2, mBTEngine->ScreenSize.x, 80, 80, 900, DT_LEFT, RGB(255, 255, 255), "%02d:%02d", MergeTimeToHour(mCurrTime), MergeTimeToMin(mCurrTime));
		}
		if (mStoryPage >= 3)
		{
			int printChar = 63 + mEndingGrade;
			if (mEndingGrade == 1) { printChar = 83; }
			mBTEngine->btDrawText(-450, mBTEngine->ScreenSize.y / 2 - 125, mBTEngine->ScreenSize.x, 250, 250, 900, DT_RIGHT, RGB(255, 255, 255), "%c", (char)printChar);
			mBTEngine->btDrawText(-450 + 200, mBTEngine->ScreenSize.y / 2 - 45, mBTEngine->ScreenSize.x, 70, 70, 900, DT_RIGHT, RGB(255, 255, 255), "등급");
		}
		if (mStoryPage >= 4)
		{
			mBTEngine->btDrawText(0, mBTEngine->ScreenSize.y - 100, mBTEngine->ScreenSize.x, 100, 35, 100, DT_CENTER, RGB(255, 255, 255), "클릭해서 다음으로");
			mbStoryInput = true;
		}
		return;
	}

	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Ending1 + mEndingGrade - 1), 0, 0, 0.8, 0.8, 1);

	if (mTextIdx > mTextEndIdx - mTextStartIdx + 1)
	{
		mGameState = (int)EGameState::GS_MainMenu_Start;
		return;
	}
	if (mTextIdx > 0)
	{
		mBTEngine->btDrawText(0, 750, mBTEngine->ScreenSize.x, 35, 35, 100, DT_CENTER, RGB(255, 255, 255),
			"%s", mDataManager->GetStoryText(mTextStartIdx + mTextIdx - 1));
	}
	return;
}

#pragma region 생성/해제 함수

void GameManager::CreateGameObject()
{
	//스크롤 오브젝트 생성
	mScrollObjList.clear();
	int loopCount = (int)EImgSrcIdx::Busan_FCity;
	for (int index = (int)EImgSrcIdx::Fence; index <= loopCount; index++)
	{
		BTScrollObject instScrollObj;// = new BTScrollObject();
		mBTEngine->btLoadScrollSprite(&instScrollObj, mDataManager->GetSpriteByIndex(index), true);

		int arrIdx = ScrollObjIndex(index);
		mScrollObjList.insert(mScrollObjList.begin() + arrIdx, instScrollObj);
		mScrollObjList[arrIdx].SetScroll(mScrollData[arrIdx]);
	}
	//애니 오브젝트 생성
	mBTEngine->btLoadAniSpriteFromFile(&mBusTire, true, ImgSrcPath[(int)EImgSrcIdx::BusTire], 410, 90);
	mBusTire.SetAnimation(15, 1, 0, 1, -1);

	//버튼 오브젝트 생성
	bt_Intro_Skip.Initialize(mBTEngine->ScreenSize.x - 150, 10, 140, 40);

	bt_GameOver_MainMenuGo.Initialize(mBTEngine->ScreenSize.x - 700, mBTEngine->ScreenSize.y - 160, 650, 120);

	//신호등 생성
	mSignalLight.SetBoxSize(
		mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Signal1)->Width,
		mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Signal1)->Height);
	mSignalLight.PosX = mSignalRegenPos;
	mSignalLight.PosY = 233;
}

void GameManager::ReleaseAll(HWND hWnd)
{
	//폰트
	RemoveFontResource(PATH_FONT);

	//사운드
	mSoundManager->DataRelease();
	mSoundManager->Release(hWnd);

	//데이터 매니저
	mDataManager->DataRelease();

	delete mDataManager;
	delete mSoundManager;
}

#pragma endregion

#pragma region 씬 그리기

void GameManager::DrawStationBackGround(StationNode* currStation)
{
	// 하늘 (시간대)
	int skyIdx = GetNearBusTimeIndexByTime(mCurrTime);
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Background1 + skyIdx), 0, 0, 0.8, 0.5);

	// 뒷 배경 (행정 구역)
	int backCityIdx = (int)EImgSrcIdx::SeoulStation + currStation->DistrictID - 1;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex(backCityIdx), 0, 0, 0.8, 0.8, 1);

	// 도로
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Road), 0, 535, 1.2, 1.2);

	// 정거장 (시골 / 도시)
	int districtIdx = (int)EImgSrcIdx::Station1 + mDataManager->GetStationImageIdById(currStation->StationID);
	int centerX = (mBTEngine->ScreenSize.x / 2) - (mDataManager->GetSpriteByIndex(districtIdx)->Width / 2);
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex(districtIdx), centerX, 216, 1, 1, 1);
}
void GameManager::DrawStationClock(StationNode* currStation)
{
	POINT ClockPos = { 0,20 };
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::ClockLocationBB), ClockPos.x, ClockPos.y, 0.8, 0.8, 1);
	ClockPos.x += 65;
	ClockPos.y += 38;
	mBTEngine->btDrawText(ClockPos.x, ClockPos.y, 150, 50, 50, 900, TA_LEFT, RGB(255, 255, 255), "%02d:%02d", MergeTimeToHour(mCurrTime), MergeTimeToMin(mCurrTime));
	ClockPos.x += 170;
	mBTEngine->btDrawText(ClockPos.x, ClockPos.y, 130, 50, 50, 900, TA_LEFT, RGB(255, 255, 255), "%s", mDataManager->GetStationNameDataById(currStation->StationID));
	if (mSelectStationID > 0)
	{
		mBTEngine->btDrawText(378, 58, 130, 50, 50, 900, TA_LEFT, RGB(255, 255, 255), "%s", mDataManager->GetStationNameDataById(mSelectStationID));
	}

	int centerX = (mBTEngine->ScreenSize.x / 2) - (mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MiniBoard)->Width / 2 * 0.76);
	int bottomY = mBTEngine->ScreenSize.y - mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MiniBoard)->Height * 1.4;
	bottomY -= 10;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MiniBoard), centerX, bottomY, 0.76, 1.4, 1);

}
void GameManager::DrawStationNodeInfo(StationNode* currStation)
{
	mBTEngine->btDrawLine(573, 684, 573, 821, RGB(255, 234, 0));
	mBTEngine->btDrawLine(574, 684, 574, 821, RGB(255, 234, 0));
	mBTEngine->btDrawLine(575, 684, 575, 821, RGB(255, 234, 0));

	POINT NodePos = { 375 , 660 };
	for (int aroundIdx = 4 * mPage; aroundIdx < 4 * (mPage + 1); aroundIdx++)
	{
		//현재 정거장 > 인접 정거장
		AroundNode instAround = currStation->AroundList[aroundIdx];
		if (instAround.StationID <= 0) { continue; }

		NodePos.y += 25;
		bt_Station_Select[aroundIdx % 4].Initialize(NodePos.x, NodePos.y, 180, 25);

		if (mLinkedStationID == aroundIdx)
		{
			mBTEngine->btDrawRect(bt_Station_Select[aroundIdx % 4].object, RGB(255, 80, 7));
		}

		mBTEngine->btDrawText(NodePos.x, NodePos.y, NodePos.x + 30, NodePos.y + 25, 25, 1, TA_LEFT, RGB(255, 255, 255), "%s 행", mDataManager->GetStationNameDataById(instAround.StationID));

		int nearTimeIndex = GetNearBusTimeIndex(currStation->AroundList[aroundIdx].BusTimeTable, mCurrTime);

		//남은 시간표 없음
		NodePos.x += 110;
		if (nearTimeIndex < 0)
		{
			mBTEngine->btDrawText(NodePos.x - 3, NodePos.y + 3, NodePos.x + 30, NodePos.y + 25, 17, 1, TA_LEFT, RGB(254, 48, 62), "배차 없음");
		}
		else
		{
			int departureTime = currStation->AroundList[aroundIdx].BusTimeTable[nearTimeIndex].DepartureTime;
			mBTEngine->btDrawText(NodePos.x, NodePos.y, NodePos.x + 30, NodePos.y + 25, 25, 1, TA_LEFT, RGB(82, 152, 212), "%02d:%02d", MergeTimeToHour(departureTime), MergeTimeToMin(departureTime));
		}
		NodePos.x -= 110;
	}
}

void GameManager::OnClickedPageButton()
{
	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		if (bt_Station_PagePrev.IsCollided(mBTEngine->MousePositionCT))
		{
			mPage -= 1;
			if (mPage < 0) { mPage = 0; }
		}
		if (bt_Station_PageNext.IsCollided(mBTEngine->MousePositionCT))
		{
			mPage += 1;
			if (mPage >= mTotalPage) { mPage = mTotalPage - 1; }
		}
	}
	mBTEngine->btDrawText(180 + 200, 790, 35, 35, 35, 100, TA_LEFT, RGB(255, 255, 255), "<");
	mBTEngine->btDrawText(219 + 200, 795, 314, 25, 25, 100, TA_LEFT, RGB(255, 255, 255), "(%d / %d)", mPage + 1, mTotalPage);
	mBTEngine->btDrawText(314 + 200, 790, 35, 35, 35, 100, TA_RIGHT, RGB(255, 255, 255), ">");
}
void GameManager::OnClickedNodeSelectButton(StationNode* currStation)
{
	//선택 안된 상태 버튼 
	int witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGray)->Width;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGray), mBTEngine->ScreenSize.x - witdh - witdh / 2, witdh, 0.8, 0.8, 1);
	witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::RedArrow)->Width;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::RedArrow), mBTEngine->ScreenSize.x - witdh - witdh / 2, 255, 0.8, 0.8, 1);

	//버튼 입력 체크
	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		for (int index = 0; index < 4; index++)
		{
			if (bt_Station_Select[index].IsCollided(mBTEngine->MousePositionCT) == false) { continue; }
			
			if (currStation->AroundList[(mPage * 4) + index].StationID <= 0)
			{
				mLinkedStationID = -1;
				continue;
			}

			int nearBusTime = GetNearBusTimeIndex(currStation->AroundList[(mPage * 4) + index].BusTimeTable, mCurrTime);
			if (nearBusTime<0)
			{
				mLinkedStationID = -1;
				continue;
			}

			mLinkedStationID = (mPage * 4) + index;
			break;
		}
	}

	//노드 선택 한 경우
	if (mLinkedStationID >= 0)
	{
		//예상 도착 시간 표시
		mSelectStationID = currStation->AroundList[mLinkedStationID].StationID;
		int nearBusIdx = GetNearBusTimeIndex(currStation->AroundList[mLinkedStationID].BusTimeTable, mCurrTime);

		if (nearBusIdx < 0)
		{
			mSelectStationID = -1;
			return;
		}

		int departureTime = currStation->AroundList[mLinkedStationID].BusTimeTable[nearBusIdx].DepartureTime;
		int arrivalTime = currStation->AroundList[mLinkedStationID].BusTimeTable[nearBusIdx].ArrivalTime;

		POINT NodePos = { 594  , 680 };
		mBTEngine->btDrawText(NodePos.x, 685, 600, 80, 27, 100, TA_LEFT, RGB(255, 234, 0),
			"%s 행 도착 예정 시간 [%02d:%02d]", mDataManager->GetStationNameDataById(mSelectStationID), MergeTimeToHour(arrivalTime), MergeTimeToMin(arrivalTime));

		//링크 정거장 선택
		StationNode selectStation = *mDataManager->GetStationNodeByID(currStation->AroundList[mLinkedStationID].StationID);

		//출발 시간, 변화 가능한 이동 시간
		mSelectDepartureTime = departureTime;
		mExpectArrivalTime = arrivalTime;
		mSelectElapseTime = arrivalTime - departureTime;
		mSelectEventID = selectStation.EventID;

		int nodeSize = 100;
		//링크 정거장 배차 시간표 출력
		NodePos.y = 720;
		for (int aroundIdx = 0; aroundIdx < LINK_COUNT; aroundIdx++)
		{
			AroundNode instAround = selectStation.AroundList[aroundIdx];

			NodePos.x = 594 + (300 * (aroundIdx / 5));

			if (instAround.StationID <= 0) { continue; }
			mBTEngine->btDrawText(NodePos.x, NodePos.y, nodeSize, 20, 20, 100, TA_LEFT, RGB(255, 255, 255), "%s 행", mDataManager->GetStationNameDataById(instAround.StationID));

			int nearTimeIndex = GetNearBusTimeIndex(instAround.BusTimeTable, arrivalTime);
			int prevTimeIndex = nearTimeIndex - 1;
			NodePos.x += nodeSize;
			if (prevTimeIndex < 0)
			{
				mBTEngine->btDrawText(NodePos.x, NodePos.y + 2, nodeSize, 20, 15, 100, TA_LEFT, RGB(254, 48, 62), "배차 없음");
			}
			else
			{
				int departureTime = instAround.BusTimeTable[prevTimeIndex].DepartureTime;
				int arrivalTime = instAround.BusTimeTable[prevTimeIndex].ArrivalTime;
				mBTEngine->btDrawText(
					NodePos.x, NodePos.y,
					nodeSize, 20,
					20, 100,
					TA_LEFT, RGB(254, 48, 62),
					"%02d:%02d",
					MergeTimeToHour(departureTime),
					MergeTimeToMin(departureTime)
				);
			}

			NodePos.x += nodeSize;
			if (nearTimeIndex < 0)
			{
				mBTEngine->btDrawText(NodePos.x, NodePos.y, nodeSize, 20, 20, 100, TA_LEFT, RGB(255, 255, 255), "배차 없음");
			}
			else
			{
				int departureTime = instAround.BusTimeTable[nearTimeIndex].DepartureTime;
				int arrivalTime = instAround.BusTimeTable[nearTimeIndex].ArrivalTime;
				mBTEngine->btDrawText(
					NodePos.x, NodePos.y,
					nodeSize, 20,
					20, 100,
					TA_LEFT, RGB(255, 255, 255),
					"%02d:%02d",
					MergeTimeToHour(departureTime),
					MergeTimeToMin(departureTime)
				);
			}
			NodePos.y += 20;

			if (aroundIdx == 0) { continue; }
			if (aroundIdx % 4 == 0)
			{
				NodePos.y = 720;
			}
		}
	}
}

void GameManager::OnClickedNextButton()
{
	if (mLinkedStationID >= 0)
	{
		//선택 된 상태 버튼 
		int witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGreen)->Width;
		bt_Station_Next.Initialize(mBTEngine->ScreenSize.x - witdh - witdh / 2, 233, 276, 178);
		mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGreen), mBTEngine->ScreenSize.x - witdh - witdh / 2, witdh, 0.8, 0.8, 1);

		witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GreenArrow)->Width;
		mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GreenArrow), mBTEngine->ScreenSize.x - witdh - witdh / 2, 255, 0.8, 0.8, 1);

		//선택된 다음 노드 확인
		if (mSelectStationID < 0) { return; }
		if (!mBTEngine->btInputKeyDown(VK_LBUTTON)) { return; }
		if (!bt_Station_Next.IsCollided(mBTEngine->MousePositionCT)) { return; }

		//mSoundManager->StopWAV(BREAK);
		//mSoundManager->PlayWAV_LOOP(DEPARTURE);
		//mBusEffect.Init(mDataManager->GetStationNodeByID(mSelectStationID)->DistrictID, 500 - mBTEngine->ScreenSize.x, 275);
		//mbOnNext = true;
		//mbOnBusEffect = false;
		//다음 StationID 설정 

		//출발 : 현재시간을 출발 시간으로 변경
		mCurrTime = mSelectDepartureTime;

		mPage = 0;
		mTotalPage = 0;

		//현재 정거장의 확정 이벤트 확인
		if (mSelectEventID <= 0)
		{
			mGameState = (int)EGameState::GS_BusMove_Game_Start;
		}
		else
		{
			mGameState = (int)EGameState::GS_BusMove_Event_Start;
		}

		mLinkedStationID = -1;
		return;
	}
}

bool GameManager::CheckGameOverState(StationNode* currStation)
{
	// 남은 버스 시간 갯수
	int remainBusTimeCount = 0;
	for (int index = 0; index < LINK_COUNT; index++)
	{
		int nearTimeIndex = GetNearBusTimeIndex(currStation->AroundList[index].BusTimeTable, mCurrTime);
		if (nearTimeIndex >= 0)
		{
			remainBusTimeCount++;
		}
	}

	//부산 도착
	if (mCurrStationID >= 34)
	{
		mGameState = (int)EGameState::GS_Ending_Start;
		return true;
	}

	//버스 없음
	if (remainBusTimeCount == 0)
	{
		mGameState = (int)EGameState::GS_GameOver_Start;
		return true;
	}

	//24시 & 부산 X
	if (mCurrTime >= 24 * 60)
	{
		if (mCurrStationID != 34)
		{
			mGameState = (int)EGameState::GS_GameOver_Start;
			return true;
		}
	}
	return false;
}

///이동 공통 부분
void GameManager::DrawBusMoving(int districtID, float lerpTime)
{
	// 하늘
	int skyIdx = GetNearBusTimeIndexByTime(mCurrTime);
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Background1 + skyIdx), 0, 0, 0.8, 0.5);

	// 지역
	float dTime = mBTEngine->GetDeltaTime() * lerpTime;
	switch (districtID)
	{
	case 1:	//서울
	{
		int index = ScrollObjIndex(EImgSrcIdx::Seoul_BCity);
		int loopCount = ScrollObjIndex(EImgSrcIdx::Seoul_FCity);
		for (; index <= loopCount; index++)
		{
			mScrollObjList[index].PlayScroll(dTime);
		}
	}
	break;
	case 2://충청
	{
		int index = ScrollObjIndex(EImgSrcIdx::Chung_BSan);
		int loopCount = ScrollObjIndex(EImgSrcIdx::Chung_Grass);
		for (; index <= loopCount; index++)
		{
			mScrollObjList[index].PlayScroll(dTime);
		}
	}
	break;
	case 3://부산
	{
		int index = ScrollObjIndex(EImgSrcIdx::Busan_BCity);
		int loopCount = ScrollObjIndex(EImgSrcIdx::Busan_FCity);
		for (; index <= loopCount; index++)
		{
			mScrollObjList[index].PlayScroll(dTime);
			if (index == ScrollObjIndex(EImgSrcIdx::Busan_BCity))
			{
				mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Busan_Ocean), 0, 319, 0.8, 0.8, 1);
			}
		}
	}
	break;
	default:
		break;
	}
	// 도로
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Road), 0, 559, 1, 1);

	// 펜스
	mScrollObjList[0].PlayScroll(dTime);

	// 버스, 바퀴
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::BUS1 + districtID - 1), 60, 440, 0.8, 0.8, 1);
	//우병택 : 애니메이션을 후에 만드는 것 생성
	mBusTire.PlayAnimation(dTime, 60 + 120, 440 + 115, 0.8, 0.8);
}

///미니맵
void GameManager::DrawMiniMap(int stationID, int selectID)
{
	mBTEngine->btDrawSpriteAlphablend
	(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MapBoard), 5, 55, 0.8, 0.8, 1);

	//배경 지도
	mBTEngine->btDrawSpriteAlphablend
	(mDataManager->GetMiniMapByID(0), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);

	//현재 지역
	if (stationID > 0)
	{
		mBTEngine->btDrawSpriteAlphablend
		(mDataManager->GetMiniMapByID((stationID * 2) - 1), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);
	}

	//선택 지역
	if (selectID > 0)
	{
		mBTEngine->btDrawSpriteAlphablend
		(mDataManager->GetMiniMapByID(selectID * 2), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);
	}
}

///팝업 창 그리기
void GameManager::DrawMoveResultPopup(EGameState nextState, int arrivalTime_actual)
{
	BTSprite* sprite = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::PopupBoard);
	int posX = (mBTEngine->ScreenSize.x / 2) - (sprite->Width / 2 * 1);
	int posY = (mBTEngine->ScreenSize.y / 2) - (sprite->Height / 2 * 1);

	//Panel
	mBTEngine->btDrawSpriteAlphablend(sprite, posX, posY, 1, 1, 1);

	//도착 예측 시간
	mBTEngine->btDrawText(
		posX - 155, (mBTEngine->ScreenSize.y / 2) - 80,
		sprite->Width, 100,
		30, 0,
		DT_CENTER, RGB(255, 255, 255),
		"예상 도착 시간");
	mBTEngine->btDrawText(
		posX - 155, (mBTEngine->ScreenSize.y / 2) - 30,
		sprite->Width, 100,
		40, 0,
		DT_CENTER, RGB(255, 255, 255),
		"%02d:%02d", MergeTimeToHour(mExpectArrivalTime), MergeTimeToMin(mExpectArrivalTime));

	//실제 도착 시간
	mBTEngine->btDrawText(
		posX + 145, (mBTEngine->ScreenSize.y / 2) - 80,
		sprite->Width, 100,
		30, 0,
		DT_CENTER, RGB(255, 255, 255),
		"실제 도착 시간");

	//도착 시간 컬러 설정
	int r = 255, g = 255, b = 255;
	if (arrivalTime_actual < mExpectArrivalTime)
	{
		r = 82, g = 152, b = 212;
	}
	else if (arrivalTime_actual > mExpectArrivalTime)
	{
		r = 254, g = 48, b = 62;
	}
	mBTEngine->btDrawText(
		posX + 145, (mBTEngine->ScreenSize.y / 2) - 30,
		sprite->Width, 100,
		40, 0,
		DT_CENTER, RGB(r, g, b),
		"%02d:%02d", MergeTimeToHour(arrivalTime_actual), MergeTimeToMin(arrivalTime_actual));

	bt_Popup_Ok.Initialize(
		(mBTEngine->ScreenSize.x / 2) - 85, (mBTEngine->ScreenSize.y / 2) + 70,
		150, 80);
	mBTEngine->btDrawText(
		bt_Popup_Ok.object.left, bt_Popup_Ok.object.bottom - 70,
		150, 80,
		45, 0,
		DT_CENTER, RGB(242, 180, 1),
		"확인");
	//mBTEngine->btDrawRect(bt_Popup_Ok.object, RGB(255, 0, 255));

	if (mBTEngine->btInputKeyDown(VK_LBUTTON)
		&& bt_Popup_Ok.IsCollided(mBTEngine->MousePositionCT))
	{
		mCurrTime = arrivalTime_actual;
		mCurrStationID = mSelectStationID;

		mGameState = (int)nextState;
		return;
	}
}

/// 버스 도착, 출발
bool GameManager::DrawBusEffect(BusEffect* busEffect)
{
	//버스 이미지
	mBTEngine->btDrawSpriteAlphablend(
		mDataManager->GetSpriteByIndex((int)EImgSrcIdx::BUS1 + busEffect->DistrictID - 1),
		busEffect->PosX, busEffect->PosY,
		1.5, 1.5,
		1);

	mBusTire.PlayAnimation(
		mBTEngine->GetDeltaTime() * (int)!busEffect->GetStoped(),
		busEffect->PosX + 225, busEffect->PosY + 210,
		1.5, 1.5);

	busEffect->Move(mBTEngine->GetDeltaTime());
	if (busEffect->PosX > 200 && busEffect->GetChecked() == false)
	{
		// 버스 멈춤
		mSoundManager->StopWAV(DEPARTURE);
		mSoundManager->PlayWAV_ONCE(BREAK);
		busEffect->PauseBus();
	}
	if (busEffect->GetAniTime() > 1 && busEffect->GetStoped() == true)
	{
		// 버스 다시 출발
		mSoundManager->StopWAV(BREAK);
		mSoundManager->PlayWAV_ONCE(DEPARTURE);
		busEffect->StartBus();
	}
	if (busEffect->PosX > mBTEngine->ScreenSize.x)
	{
		return false;
	}
	return true;
}

#pragma endregion

#pragma region 기타 정보 획득
/// 다음 배차 Index 획득
int GameManager::GetNearBusTimeIndex(BusTime table[], int currTime)
{
	for (int tableIdx = 0; tableIdx < TIMETABLE_COUNT; tableIdx++)
	{
		//오름차순 정리 필요
		if (currTime > table[tableIdx].DepartureTime) { continue; }
		return tableIdx;
	}
	return -1;
}

/// 시간대 별 배경 Index 획득
int GameManager::GetNearBusTimeIndexByTime(int time)
{
	//아침
	int idx = 0;

	//새벽 & 오후
	//5:00 ~ 7:00, 15:00 ~ 18:00
	if ((time >= START_TIME && time < 7 * 60)
		|| (time >= 15 * 60 && time < 18 * 60))
	{
		idx = 1; //새벽 + 오후
	}

	//저녁
	//18:00~
	else if (time >= 18 * 60)
	{
		idx = 2;
	}

	return idx;
}

///모든 키를 입력 받는 테스트 함수
void GameManager::TestKeyUpdate()
{
	if (mBTEngine->btInputKeyDown(VK_Q))
	{
		//타이틀 씬으로
		mGameState = (int)EGameState::GS_MainMenu_Start;
		return;
	}
	if (mBTEngine->btInputKeyDown(VK_W))
	{
		//엔딩 씬으로
		mGameState = (int)EGameState::GS_Ending_Start;
		return;
	}

	////신호등 속도 조절
	//if (mBTEngine->btInputKey(VK_U))//증가
	//{
	//	mSignalSpeed += 1;
	//}
	//if (mBTEngine->btInputKey(VK_H))//감소
	//{
	//	mSignalSpeed -= 1;
	//}

	////신호등 간격 조절
	//if (mBTEngine->btInputKey(VK_I))//증가
	//{
	//	mSignalRegenPos += 1;
	//}
	//if (mBTEngine->btInputKey(VK_J))//감소
	//{
	//	mSignalRegenPos -= 1;
	//}

	////Limit Count 생성 보정 값
	//if (mBTEngine->btInputKeyDown(VK_O))//증가
	//{
	//	mPushCountCorrection++;
	//}
	//if (mBTEngine->btInputKeyDown(VK_K))//감소
	//{
	//	mPushCountCorrection--;
	//}

	//현재 시간 변경
	if (mBTEngine->btInputKeyDown(VK_P))//증가
	{
		mCurrTime += 10;
	}
	if (mBTEngine->btInputKeyDown(VK_L))//감소
	{
		mCurrTime -= 10;
	}
}
void GameManager::ShowTestInfo()
{
	//정보출력 쿄쿄
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 35, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "신호등 속도 : -H[%.0f]U+", mSignalSpeed);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 60, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "신호등 간격 : -J[%d]I+", mSignalRegenPos);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 85, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "SpacePerSec : -K[%d]O+", mPushCountCorrection);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 110, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "타이틀 : Q");
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 135, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "엔  딩 : W");
}
#pragma endregion