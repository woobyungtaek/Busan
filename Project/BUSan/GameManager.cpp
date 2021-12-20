#include "pch.h"

GameManager::GameManager() {}
GameManager::~GameManager() {}

//�ʱ�ȭ
void GameManager::InitGameManager(BTEngine* engine, HWND hWnd)
{
	mBTEngine = engine;
	mDataManager = new DataManager();
	mSoundManager = new SoundManager();
	mSoundManager->Initiate(hWnd);

	mGameState = (int)EGameState::GS_MainLoad;
}

//���� ��
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
	//������ �ε�
	mDataManager->LoadStationDataListFromFile(STATION_DATA_PATH);
	mDataManager->LoadImageDataFromFile(mBTEngine);
	mDataManager->LoadMiniMapDataFromFile(mBTEngine);

	//���� �ε�
	mSoundManager->DataLoadAllWavByFile();						// wav���� ���� �ε�
	//mSoundManager->DataLoad_MP3(MediaFileName[OPENING]);		// mp3���� �� �� �ε�(���ϸ�)

	//���� ������Ʈ ����
	CreateGameObject();

	//���� ����
	mGameState = (int)EGameState::GS_Intro_Start;
	//mBTEngine->btTextOut(30, 30, "������ �ε� ��");
}

void GameManager::Scene_Intro_Start()
{
	//��Ʈ�� �� ���Ժ�
	mStoryPage = 0;
	mTextIdx = 0;

	//��Ʈ�� BGM
	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(OPENING);

	mGameState = (int)EGameState::GS_Intro;
	//mBTEngine->btTextOut(30, 30, "��Ʈ�� ���� ��");
}
void GameManager::Scene_Intro()
{
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Intro_0 + mStoryPage), 0, 0, 0.8, 0.8, 1);
	//mBTEngine->btDrawRect(bt_Intro_Skip.object, RGB(255, 0, 255));
	mBTEngine->btDrawText(bt_Intro_Skip.object, 35, 900, TA_RIGHT | TA_BOTTOM, RGB(0, 0, 0), "Skip >>");

	//text index need
	mBTEngine->btDrawText(0, 750, mBTEngine->ScreenSize.x, 35, 35, 100, DT_CENTER, RGB(0, 0, 0),
		"%s", mDataManager->GetStoryText(mTextIdx));

	//��ư�� ������ ��
	if (mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		mTextIdx++;

		//��ȭ ���� ���� Index
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
	//�÷��̾� �� �ʱ�ȭ
	mCurrTime = START_TIME;			// 05:00�� ���
	mCurrStationID = START_STATION;	// 1�� ���￪ ���
	mLinkedStationID = -1;
	mLerpTime = 1;

	bt_MainMenu_Start.Initialize(707, 401, 215, 68);
	bt_MainMenu_Exit.Initialize(707, 476, 215, 60);
	bt_MainMenu_BackIntro.Initialize(506, 539, 425, 61);

	//BGM ����
	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(TITLE);

	mGameState = (int)EGameState::GS_MainMenu;
	//mBTEngine->btTextOut(30, 30, "���� �޴� ���� ��");
}
void GameManager::Scene_MainMenu()
{
	//Ÿ��Ʋ �� �׸���
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Title), 0, 0, 0.8, 0.8, 1);

	//mBTEngine->btTextOut(30, 30, "���� �޴� ��");

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
			//���� ����
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

	//�� ��� ī��Ʈ �� ������ ����
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

	//������ ��ư �Է� �� ����
	OnClickedPageButton();

	//���� ���� �̵�
	mbOnBusEffect = DrawBusEffect(&mBusEffect);
	if (mbOnBusEffect == true)
	{
		return;
	}
	//else
	//{
	//	if (mbOnNext == true)
	//	{
	//		//��� : ����ð��� ��� �ð����� ����
	//		mCurrTime = mSelectDepartureTime;

	//		mPage = 0;
	//		mTotalPage = 0;

	//		//���� �������� Ȯ�� �̺�Ʈ Ȯ��
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
	mSelectElapseTime = 0;//Game���� �ٽ� ���ȴ�.
	mSignalLight.PosX = mSignalRegenPos;
	mSignalLight.SetRandomSignal();

	mStopTime = 0;
	mLerpTime = 1;

	mSoundManager->StopAllWAV();
	mSoundManager->PlayWAV_LOOP(MINIGAME);

	mGameState = (int)EGameState::GS_BusMove_Game;
	//mBTEngine->btTextOut(30, 30, "���� �̵� ���� ������");
}
void GameManager::Scene_BusMoveGame()
{
	BTSprite* drawSprite = nullptr;

	//��� �׸���
	int districtID = mDataManager->GetStationNodeByID(mSelectStationID)->DistrictID;
	DrawBusMoving(districtID, mLerpTime);

	//1�ʿ� 5�о� ElapseTime�� ���� �Ѵ�.
	mRealTime += mBTEngine->GetDeltaTime();
	if (mRealTime > 0.5 && IsMovePopup == false)
	{
		//1�ʿ� 10�о� �ð��� ����
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

	//Ű�Է� 
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
		"���� �ð�  %02d:%02d", MergeTimeToHour(expectTime), MergeTimeToMin(expectTime));

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
		//�˾� �����
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
	//mBTEngine->btTextOut(30, 30, "���� �̵� �̺�Ʈ ������");
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
		//�̺�Ʈ ��ȭ ��
		mOffsetY += (mBTEngine->ScreenSize.y) * mBTEngine->GetDeltaTime();
		if (mOffsetY >= mBTEngine->ScreenSize.y)
		{
			mOffsetY = mBTEngine->ScreenSize.y;
		}
	}

