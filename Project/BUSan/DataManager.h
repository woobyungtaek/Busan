#pragma once

#define ScrollObjIndex(imgIdx) ((int)imgIdx - (int)EImgSrcIdx::Fence)

using namespace std;

#pragma region ������ �߿��� ����

//���丮 ���� �ε���
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

//�̹��� �ε���
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

//�̹��� ��� ����
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

//��ũ�� ����
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
		{1 ,"����",1},{2 ,"����",1},{3,"�ϳ�",1}, {4,"����",1}, {5,"��õ",1}, {6,"����",1}, {7,"����",1}, {8,"����",1}, {9,"����",1}, {10,"��õ",2},
		{11,"��õ",2},{12,"õ��",1},{13,"����",1},{14,"���",1},{15,"����",1},{16,"����",2},{17,"û��",1},{18,"����",2},{19,"����",2},{20,"�ȵ�",2},
		{21,"����",2},{22,"����",1},{23,"�Ǽ�",2},{24,"����",1},{25,"��õ",2},{26,"��û",2},{27,"â��",2},{28,"�뱸",1},{29,"����",2},{30,"�о�",2},
		{31,"â��",1},{32,"����",1},{33,"���",1},{34,"�λ�",1}
	};

	EventData mEventDataList[7] =
	{
		{1, "���ܰ�",			 15  , "���ڱ� ������ vs �罺�ɱ� ��� �߻�!\n�������� �ο���� ��ȭ��?!\n�ְ��ڵ��� �ο��̴�."},
		{2, "���� �̶�",		 15  , "��ĥ�� �ҷ��� ������ �ʴ� �༮\n���� ���� ���� ����޶�� ��������\n����� �ΰ��� �������� ���ѳ´�."},
		{3, "���� �ܰ� ��ü",	 15  , "�߼� �Ͱ���� ������ �и��١�\n������ ����ũ�� �ɾ�� �̰ź��� ���� ��."},
		{4, "��Ÿ�� �λ���",	-20 , "�̷��� �� �̻� û�ʹ�, �ƴ� �λ����� ��´�!!\n������! �׷��� �� �մԴ���!"},
		{5, "�׸�����Ʈ",		-25 , "������ �� ������ �޷���\n��������� Ư���� ����� ����\n�׸�����Ʈ�� ������!"},
		{6, "ȣ�ΰ��� �Թ�",	 30  , "���� â�� ������ ���̴� õ�� ȣ�ΰ��� ����. \n��, �̰� �� ����."},
		{7, "��������� 3����",	-20 , "������ ����ġ�ٰ� �� ���������\n����� �ڷ� �������� �пջ� �б⿡ ȣ�ٴڡ�"}
	};

	char* StoryTextArr[(int)EStoryTextIdx::StroyTextMax] = {
		"������ ����ģ�� ��ȯ�̿� ��â ������� ���� ���̴�.",						
		"�׷��� ����ģ���� �λ� �߷����� ���۽��� ����-�λ� ��Ÿ� ���ָ� �ϰ� �ƴ�.",
		"�߼� ���޸� �¾� ����ģ���� �ִ� �λ꿡 ����� ������ ����!",				
		"�׷��� �߼� ���� ��ӹ���, KTX ǥ ���ϱ�� �ϴ��� ������!",				
		"������ ����� ���� �����ϴ�. ��ӹ����� �ȵǸ� �ó������� Ÿ�� ����!",	
		
		//1
		"��¼�ٺ��� ��� �ð����� ���� ���� ������ ����.",
		"�ð��� ���� ���� ��ȯ���� ���� ã�ư���.",
		"������ ������ �ڽ��� �̸� �湮�� ����ġ ���� ��ȯ�̿� ���� ������ ��ȸ�� ����ϴµ�...",
		"�� ���ҳ�! �����!",

		//2
		"��¼�ٺ��� ��� �ð����� ���� ���� ������ ����.",
		"�ð��� ���� ���� ��ȯ���� ���� ã�ư���.",
		"������ �̸� �湮�� ����ġ ���� ��ȯ.",
		"��Ŭ���� �Ӹ��� ���� �� �� ������� ����ģ���� ���� �ߴ�.",
		"������ �׳� ������ ����Ʈ����!",
		
		//3
		"��ӽð��� ���� ���� �λ��� ���÷��̽� ���鿡 ������ ����.",
		"��ȯ�̸� ���� ȸ�� �԰� �װ� ������ �̾߱⵵ ������ �ູ�� ����Ʈ�� ����.",
		"���� �� ����ģ���� �ְ��!",
		
		//4
		"\"�������.\" ������ ���� �������ڸ��� ������ ��ȯ���� ù ���𿴴�.",
		"��� ��ȯ�̴� �λ� �߷� ���� ��ӵ� ��Ÿ� ���ֿ� ���� ���±⸦ ������ �־���.",
		"�ᱹ ���� ��ӽð����� ���� ���� ������ ���ڸ��� �� �ӿ� ��Ƶ״� �̺��� ���´�.",
		"��ü �� �� ������� �°���?"
	};
};