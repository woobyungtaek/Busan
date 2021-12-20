#pragma once

#define ScrollObjIndex(imgIdx) ((int)imgIdx - (int)EImgSrcIdx::Fence)

using namespace std;

#pragma region 순서가 중요한 정보

//스토리 문구 인덱스
enum class EStoryTextIdx
{
	Intro1 = 0,
	Intro2,
	Intro3,
	Intro4,
	Intro5,

	Ending1_1,
	Ending1_2,
	Ending1_3,
	Ending1_4,
	
	Ending2_1,
	Ending2_2,
	Ending2_3,
	Ending2_4,
	Ending2_5,
	
	Ending3_1,
	Ending3_2,
	Ending3_3,

	Ending4_1,
	Ending4_2,
	Ending4_3,
	Ending4_4,

	StroyTextMax
};

//이미지 인덱스
enum class EImgSrcIdx
{
	BUS1 = 0,
	BUS2,
	BUS3,

	BusTire,

	Signal1,
	Signal2,
	Signal3,

	Station1,
	Station2,

	Background1,
	Background2,
	Background3,

	Road,
	Fence,

	Seoul_BCity,
	Seoul_Tower,
	Seoul_FCity,

	Chung_BSan,
	Chung_FSan,
	Chung_Road,
	Chung_Grass,

	Busan_BCity,
	Busan_Bridge,
	Busan_FCity,
	Busan_Ocean,

	EventCloseBT,

	GoIconGray,
	GoIconGreen,
	GreenArrow,
	RedArrow,

	ClockLocationBB,
	MiniClockBoard,
	MiniBoard,

	Event_Fight,
	Event_DDong,
	Event_TrafficJam,
	Event_FireBus,
	Event_Greenlight,
	Event_Hodoo,
	Event_SamDae,
	Event_Sadfrog,

	Intro_0,
	Intro_1,
	Intro_2,
	Intro_3,

	GameOver,

	SeoulStation,
	ChungStation,
	BusanStation,

	Title,

	Ending1,
	Ending2,
	Ending3,
	Ending4,

	MapBoard,

	PopupBoard,

	SrcMax
};

//이미지 경로 정보
static char* ImgSrcPath[(int)EImgSrcIdx::SrcMax] ={
	"../DATA/BMP/Bus_gyeonggi.bmp",							//BUS1
	"../DATA/BMP/Bus_chungcung.bmp",						//BUS2
	"../DATA/BMP/Bus_gyungsang.bmp",						//BUS3
	"../DATA/BMP/BusTire.bmp",								//BusTire
															
	"../DATA/BMP/signal_red.bmp",							//Signal1
	"../DATA/BMP/signal_yellow.bmp",						//Signal2
	"../DATA/BMP/signal_green.bmp",							//Signal3
															
	"../DATA/BMP/Station_city.bmp",							//Station1
	"../DATA/BMP/Station_ssigol.bmp",						//Station2
															
	"../DATA/BMP/Seoul/SeoulBackground.bmp",				//Background1
	"../DATA/BMP/Chungcheong/ChungcheongBackground.bmp",	//Background2
	"../DATA/BMP/Busan/BusanBackground.bmp",				//Background3
															
	"../DATA/BMP/Road.bmp",									//Road
	"../DATA/BMP/Fence.bmp",								//Fence
															
	"../DATA/BMP/Seoul/BackBuilding.bmp",					//Seoul_BCity
	"../DATA/BMP/Seoul/NamsanTower.bmp",					//Seoul_Tower
	"../DATA/BMP/Seoul/CityBuilding.bmp",					//Seoul_FCity
															
	"../DATA/BMP/Chungcheong/BackMountain.bmp",				//Chung_BSan
	"../DATA/BMP/Chungcheong/mountain.bmp",					//Chung_FSan
	"../DATA/BMP/Chungcheong/CountryRoad.bmp",				//Chung_Road
	"../DATA/BMP/Chungcheong/Grass.bmp",					//Chung_Grass
															
	"../DATA/BMP/Busan/BackBuilding.bmp",					//Busan_BCity,
	"../DATA/BMP/Busan/Bridge.bmp",							//Busan_Bridge
	"../DATA/BMP/Busan/BusanBuilding.bmp",					//Busan_FCity,
	"../DATA/BMP/Busan/Ocean.bmp",							//Busan_Ocean,
																
	"../DATA/UI/PostitBold.bmp",							//EventCloseBT,
	"../DATA/UI/GoIconGray.bmp",							//GoIconGray,
	"../DATA/UI/GoIconGreen.bmp",							//GoIconGreen,

	"../DATA/UI/GreenArrow.bmp",							//GoIconGreen,
	"../DATA/UI/RedArrow.bmp",								//GoIconGreen,

	"../DATA/UI/ClockLocationBillboard.bmp",				//ClockLocationBillboard,
	"../DATA/UI/MiniClockBillboard.bmp",					//MiniClockBoard,
	"../DATA/UI/MiniBillboard.bmp",							//MiniBoard,
															
	"../DATA/EVENT/Polaroid_Fight.bmp",						//Event_Fight,
	"../DATA/EVENT/Polaroid_Ddong.bmp",						//Event_DDong,
	"../DATA/EVENT/Polaroid_Trafficjam.bmp",				//Event_TrafficJam,
	"../DATA/EVENT/FireBus.bmp",							//Event_FireBus,
	"../DATA/EVENT/Greenlight.bmp",							//Event_Greenlight,
	"../DATA/EVENT/CheonAn_Hodoo.bmp",						//Event_Hodoo,
	"../DATA/EVENT/SeongNam_Polaroid.bmp",					//Event_Hodoo,
	"../DATA/EVENT/SadFrog.bmp",							//Event_Sadfrog,

															
	"../DATA/Intro/Opening0.bmp",							//Intro0,
	"../DATA/Intro/Opening_1_LongDistance_BMP_2.bmp",		//Intro1,
	"../DATA/Intro/Opening_2_Soldout_Bmp.bmp",				//Intro2,
	"../DATA/Intro/Opening_3_GO_BMP.bmp",					//Intro3,

	"../DATA/GameOver/Gameover.bmp",						//GameOver

	"../DATA/BMP/SeoulBusStop.bmp",							//seoul Station
	"../DATA/BMP/ChungCheongBusStop.bmp",					//chung Station
	"../DATA/BMP/BusanBusStop.bmp",							//Busan Station

	"../DATA/BMP/Title.bmp",								//Title

	"../DATA/Ending/Ending1.bmp",							//ending1
	"../DATA/Ending/Ending2.bmp",							//ending2
	"../DATA/Ending/Ending3.bmp",							//ending3
	"../DATA/Ending/Ending4.bmp",							//ending4

	"../DATA/UI/MapBoard.bmp",								//MapBoard
	"../DATA/UI/PopupBoard.bmp"								//PopupBoard
};