#pragma region �̺�Ʈ ��ȭ �׸���
	int textPosX = 105;
	int ImageID = mSelectEventID;

	//�̺�Ʈ ��ȭ
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Event_Fight + mSelectEventID - 1),
		900, 150 + (mBTEngine->ScreenSize.y) - mOffsetY,
		0.75, 0.75);

	//�̺�Ʈ ���� �̹���
	mBTEngine->btDrawSpriteTransparent(
		mDataManager->GetSpriteByIndex(
			(int)EImgSrcIdx::EventCloseBT), 1360, (mBTEngine->ScreenSize.y) + 105 - mOffsetY, 0.8, 0.8);
	//�̺�Ʈ ���� ��ư
	bt_Event_Close.Initialize(1360, (mBTEngine->ScreenSize.y) + 105 - mOffsetY, 46, 50);

	//����
	mBTEngine->btDrawText(
		825 + textPosX, 650 + (mBTEngine->ScreenSize.y) - mOffsetY,
		711 + textPosX, 100,
		30, 0,
		DT_LEFT, RGB(0, 0, 0),
		"%s", mSelectEventData->Title);

	//�ð� ǥ��
	char buffer[30];
	int r = 0;
	int g = 0;
	int b = 0;
	if (mSelectEventData->Time < 0)
	{
		sprintf_s(buffer, "�̵� �ð�: %d�� ����", mSelectEventData->Time * -1);
		//r = 0; g = 82; b = 255;
	}
	else
	{
		sprintf_s(buffer, "�̵� �ð�: %d�� ����", mSelectEventData->Time);
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
			//�˾� �����
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
	//mBTEngine->btTextOut(30, 30, "���ӿ��� ������");
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

	//���� ���� ��� �����ϱ�
	if (mCurrTime <= (16 * 60))
	{
		//True����
		mEndingGrade = 1;
		mSoundManager->PlayWAV_LOOP(ENDING1);

		mTextStartIdx = (int)EStoryTextIdx::Ending1_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending1_4;
	}
	else if (mCurrTime > (16 * 60) && mCurrTime <= (18 * 60))
	{
		//���� 2
		mEndingGrade = 2;
		mSoundManager->PlayWAV_LOOP(ENDING2);

		mTextStartIdx = (int)EStoryTextIdx::Ending2_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending2_5;
	}
	else if (mCurrTime > (18 * 60) && mCurrTime <= (21 * 60))
	{
		//���� 3
		mEndingGrade = 3;
		mSoundManager->PlayWAV_LOOP(ENDING3);

		mTextStartIdx = (int)EStoryTextIdx::Ending3_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending3_3;
	}
	else if (mCurrTime > (21 * 60))
	{
		//���� 4
		mEndingGrade = 4;
		mSoundManager->PlayWAV_LOOP(ENDING4);

		mTextStartIdx = (int)EStoryTextIdx::Ending4_1;
		mTextEndIdx = (int)EStoryTextIdx::Ending4_4;
	}

	mGameState = (int)EGameState::GS_Ending;
	//mBTEngine->btTextOut(30, 30, "���� ���� ������");
}
void GameManager::Scene_GameEnding()
{
	if (mbStoryInput == true && mBTEngine->btInputKeyDown(VK_LBUTTON))
	{
		mStoryPage = 5; // ��ȭ ����
		mTextIdx += 1;
	}

	//�ڵ����� �ѱ��.
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

	//���� ���
	//ending page 1 = ���, �ð�
	if (mStoryPage < 5)
	{
		if (mStoryPage >= 1)
		{
			mBTEngine->btDrawText(200, mBTEngine->ScreenSize.y / 2 - 90, mBTEngine->ScreenSize.x, 50, 50, 900, DT_LEFT, RGB(255, 255, 255), "�λ� ���� �ð�");
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
			mBTEngine->btDrawText(-450 + 200, mBTEngine->ScreenSize.y / 2 - 45, mBTEngine->ScreenSize.x, 70, 70, 900, DT_RIGHT, RGB(255, 255, 255), "���");
		}
		if (mStoryPage >= 4)
		{
			mBTEngine->btDrawText(0, mBTEngine->ScreenSize.y - 100, mBTEngine->ScreenSize.x, 100, 35, 100, DT_CENTER, RGB(255, 255, 255), "Ŭ���ؼ� ��������");
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

#pragma region ����/���� �Լ�

void GameManager::CreateGameObject()
{
	//��ũ�� ������Ʈ ����
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
	//�ִ� ������Ʈ ����
	mBTEngine->btLoadAniSpriteFromFile(&mBusTire, true, ImgSrcPath[(int)EImgSrcIdx::BusTire], 410, 90);
	mBusTire.SetAnimation(15, 1, 0, 1, -1);

	//��ư ������Ʈ ����
	bt_Intro_Skip.Initialize(mBTEngine->ScreenSize.x - 150, 10, 140, 40);

	bt_GameOver_MainMenuGo.Initialize(mBTEngine->ScreenSize.x - 700, mBTEngine->ScreenSize.y - 160, 650, 120);

	//��ȣ�� ����
	mSignalLight.SetBoxSize(
		mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Signal1)->Width,
		mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Signal1)->Height);
	mSignalLight.PosX = mSignalRegenPos;
	mSignalLight.PosY = 233;
}

void GameManager::ReleaseAll(HWND hWnd)
{
	//��Ʈ
	RemoveFontResource(PATH_FONT);

	//����
	mSoundManager->DataRelease();
	mSoundManager->Release(hWnd);

	//������ �Ŵ���
	mDataManager->DataRelease();

	delete mDataManager;
	delete mSoundManager;
}

#pragma endregion

#pragma region �� �׸���

void GameManager::DrawStationBackGround(StationNode* currStation)
{
	// �ϴ� (�ð���)
	int skyIdx = GetNearBusTimeIndexByTime(mCurrTime);
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Background1 + skyIdx), 0, 0, 0.8, 0.5);

	// �� ��� (���� ����)
	int backCityIdx = (int)EImgSrcIdx::SeoulStation + currStation->DistrictID - 1;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex(backCityIdx), 0, 0, 0.8, 0.8, 1);

	// ����
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Road), 0, 535, 1.2, 1.2);

	// ������ (�ð� / ����)
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
		//���� ������ > ���� ������
		AroundNode instAround = currStation->AroundList[aroundIdx];
		if (instAround.StationID <= 0) { continue; }

		NodePos.y += 25;
		bt_Station_Select[aroundIdx % 4].Initialize(NodePos.x, NodePos.y, 180, 25);

		if (mLinkedStationID == aroundIdx)
		{
			mBTEngine->btDrawRect(bt_Station_Select[aroundIdx % 4].object, RGB(255, 80, 7));
		}

		mBTEngine->btDrawText(NodePos.x, NodePos.y, NodePos.x + 30, NodePos.y + 25, 25, 1, TA_LEFT, RGB(255, 255, 255), "%s ��", mDataManager->GetStationNameDataById(instAround.StationID));

		int nearTimeIndex = GetNearBusTimeIndex(currStation->AroundList[aroundIdx].BusTimeTable, mCurrTime);

		//���� �ð�ǥ ����
		NodePos.x += 110;
		if (nearTimeIndex < 0)
		{
			mBTEngine->btDrawText(NodePos.x - 3, NodePos.y + 3, NodePos.x + 30, NodePos.y + 25, 17, 1, TA_LEFT, RGB(254, 48, 62), "���� ����");
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
	//���� �ȵ� ���� ��ư 
	int witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGray)->Width;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGray), mBTEngine->ScreenSize.x - witdh - witdh / 2, witdh, 0.8, 0.8, 1);
	witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::RedArrow)->Width;
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::RedArrow), mBTEngine->ScreenSize.x - witdh - witdh / 2, 255, 0.8, 0.8, 1);

	//��ư �Է� üũ
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

	//��� ���� �� ���
	if (mLinkedStationID >= 0)
	{
		//���� ���� �ð� ǥ��
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
			"%s �� ���� ���� �ð� [%02d:%02d]", mDataManager->GetStationNameDataById(mSelectStationID), MergeTimeToHour(arrivalTime), MergeTimeToMin(arrivalTime));

		//��ũ ������ ����
		StationNode selectStation = *mDataManager->GetStationNodeByID(currStation->AroundList[mLinkedStationID].StationID);

		//��� �ð�, ��ȭ ������ �̵� �ð�
		mSelectDepartureTime = departureTime;
		mExpectArrivalTime = arrivalTime;
		mSelectElapseTime = arrivalTime - departureTime;
		mSelectEventID = selectStation.EventID;

		int nodeSize = 100;
		//��ũ ������ ���� �ð�ǥ ���
		NodePos.y = 720;
		for (int aroundIdx = 0; aroundIdx < LINK_COUNT; aroundIdx++)
		{
			AroundNode instAround = selectStation.AroundList[aroundIdx];

			NodePos.x = 594 + (300 * (aroundIdx / 5));

			if (instAround.StationID <= 0) { continue; }
			mBTEngine->btDrawText(NodePos.x, NodePos.y, nodeSize, 20, 20, 100, TA_LEFT, RGB(255, 255, 255), "%s ��", mDataManager->GetStationNameDataById(instAround.StationID));

			int nearTimeIndex = GetNearBusTimeIndex(instAround.BusTimeTable, arrivalTime);
			int prevTimeIndex = nearTimeIndex - 1;
			NodePos.x += nodeSize;
			if (prevTimeIndex < 0)
			{
				mBTEngine->btDrawText(NodePos.x, NodePos.y + 2, nodeSize, 20, 15, 100, TA_LEFT, RGB(254, 48, 62), "���� ����");
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
				mBTEngine->btDrawText(NodePos.x, NodePos.y, nodeSize, 20, 20, 100, TA_LEFT, RGB(255, 255, 255), "���� ����");
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
		//���� �� ���� ��ư 
		int witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGreen)->Width;
		bt_Station_Next.Initialize(mBTEngine->ScreenSize.x - witdh - witdh / 2, 233, 276, 178);
		mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GoIconGreen), mBTEngine->ScreenSize.x - witdh - witdh / 2, witdh, 0.8, 0.8, 1);

		witdh = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GreenArrow)->Width;
		mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::GreenArrow), mBTEngine->ScreenSize.x - witdh - witdh / 2, 255, 0.8, 0.8, 1);

		//���õ� ���� ��� Ȯ��
		if (mSelectStationID < 0) { return; }
		if (!mBTEngine->btInputKeyDown(VK_LBUTTON)) { return; }
		if (!bt_Station_Next.IsCollided(mBTEngine->MousePositionCT)) { return; }

		//mSoundManager->StopWAV(BREAK);
		//mSoundManager->PlayWAV_LOOP(DEPARTURE);
		//mBusEffect.Init(mDataManager->GetStationNodeByID(mSelectStationID)->DistrictID, 500 - mBTEngine->ScreenSize.x, 275);
		//mbOnNext = true;
		//mbOnBusEffect = false;
		//���� StationID ���� 

		//��� : ����ð��� ��� �ð����� ����
		mCurrTime = mSelectDepartureTime;

		mPage = 0;
		mTotalPage = 0;

		//���� �������� Ȯ�� �̺�Ʈ Ȯ��
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
	// ���� ���� �ð� ����
	int remainBusTimeCount = 0;
	for (int index = 0; index < LINK_COUNT; index++)
	{
		int nearTimeIndex = GetNearBusTimeIndex(currStation->AroundList[index].BusTimeTable, mCurrTime);
		if (nearTimeIndex >= 0)
		{
			remainBusTimeCount++;
		}
	}

	//�λ� ����
	if (mCurrStationID >= 34)
	{
		mGameState = (int)EGameState::GS_Ending_Start;
		return true;
	}

	//���� ����
	if (remainBusTimeCount == 0)
	{
		mGameState = (int)EGameState::GS_GameOver_Start;
		return true;
	}

	//24�� & �λ� X
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

