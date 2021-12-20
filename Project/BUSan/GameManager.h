#pragma once

#define GS_EXIT 0;
#define GS_GO	1;

enum class EGameState
{
	GS_MainLoad = 0,
	GS_Intro_Start,
	GS_Intro,
	GS_MainMenu_Start,
	GS_MainMenu,
	GS_BusStation_Start,
	GS_BusStation,
	GS_BusMove_Game_Start,
	GS_BusMove_Game,
	GS_BusMove_Event_Start,
	GS_BusMove_Event,
	GS_GameOver_Start,
	GS_GameOver,
	GS_Ending_Start,
	GS_Ending,
	
	GS_Max
};

class GameManager
{
public :
	GameManager();
	~GameManager();

	void InitGameManager(BTEngine* engine, HWND hWnd);
	
	int GameLoop();

	void DataLoad();

	void Scene_Intro_Start();

	void Scene_Intro();
	void Scene_MainMenu_Start();
	void Scene_MainMenu();
	void Scene_BusStation_Start();
	void Scene_BusStation();
	void Scene_BusMoveGame_Start();
	void Scene_BusMoveGame();
	void Scene_BusMoveEvent_Start();
	void Scene_BusMoveEvent();
	void Scene_GameOver_Start();
	void Scene_GameOver();
	void Scene_GameEnding_Start();
	void Scene_GameEnding();

	void CreateGameObject();

	void ReleaseAll(HWND hWnd);

	void DrawStationBackGround(StationNode* currStation);
	void DrawStationClock(StationNode* currStation);
	void DrawStationNodeInfo(StationNode* currStation);
	void OnClickedPageButton();
	void OnClickedNodeSelectButton(StationNode* currStation);
	void OnClickedNextButton();
	bool CheckGameOverState(StationNode* currStation);

	void DrawBusMoving(int districtID, float lerpTime = 1);
	void DrawMiniMap(int stationID, int selectID);
	void DrawMoveResultPopup(EGameState nextState, int arrivalTime_actual);

	bool DrawBusEffect(BusEffect* busEffect);

	int GetNearBusTimeIndex(BusTime table[], int currTime);
	int GetNearBusTimeIndexByTime(int time);
	void TestKeyUpdate();
	void ShowTestInfo();

private :	
	BTEngine*	 mBTEngine;
	DataManager* mDataManager;
	SoundManager* mSoundManager;

	int			mGameState;

	EventData* mSelectEventData;

	int			mCurrStationID;
	int			mSelectStationID;
	int			mLinkedStationID;


	//정류장 변수
	int			mPage;
	int			mTotalPage;
	bool		mbOnBusEffect;
	bool		mbOnNext;


	//시간 변수 
	int			mCurrTime;
	int			mSelectElapseTime;
	int			mSelectDepartureTime;
	int			mExpectArrivalTime;

	//스토리 변수
	bool		mbStoryInput;
	int			mTextIdx;
	int			mTextStartIdx;
	int			mTextEndIdx;
	int			mStoryPage;
	float		mEndingTime;
	//int			mEndingPage;
	int			mEndingGrade;

	//이벤트 변수
	int			mSelectEventID;
	float		mEventAniTime;
	int			mOffsetY;

	//이동 게임 변수
	bool		IsMovePopup;
	bool		IsStop;
	float		mStopTime;
	float		mLerpTime;
	float		mRealTime;
	int			mPushCount;
	
	int			mPushCountCorrection = 8;
	float		mSignalSpeed = 420;
	int			mSignalRegenPos = 1920 * 0.8;
	int			mLimitPushCount;

	//장면 전환 변수
	float		mFadeSize;

	//게임 오브젝트(배경)
	vector<BTScrollObject> mScrollObjList;

	BusEffect	mBusEffect;
	SignalLight mSignalLight;

	BTAniSprite mBusTire;
	
	//게임 오브젝트(버튼)
	BTGameObject bt_Intro_Skip;

	BTGameObject bt_MainMenu_Start;
	BTGameObject bt_MainMenu_Exit;
	BTGameObject bt_MainMenu_BackIntro;

	BTGameObject bt_GameOver_MainMenuGo;

	BTGameObject bt_Station_Next;

	BTGameObject bt_Station_PageNext;
	BTGameObject bt_Station_PagePrev;

	BTGameObject bt_Station_Select[4];

	BTGameObject bt_Event_Close;

	BTGameObject bt_Popup_Ok;
};