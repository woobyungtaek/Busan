#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include "TCHAR.h"
#include "windowsx.h"
#include "commdlg.h"
#include "BTEngineDefine.h"
#include "BTEngine.h"
#include "NodeTool.h"
#include "resource.h"
#include <vector>

//버스 시간표 40개, 연결 정거장 20개

using namespace std;
#define IDC_STATION_BUTTON 30001

#pragma region Window관련
LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

char* g_ClassName = "노드 생성기";
char* g_WindowName = "노드 생성기";
POINT g_ScreenSize;

HINSTANCE gInst;
HWND gMainWnd;
HWND gDialog_1;
#pragma endregion

bool			IsExistStation(int stationNum);
bool			CreateStationNode(HWND hDlg);
StationNode*	GetStationNodeByNum(int stationNum);
void			RemoveStationNodeByNum(int stationNum);
void			ShowSelectStationInfo(HWND hDlg, int aroundNum);

void ShowStationNode	(HWND hDlg, StationNode* station);
void SaveStationNode	(HWND hDlg, StationNode* station);

void LoadBusTimeTable	(HWND hDlg, StationNode* station, int aroundNum);
void ShowBusTimeByValue	(HWND hDlg, int value, int* eIdx);
void SaveBusTimeTable	(HWND hDlg, StationNode* station, int aroundNum);

void CreateStationNodeButton();
void DestroyStationNodeButton();

void LoadDataFile(TCHAR fileName[]);
void SaveDataFile(TCHAR fileName[]);

const POINT margin = {25,25};

int gCurrStationIndex;
int gCurrAroundIndex;


///선택 Station
StationNode*		gSelectedStation;

///전체 노드 버튼
vector<HWND>		gStationButtonList;