///�̵� ���� �κ�
void GameManager::DrawBusMoving(int districtID, float lerpTime)
{
	// �ϴ�
	int skyIdx = GetNearBusTimeIndexByTime(mCurrTime);
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Background1 + skyIdx), 0, 0, 0.8, 0.5);

	// ����
	float dTime = mBTEngine->GetDeltaTime() * lerpTime;
	switch (districtID)
	{
	case 1:	//����
	{
		int index = ScrollObjIndex(EImgSrcIdx::Seoul_BCity);
		int loopCount = ScrollObjIndex(EImgSrcIdx::Seoul_FCity);
		for (; index <= loopCount; index++)
		{
			mScrollObjList[index].PlayScroll(dTime);
		}
	}
	break;
	case 2://��û
	{
		int index = ScrollObjIndex(EImgSrcIdx::Chung_BSan);
		int loopCount = ScrollObjIndex(EImgSrcIdx::Chung_Grass);
		for (; index <= loopCount; index++)
		{
			mScrollObjList[index].PlayScroll(dTime);
		}
	}
	break;
	case 3://�λ�
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
	// ����
	mBTEngine->btDrawSpriteTransparent(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::Road), 0, 559, 1, 1);

	// �潺
	mScrollObjList[0].PlayScroll(dTime);

	// ����, ����
	mBTEngine->btDrawSpriteAlphablend(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::BUS1 + districtID - 1), 60, 440, 0.8, 0.8, 1);
	//�캴�� : �ִϸ��̼��� �Ŀ� ����� �� ����
	mBusTire.PlayAnimation(dTime, 60 + 120, 440 + 115, 0.8, 0.8);
}