//스크롤 정보
static BTScrollData mScrollData[ScrollObjIndex(EImgSrcIdx::Busan_FCity) + 1] ={
	//speed,x,y,sx,sy,alpha,dirX
	{150, 0,500, 0.8, 0.8,1, -1}, //Fence,

	{5,  0, 235, 0.8, 0.8,1, -1}, //Seoul_BCity,
	{10, 0, 0,   0.8, 0.8,1, -1}, //Seoul_Tower,
	{30, 0, 300, 0.8, 0.8,1, -1}, //Seoul_FCity,	

	{0.1 ,0, 100, 0.6, 0.6, 1, -1}, //Chung_BSan,
	{4   ,0, 100, 0.6, 0.6, 1, -1}, //Chung_FSan,
	{15  ,0, 330, 0.6, 0.6, 1, -1}, //Chung_Road,
	{35  ,0, 400, 0.6, 0.6, 1, -1}, //Chung_Grass,	

	{10, -200, 80, 0.6, 0.6 ,1, -1}, //Busan_BCity,
	{30, 100, 159, 0.6, 0.6 ,1, -1}, //Busan_Bridge,
	{30,-200, 130, 0.6, 0.6,1, -1}, //Busan_FCity,
};

#pragma endregion

struct StationNameData
{
	int StationID;
	char Name[20];
	int ImageID;
};
struct EventData
{
	int		EventID;
	char	Title[30];
	int		Time;
	char	Desc[150];
};

class DataManager
{
public:
	DataManager();
	~DataManager();

public:
	void LoadStationDataListFromFile(TCHAR filePath[]);
	void LoadImageDataFromFile(BTEngine* engine);
	void LoadMiniMapDataFromFile(BTEngine* engine);
	void DataRelease();

	StationNode* GetStationNodeByID(int stationID);

	char* GetStationNameDataById(int stationID);
	int GetStationImageIdById(int stationID);

	BTSprite* GetSpriteByIndex(int index);
	BTSprite* GetMiniMapByID(int ID);
	EventData* GetEventDataByIndex(int index);


	char* GetStoryText(int index)
	{
		return StoryTextArr[index];
	}