///전체 Station Node
vector<StationNode> gStationNodeList;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	WNDCLASSEX wc;
	HACCEL hAcc;

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	gInst = hInstance;

	g_ScreenSize.x = 512;
	g_ScreenSize.y = 768;

	//메인 윈도우 등록
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	RegisterClassEx(&wc);

	gMainWnd = CreateWindow(
		g_ClassName,
		"Main Window Title",
		WS_OVERLAPPEDWINDOW,
		300, 200,
		g_ScreenSize.x, g_ScreenSize.y,
		GetDesktopWindow(),
		NULL,
		hInstance,
		NULL
	);

	gDialog_1 = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), gMainWnd, (DLGPROC)DialogProc);

	SetWindowPos(gDialog_1, NULL, 300+g_ScreenSize.x, 200, 0, 0, SWP_NOSIZE);
	//SetWindowPos(gDialog_1, , g_ScreenSize.x, 0, SWP_NOSIZE);
	ShowWindow(gDialog_1, SW_SHOWDEFAULT);


	ShowWindow(gMainWnd, SW_SHOWDEFAULT);
	UpdateWindow(gMainWnd);

	gSelectedStation = nullptr;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(gMainWnd, hAcc, &msg))
			{
				if (msg.message == WM_QUIT) { break; }
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{

		}
	}

	UnregisterClass(g_ClassName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[100], lpstrFile[100] = "";
	TCHAR filter[] = "SAV File(*.sav)\0*.sav\0";

	switch (msg)
	{
	case WM_COMMAND:
		//노드 버튼 클릭시 SetNodeInfo를 실행
		if (LOWORD(wParam) >= IDC_STATION_BUTTON && LOWORD(wParam) <= IDC_STATION_BUTTON + 5000)
		{
			int loadIdx = LOWORD(wParam) - IDC_STATION_BUTTON;
			gSelectedStation = GetStationNodeByNum(loadIdx);
			ShowStationNode(gDialog_1, gSelectedStation);
			ShowSelectStationInfo(gDialog_1, -1);
			break;
		}
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			break;
		case ID_FILE_OPEN:
		{
			OPENFILENAME ofn;
			memset(&ofn, 0, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;				//대화상자의 주인 윈도우
			ofn.lpstrFilter = filter;			//파일 필터링
			ofn.lpstrFile = lpstrFile;			//파일 경로
			ofn.nMaxFile = 100;					//파일의 최대 경로
			ofn.lpstrInitialDir = "../Data";	//먼저 보여줄 폴더
			if (GetOpenFileName(&ofn) != 0)
			{
				sprintf_s(str, "%s 파일을 열겠습니까?", ofn.lpstrFile);
				int res = MessageBox(hwnd, str, "열기 선택", MB_YESNO | MB_ICONQUESTION);
				if (res == IDNO)
				{
					return 0;
				}
				LoadDataFile(ofn.lpstrFile);

				DestroyStationNodeButton();
				CreateStationNodeButton();
			}
		}
		break;
		case ID_FILE_SAVE:
		{
			OPENFILENAME sfn;
			memset(&sfn, 0, sizeof(OPENFILENAME));
			sfn.lStructSize = sizeof(OPENFILENAME);
			sfn.hwndOwner = hwnd;		//대화상자의 주인 윈도우
			sfn.lpstrFilter = filter;	//파일 필터링
			sfn.lpstrFile = lpstrFile;	//파일 경로
			sfn.nMaxFile = 256;			//파일의 최대 경로
			sfn.lpstrInitialDir = "../Data";  //먼저 보여줄 폴더
			if (GetSaveFileName(&sfn) != 0)
			{
				sprintf_s(str, "%s 파일로 저장하시겠습니까?", sfn.lpstrFile);
				int res = MessageBox(hwnd, str, "저장 선택", MB_YESNO | MB_ICONQUESTION);
				if (res == IDNO)
				{
					return 0;
				}
				SaveDataFile(sfn.lpstrFile);
			}
		}
		break;
		case ID_FILE_EXIT:
		{
			int res = MessageBox(hwnd, "프로그램을 종료할까요?", "프로그램 종료", MB_YESNO | MB_ICONQUESTION);
			if (res == IDNO)
			{
				return 0;
			}
			PostQuitMessage(0);
		}
		break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
	{
		int res = MessageBox(hwnd, "프로그램을 종료할까요?", "프로그램 종료", MB_YESNO | MB_ICONQUESTION);
		if (res == IDNO)
		{
			return 0;
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
BOOL	CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		//편집 버튼 눌렀을 때
		if (LOWORD(wParam) >= IDC_BUTTON1 && LOWORD(wParam) <= IDC_BUTTON20)
		{
			if (gSelectedStation == nullptr) { break; }

			gCurrAroundIndex = LOWORD(wParam) - IDC_BUTTON1;
			LoadBusTimeTable(hDlg, gSelectedStation, gCurrAroundIndex);
			break;
		}
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			if (CreateStationNode(hDlg) == false)
			{
				break;
			}
			//저장
			SaveStationNode(hDlg, gSelectedStation);

			//갱신
			DestroyStationNodeButton();
			CreateStationNodeButton();

			gSelectedStation = nullptr;

			ShowStationNode(hDlg, gSelectedStation);
			ShowWindow(gMainWnd, SW_SHOWDEFAULT);
		}
		break;
		case IDC_NODE_CREATE:
		//{
		//	//입력 값 로드
		//	int stationNum = GetDlgItemInt(hDlg, IDC_STATION_ID, FALSE, FALSE);
		//	if (stationNum - 1 < 0)
		//	{
		//		//값 입력 X
		//		break;
		//	}
		//	if (IsExistStation(stationNum) == FALSE)
		//	{
		//		//새 정거장 추가
		//		StationNode instStation;				
		//		instStation.StationID = stationNum;
		//		gStationNodeList.push_back(instStation);
		//		DestroyStationNodeButton();
		//		CreateStationNodeButton();
		//	}
		//	//현재 선택된 정거장 출력
		//	gSelectedStation = GetStationNodeByNum(stationNum);
		//	//추가값 설정
		//	//GetDlgItemText(hDlg, IDC_STATION_NAME, gSelectedStation->Name, 20);
		//	if (!(GetDlgItemInt(hDlg, IDC_DISTRICT_ID, FALSE, FALSE) <= 0))
		//	{
		//		gSelectedStation->DistrictID = GetDlgItemInt(hDlg, IDC_DISTRICT_ID, FALSE, FALSE);
		//	}
		//	if (!(GetDlgItemInt(hDlg, IDC_EVENT_ID, FALSE, FALSE) <= 0))
		//	{
		//		gSelectedStation->EventID = GetDlgItemInt(hDlg, IDC_EVENT_ID, FALSE, FALSE);
		//	}
		//	ShowStationNode(hDlg, gSelectedStation);
		//}
		break;
		case IDC_SAVE_TIMETABLE:
			if (gSelectedStation == nullptr)
			{
				break;
			}
			if (gCurrAroundIndex < 0)
			{
				break;
			}
			SaveBusTimeTable(hDlg, gSelectedStation, gCurrAroundIndex);
			SaveStationNode(hDlg,  gSelectedStation);
			LoadBusTimeTable(hDlg, gSelectedStation, gCurrAroundIndex);
			//gCurrAroundIndex = -1;
			break;
		case IDC_NODE_DELETE :
		{
			if (gSelectedStation == nullptr) { break; }
			char buffer[30];
			sprintf_s(buffer, "%d번 노드를 삭제하시겠습니까?", gSelectedStation->StationID);
			int res = MessageBox(hDlg, buffer, "노드 삭제", MB_YESNO | MB_ICONQUESTION);
			if (res == IDNO)
			{
				return 0;
			}

			//벡터 요소 지우기
			RemoveStationNodeByNum(gSelectedStation->StationID);
			gSelectedStation = nullptr;
			ShowSelectStationInfo(hDlg, -1);
			DestroyStationNodeButton();
			CreateStationNodeButton();
		}
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

//StationInfo 출력
void ShowStationNode(HWND hDlg, StationNode* station)
{
	//Station이 없는 경우
	if (station == nullptr)
	{
		SetDlgItemText(hDlg, IDC_STATION_NAME, "");
		SetDlgItemText(hDlg, IDC_STATION_ID, "");
		SetDlgItemText(hDlg, IDC_DISTRICT_ID, "");
		SetDlgItemText(hDlg, IDC_EVENT_ID, "");

		for (int index = 0; index < 20; index++)
		{
			SetDlgItemText(hDlg, IDC_LINKNODE_1 + index, "");
		}

		char buffer[20];
		sprintf_s(buffer, "%02d:%02d", 0, 0);
		for (int index = IDC_BUSTIME_1; index < IDC_BUSTIME_180; index++)
		{
			if (index % 3 == 2)
			{
				SetDlgItemText(hDlg, index, buffer);
			}
			else
			{
				SetDlgItemText(hDlg, index, "");
			}
		}
		return;
	}
	//Station이 있는 경우
	SetDlgItemText(hDlg, IDC_STATION_NAME, station->Name);
	SetDlgItemInt(hDlg, IDC_STATION_ID, station->StationID, FALSE);
	SetDlgItemInt(hDlg, IDC_DISTRICT_ID, station->DistrictID, FALSE);
	SetDlgItemInt(hDlg, IDC_EVENT_ID, station->EventID, FALSE);
	if (station->StationID < 0)
	{
		SetDlgItemText(hDlg, IDC_STATION_ID, "");
	}
	if (station->DistrictID < 0)
	{
		SetDlgItemText(hDlg, IDC_DISTRICT_ID, "");
	}
	if (station->EventID < 0)
	{
		SetDlgItemText(hDlg, IDC_EVENT_ID, "");
	}

	for (int index = 0; index < 20; index++)
	{
		if (station->AroundList[index].StationID <= 0)
		{
			SetDlgItemText(hDlg, IDC_LINKNODE_1 + index, "");
		}
		else
		{
			SetDlgItemInt(hDlg, IDC_LINKNODE_1 + index, station->AroundList[index].StationID, FALSE);
		}
	}
}
void SaveStationNode(HWND hDlg, StationNode* station)
{
	GetDlgItemText(hDlg, IDC_STATION_NAME, station->Name, 20);
	station->StationID = GetDlgItemInt(hDlg, IDC_STATION_ID, FALSE, TRUE);
	station->DistrictID = GetDlgItemInt(hDlg, IDC_DISTRICT_ID, FALSE, TRUE);
	station->EventID = GetDlgItemInt(hDlg, IDC_EVENT_ID, FALSE, TRUE);
	for (int index = 0; index < 20; index++)
	{
		station->AroundList[index].StationID = GetDlgItemInt(hDlg, IDC_LINKNODE_1 + index, FALSE, FALSE);
	}
}

//Station 체크
bool IsExistStation(int stationNum)
{
	int loopCount = gStationNodeList.size();
	for (int index = 0; index < loopCount; index++)
	{
		if (gStationNodeList[index].StationID == stationNum)
		{
			return true;
		}
	}
	return false;
}
bool CreateStationNode(HWND hDlg)
{
	if (gSelectedStation == nullptr
		|| gSelectedStation->StationID != GetDlgItemInt(hDlg, IDC_STATION_ID, FALSE, FALSE))
	{
		int stationNum = GetDlgItemInt(hDlg, IDC_STATION_ID, FALSE, FALSE);
		if (stationNum - 1 < 0)
		{
			//값 입력 X
			return false;
		}
		if (IsExistStation(stationNum) == FALSE)
		{
			//새 정거장 추가
			StationNode instStation;
			instStation.StationID = stationNum;

			gStationNodeList.push_back(instStation);
		}
		gSelectedStation = GetStationNodeByNum(stationNum);

		if (!(GetDlgItemInt(hDlg, IDC_DISTRICT_ID, FALSE, FALSE) <= 0))
		{
			gSelectedStation->DistrictID = GetDlgItemInt(hDlg, IDC_DISTRICT_ID, FALSE, FALSE);
		}
		if (!(GetDlgItemInt(hDlg, IDC_EVENT_ID, FALSE, FALSE) <= 0))
		{
			gSelectedStation->EventID = GetDlgItemInt(hDlg, IDC_EVENT_ID, FALSE, FALSE);
		}
		return true;
	}
	return true;
}
StationNode* GetStationNodeByNum(int stationNum)
{
	int loopCount = gStationNodeList.size();
	for (int index = 0; index < loopCount; index++)
	{
		if (gStationNodeList[index].StationID == stationNum)
		{
			return &gStationNodeList[index];
		}
	}
	return nullptr;
}
void RemoveStationNodeByNum(int stationNum)
{
	int loopCount = gStationNodeList.size();
	for (int index = 0; index < loopCount; index++)
	{
		if (gStationNodeList[index].StationID == stationNum)
		{
			gStationNodeList.erase(gStationNodeList.begin() + index);
			break;
		}
	}
}

//버튼 생성
void DestroyStationNodeButton()
{
	//모든 노드 버튼을 제거합니다.
	int loopCount = gStationButtonList.size();
	for (int index = 0; index < loopCount; index++)
	{
		DestroyWindow(gStationButtonList[index]);
	}
	gStationButtonList.clear();
}
void CreateStationNodeButton()
{
	//모든 노드 버튼을 생성합니다.
	int loopCount = gStationNodeList.size();
	for (int index = 0; index < loopCount; index++)
	{
		TCHAR buffer[30];
		sprintf_s(buffer, "노드 %d", gStationNodeList[index].StationID);

		int yPos = (gStationNodeList[index].StationID - 1) % 20;
		int xPos = (gStationNodeList[index].StationID - 1) / 20;

		HWND button;
		button = CreateWindow(
			"button", buffer,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			(85 * xPos) + margin.x, (30 * yPos)+ margin.y, 75, 25,
			gMainWnd,
			(HMENU)(IDC_STATION_BUTTON + gStationNodeList[index].StationID),
			gInst,
			NULL);
		gStationButtonList.push_back(button);
	}
}

//버스 노선 별 시간표
void LoadBusTimeTable(HWND hDlg, StationNode* station, int aroundNum)
{
	int moveTime = station->AroundList[aroundNum].BusTimeTable[0].ArrivalTime - station->AroundList[aroundNum].BusTimeTable[0].DepartureTime;

	SetDlgItemInt(hDlg, IDC_MOVE_TIME_1, moveTime / 60, TRUE);
	SetDlgItemInt(hDlg, IDC_MOVE_TIME_2, moveTime % 60, TRUE);

	int editIndex = IDC_BUSTIME_1;
	for (int index = 0; index < 60; index++)
	{
		int value = station->AroundList[aroundNum].BusTimeTable[index].DepartureTime;
		ShowBusTimeByValue(hDlg, value, &editIndex);

		value = station->AroundList[aroundNum].BusTimeTable[index].ArrivalTime;
		char buffer[20];
		if (value <= 0)
		{
			sprintf_s(buffer, "%02d:%02d", 0, 0);
			SetDlgItemText(hDlg, editIndex, buffer);
		}
		else
		{
			sprintf_s(buffer, "%02d:%02d", value / 60, value % 60);
			SetDlgItemText(hDlg, editIndex, buffer);
		}
		editIndex++;
	}
	ShowSelectStationInfo(hDlg, aroundNum + 1);
	//순서 디버깅용
	//for (int index = IDC_BUSTIME_1; index < IDC_BUSTIME_1 + 180; index++)
	//{
	//	SetDlgItemInt(hDlg, index, index- IDC_BUSTIME_1 +1, FALSE);
	//}
}
void ShowBusTimeByValue(HWND hDlg, int value, int* eIdx)
{
	if (value <= 0)
	{
		SetDlgItemText(hDlg, *eIdx, "");
		(*eIdx)++;
		SetDlgItemText(hDlg, *eIdx, "");
		(*eIdx)++;
	}
	else
	{
		SetDlgItemInt(hDlg, *eIdx, value / 60, FALSE);
		(*eIdx)++;
		SetDlgItemInt(hDlg, *eIdx, value % 60, FALSE);
		(*eIdx)++;
	}
}
void SaveBusTimeTable(HWND hDlg, StationNode* station, int aroundNum)
{
	int moveTime = GetDlgItemInt(hDlg, IDC_MOVE_TIME_1, FALSE, FALSE) * 60;
	moveTime	+= GetDlgItemInt(hDlg, IDC_MOVE_TIME_2, FALSE, FALSE);

	int editIndex = IDC_BUSTIME_1;
	for (int index = 0; index < 60; index++)
	{
		int value;
		int arrival = 0;

		value = GetDlgItemInt(hDlg, editIndex, FALSE, FALSE) * 60;
		editIndex++;
		value += GetDlgItemInt(hDlg, editIndex, FALSE, FALSE);
		if (!(value <= 0))
		{
			station->AroundList[aroundNum].BusTimeTable[index].DepartureTime = value;
		}
		else 
		{
			station->AroundList[aroundNum].BusTimeTable[index].DepartureTime = -1;
		}
		editIndex++;

		if (!(value <= 0))
		{
			arrival = value + moveTime;
			station->AroundList[aroundNum].BusTimeTable[index].ArrivalTime = arrival;
		}
		else
		{
			station->AroundList[aroundNum].BusTimeTable[index].ArrivalTime = -1;
		}
		editIndex++;
	}
}
void ShowSelectStationInfo(HWND hDlg, int aroundNum)
{
	char buffer[40];
	if (gSelectedStation != nullptr)
	{
		sprintf_s(buffer, "정거장 : %d / 연결 : %d", (int)gSelectedStation->StationID, aroundNum);
	}
	else
	{
		sprintf_s(buffer, "정거장 : %d / 연결 : %d", -1, -1 );
	}
	SetDlgItemText(hDlg, IDC_CURRENT_TIME_VIEW, buffer);
}

//바꿔야하는 친구들
void LoadDataFile(TCHAR fileName[])
{
	gStationNodeList.clear();
	FILE* fp = NULL;

#ifdef _UNICODE
	fopen_s(&fPtr, fileName, "rb, ccs = UNICODE");
#else
	fopen_s(&fp, fileName, "rb");
#endif
	if (fp == NULL) { return; }

	int DataCount = 0;
	fread(&DataCount, sizeof(int), 1, fp);

	for (int index = 0; index < DataCount; index++)
	{
		StationNode instNode;

		fread(&instNode.StationID,  sizeof(short), 1, fp);
		fread(&instNode.DistrictID, sizeof(short), 1, fp);
		fread(&instNode.EventID,    sizeof(short), 1, fp);

		int aroundSize = sizeof(instNode.AroundList) / sizeof(AroundNode);
		for (int aroundIdx = 0; aroundIdx < aroundSize; aroundIdx++)
		{
			fread(&instNode.AroundList[aroundIdx].StationID, sizeof(short), 1, fp);
			fread(&instNode.AroundList[aroundIdx].BusTimeTable, sizeof(instNode.AroundList->BusTimeTable), 1, fp);
		}
		gStationNodeList.push_back(instNode);
	}

	fclose(fp);
}
void SaveDataFile(TCHAR fileName[])
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "wb");
	if (fp == NULL) { return; }

	//노드 수 저장
	int DataCount = gStationNodeList.size();
	fwrite(&DataCount, sizeof(int), 1, fp);

	for (int index = 0; index < DataCount; index++)
	{
		fwrite(&gStationNodeList[index].StationID, sizeof(short), 1, fp);
		fwrite(&gStationNodeList[index].DistrictID, sizeof(short), 1, fp);
		fwrite(&gStationNodeList[index].EventID, sizeof(short), 1, fp);

		int aroundSize = sizeof(gStationNodeList[index].AroundList) / sizeof(AroundNode);
		for (int aroundIdx = 0; aroundIdx < aroundSize; aroundIdx++)
		{
			fwrite(&gStationNodeList[index].AroundList[aroundIdx].StationID, sizeof(short), 1, fp);
			fwrite(&gStationNodeList[index].AroundList[aroundIdx].BusTimeTable, sizeof(gStationNodeList[index].AroundList[aroundIdx].BusTimeTable), 1, fp);
		}
	}
	fclose(fp);
}