///�̴ϸ�
void GameManager::DrawMiniMap(int stationID, int selectID)
{
	mBTEngine->btDrawSpriteAlphablend
	(mDataManager->GetSpriteByIndex((int)EImgSrcIdx::MapBoard), 5, 55, 0.8, 0.8, 1);

	//��� ����
	mBTEngine->btDrawSpriteAlphablend
	(mDataManager->GetMiniMapByID(0), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);

	//���� ����
	if (stationID > 0)
	{
		mBTEngine->btDrawSpriteAlphablend
		(mDataManager->GetMiniMapByID((stationID * 2) - 1), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);
	}

	//���� ����
	if (selectID > 0)
	{
		mBTEngine->btDrawSpriteAlphablend
		(mDataManager->GetMiniMapByID(selectID * 2), MiniMapPosX, MiniMapPosY, MiniMapSize, MiniMapSize, 1);
	}
}

///�˾� â �׸���
void GameManager::DrawMoveResultPopup(EGameState nextState, int arrivalTime_actual)
{
	BTSprite* sprite = mDataManager->GetSpriteByIndex((int)EImgSrcIdx::PopupBoard);
	int posX = (mBTEngine->ScreenSize.x / 2) - (sprite->Width / 2 * 1);
	int posY = (mBTEngine->ScreenSize.y / 2) - (sprite->Height / 2 * 1);

	//Panel
	mBTEngine->btDrawSpriteAlphablend(sprite, posX, posY, 1, 1, 1);

	//���� ���� �ð�
	mBTEngine->btDrawText(
		posX - 155, (mBTEngine->ScreenSize.y / 2) - 80,
		sprite->Width, 100,
		30, 0,
		DT_CENTER, RGB(255, 255, 255),
		"���� ���� �ð�");
	mBTEngine->btDrawText(
		posX - 155, (mBTEngine->ScreenSize.y / 2) - 30,
		sprite->Width, 100,
		40, 0,
		DT_CENTER, RGB(255, 255, 255),
		"%02d:%02d", MergeTimeToHour(mExpectArrivalTime), MergeTimeToMin(mExpectArrivalTime));

	//���� ���� �ð�
	mBTEngine->btDrawText(
		posX + 145, (mBTEngine->ScreenSize.y / 2) - 80,
		sprite->Width, 100,
		30, 0,
		DT_CENTER, RGB(255, 255, 255),
		"���� ���� �ð�");

	//���� �ð� �÷� ����
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
		"Ȯ��");
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