	BTAniSprite sprBusTire;
private:
	vector<StationNode> mStationNodeList;
	vector<BTSprite>	mSpriteList;
	vector<BTSprite>	mMiniMapSpriteList;

	StationNameData		mStationNameList[STATION_COUNT] =
	{
		{1 ,"서울",1},{2 ,"구리",1},{3,"하남",1}, {4,"성남",1}, {5,"과천",1}, {6,"수원",1}, {7,"평택",1}, {8,"용인",1}, {9,"광주",1}, {10,"제천",2},
		{11,"진천",2},{12,"천안",1},{13,"세종",1},{14,"논산",1},{15,"대전",1},{16,"영동",2},{17,"청주",1},{18,"증평",2},{19,"문경",2},{20,"안동",2},
		{21,"영덕",2},{22,"포항",1},{23,"의성",2},{24,"구미",1},{25,"김천",2},{26,"산청",2},{27,"창녕",2},{28,"대구",1},{29,"경주",2},{30,"밀양",2},
		{31,"창원",1},{32,"김해",1},{33,"울산",1},{34,"부산",1}
	};

	EventData mEventDataList[7] =
	{
		{1, "팝콘각",			 15  , "갑자기 나루토 vs 사스케급 대결 발생!\n아저씨들 싸움수준 실화냐?!\n최강자들의 싸움이다."},
		{2, "하필 이때",		 15  , "며칠간 불러도 나오지 않던 녀석\n하필 지금 문을 열어달라고 했지만…\n가까스로 인간의 존엄성을 지켜냈다."},
		{3, "명절 단골 정체",	 15  , "추석 귀경길은 언제나 밀린다…\n내려서 문워크로 걸어가도 이거보단 빠를 듯."},
		{4, "불타는 부산행",	-20 , "이렇게 된 이상 청와대, 아니 부산으로 밟는다!!\n오케이! 그래야 내 손님답지!"},
		{5, "그린라이트",		-25 , "조급한 내 마음을 달래는\n사소하지만 특별한 행운의 연속\n그린라이트로 가버렷!"},
		{6, "호두과자 먹방",	 30  , "버스 창문 밖으로 보이는 천안 호두과자 가게. \n아, 이건 못 참지."},
		{7, "게임인재원 3대장",	-20 , "성남을 지나치다가 본 게임인재원\n목덜미 뒤로 느껴지는 패왕색 패기에 호다닥…"}
	};

	char* StoryTextArr[(int)EStoryTextIdx::StroyTextMax] = {
		"윤서는 남자친구 윤환이와 한창 알콩달콩 연애 중이다.",						
		"그런데 남자친구의 부산 발령으로 갑작스레 서울-부산 장거리 연애를 하게 됐다.",
		"추석 연휴를 맞아 남자친구가 있는 부산에 가기로 결정한 윤서!",				
		"그러나 추석 시즌에 고속버스, KTX 표 구하기는 하늘의 별따기!",				
		"하지만 사랑의 힘은 위대하다. 고속버스가 안되면 시내버스라도 타고 가자!",	
		
		//1
		"어쩌다보니 약속 시간보다 한참 일찍 도착한 윤서.",
		"시간이 남아 곧장 윤환이의 집에 찾아갔다.",
		"하지만 윤서는 자신의 이른 방문을 예상치 못한 윤환이와 낯선 여자의 밀회를 목격하는데...",
		"이 망할놈! 헤어져!",

		//2
		"어쩌다보니 약속 시간보다 조금 일찍 도착한 윤서.",
		"시간이 남아 곧장 윤환이의 집에 찾아갔다.",
		"윤서의 이른 방문을 예상치 못한 윤환.",
		"헝클어진 머리에 잠이 덜 깬 모습으로 여자친구를 맞이 했다.",
		"오늘은 그냥 집에서 데이트하자!",
		
		//3
		"약속시간에 얼추 맞춰 부산의 핫플레이스 서면에 도착한 윤서.",
		"윤환이를 만나 회도 먹고 그간 못다한 이야기도 나누며 행복한 데이트를 즐겼다.",
		"역시 내 남자친구가 최고야!",
		
		//4
		"\"헤어지자.\" 윤서의 얼굴을 마주하자마자 내뱉은 윤환이의 첫 마디였다.",
		"사실 윤환이는 부산 발령 이후 계속된 장거리 연애에 지쳐 권태기를 느끼고 있었다.",
		"결국 오늘 약속시간보다 많이 늦은 윤서를 보자마자 맘 속에 담아뒀던 이별을 꺼냈다.",
		"대체 나 왜 여기까지 온거지?"
	};
};