/// ���� ����, ���
bool GameManager::DrawBusEffect(BusEffect* busEffect)
{
	//���� �̹���
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
		// ���� ����
		mSoundManager->StopWAV(DEPARTURE);
		mSoundManager->PlayWAV_ONCE(BREAK);
		busEffect->PauseBus();
	}
	if (busEffect->GetAniTime() > 1 && busEffect->GetStoped() == true)
	{
		// ���� �ٽ� ���
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

#pragma region ��Ÿ ���� ȹ��
/// ���� ���� Index ȹ��
int GameManager::GetNearBusTimeIndex(BusTime table[], int currTime)
{
	for (int tableIdx = 0; tableIdx < TIMETABLE_COUNT; tableIdx++)
	{
		//�������� ���� �ʿ�
		if (currTime > table[tableIdx].DepartureTime) { continue; }
		return tableIdx;
	}
	return -1;
}

/// �ð��� �� ��� Index ȹ��
int GameManager::GetNearBusTimeIndexByTime(int time)
{
	//��ħ
	int idx = 0;

	//���� & ����
	//5:00 ~ 7:00, 15:00 ~ 18:00
	if ((time >= START_TIME && time < 7 * 60)
		|| (time >= 15 * 60 && time < 18 * 60))
	{
		idx = 1; //���� + ����
	}

	//����
	//18:00~
	else if (time >= 18 * 60)
	{
		idx = 2;
	}

	return idx;
}

///��� Ű�� �Է� �޴� �׽�Ʈ �Լ�
void GameManager::TestKeyUpdate()
{
	if (mBTEngine->btInputKeyDown(VK_Q))
	{
		//Ÿ��Ʋ ������
		mGameState = (int)EGameState::GS_MainMenu_Start;
		return;
	}
	if (mBTEngine->btInputKeyDown(VK_W))
	{
		//���� ������
		mGameState = (int)EGameState::GS_Ending_Start;
		return;
	}

	////��ȣ�� �ӵ� ����
	//if (mBTEngine->btInputKey(VK_U))//����
	//{
	//	mSignalSpeed += 1;
	//}
	//if (mBTEngine->btInputKey(VK_H))//����
	//{
	//	mSignalSpeed -= 1;
	//}

	////��ȣ�� ���� ����
	//if (mBTEngine->btInputKey(VK_I))//����
	//{
	//	mSignalRegenPos += 1;
	//}
	//if (mBTEngine->btInputKey(VK_J))//����
	//{
	//	mSignalRegenPos -= 1;
	//}

	////Limit Count ���� ���� ��
	//if (mBTEngine->btInputKeyDown(VK_O))//����
	//{
	//	mPushCountCorrection++;
	//}
	//if (mBTEngine->btInputKeyDown(VK_K))//����
	//{
	//	mPushCountCorrection--;
	//}

	//���� �ð� ����
	if (mBTEngine->btInputKeyDown(VK_P))//����
	{
		mCurrTime += 10;
	}
	if (mBTEngine->btInputKeyDown(VK_L))//����
	{
		mCurrTime -= 10;
	}
}
void GameManager::ShowTestInfo()
{
	//������� ����
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 35, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "��ȣ�� �ӵ� : -H[%.0f]U+", mSignalSpeed);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 60, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "��ȣ�� ���� : -J[%d]I+", mSignalRegenPos);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 85, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "SpacePerSec : -K[%d]O+", mPushCountCorrection);
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 110, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "Ÿ��Ʋ : Q");
	mBTEngine->btDrawText(mBTEngine->ScreenSize.x - 350, 135, mBTEngine->ScreenSize.x, 25, 25, 100, TA_LEFT, RGB(25, 25, 25), "��  �� : W");
}
#pragma endregion